module parse_model_mod
  implicit none
  private
  public :: init_model, condition_mapper, key_finder, frixgb

  ! Derived type to store node information
  type :: node_t
    character(len=32) :: key = ""         ! Feature name or "leaf"
    real              :: threshold = 0.0  ! Threshold or leaf value
    integer           :: gotonode = -1    ! Node to jump to (yes branch)
  end type node_t

  ! Feature map for indexing
  type :: feature_map_t
    character(len=32), allocatable :: names(:)
    integer                        :: n_features = 0
  contains
    procedure :: get_index => feature_map_get_index
  end type feature_map_t

  ! Global variables
  type(node_t)       , allocatable, save :: node_mat(:,:)           ! Fortran equivalent of the model
  type(feature_map_t), save              :: feature_map
  logical            , save              :: is_initialized = .false.
  real               , save              :: base_score = 0.0

contains

  ! Get column index for a feature name
  pure integer function feature_map_get_index(this, name) result(idx)
    class(feature_map_t), intent(in) :: this
    character(len=*)    , intent(in) :: name
    integer                          :: i
    idx = -1
    do i = 1, this%n_features
      if (trim(this%names(i)) == trim(name)) then
        idx = i
        exit
      end if
    end do
  end function feature_map_get_index

  !+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  ! Parse the model in text format to build a matrix.          !
  ! The matrix contains a dictionary that pairs the            !  
  ! conditions in each booster to the corresponding            !
  ! output. In addition, it also saves the base score. This    !
  ! value is on which the model output is built upon.          !
  ! It is the average of the train data outputs for regression.!
  !++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++!
  subroutine init_model(model_txt, num_boost_rounds, base_score_file)
    character(len=*), intent(in) :: model_txt                         ! model in text format
    integer         , intent(in) :: num_boost_rounds                  ! total no. of trees
    character(len=*), intent(in) :: base_score_file                   ! file that contains the base score
    
    ! Local variables
    integer                        :: io_unit, ios, booster, node, gotonode
    character(len=512)             :: line
    character(len=32)              :: node_str, key
    real                           :: threshold
    integer                        :: pos1, pos2, pos3, max_node, i
    logical                        :: is_leaf
    character(len=32), allocatable :: temp_features(:)
    integer                        :: feature_count, max_features
    integer          , allocatable :: node_list(:), node_counts(:)
    integer                        :: max_nodes

    ! Check if already initialized
    if (is_initialized) return

    ! Read base score
    open(newunit=io_unit, file=base_score_file, status='old', action='read', iostat=ios)
    if (ios /= 0) then
      print *, "Error: Cannot open base_score file: ", trim(base_score_file)
      stop
    end if
    read(io_unit, *, iostat=ios) base_score
    if (ios /= 0) then
      print *, "Error: Invalid base_score value in file: ", trim(base_score_file)
      close(io_unit)
      stop
    end if
    close(io_unit)

    ! Initialize feature map
    max_features = 10
    allocate(temp_features(max_features))
    feature_count = 0

    ! Initialize node list for counting
    allocate(node_list(0:1000)) ! Arbitrary initial size
    allocate(node_counts(0:num_boost_rounds-1))
    node_counts = 0
    max_nodes = 0

    ! Open model file
    open(newunit=io_unit, file=model_txt, status='old', action='read', iostat=ios)
    if (ios /= 0) then
      print *, "Error opening file: ", trim(model_txt)
      stop
    end if

    booster = -1
    do
      read(io_unit, '(A)', iostat=ios) line
      if (ios /= 0) exit
      line = adjustl(trim(line))
      if (line == "") cycle

      ! Parse booster line
      if (index(line, 'booster') == 1) then
        pos1 = index(line, '[') + 1
        pos2 = index(line, ']') - 1
        read(line(pos1:pos2), *, iostat=ios) booster
        if (ios /= 0) then
          print *, "Warning: Invalid booster line: ", trim(line)
          cycle
        end if
        cycle
      end if

      ! Parse node line
      pos1 = index(line, ':')
      if (pos1 == 0) then
        print *, "Warning: Invalid node line: ", trim(line)
        cycle
      end if
      node_str = line(1:pos1-1)
      read(node_str, *, iostat=ios) node
      if (ios /= 0) then
        print *, "Warning: Invalid node index in line: ", trim(line)
        cycle
      end if

      ! Track node indices
      if (node >= size(node_list)) then
        call reallocate_node_list(node_list, node + 1000)
      end if
      node_list(node_counts(booster)) = node
      node_counts(booster) = node_counts(booster) + 1
      max_nodes = max(max_nodes, node + 1)

      is_leaf = (index(line, 'leaf=') > 0)
      if (is_leaf) then
        key = "leaf"
        pos1 = index(line, '=') + 1
        read(line(pos1:), *, iostat=ios) threshold
        if (ios /= 0) then
          print *, "Warning: Invalid leaf value in line: ", trim(line)
          cycle
        end if
        gotonode = -1
      else
        pos1 = index(line, '[') + 1
        pos2 = index(line, '<')
        pos3 = index(line, ']')
        if (pos1 < 1 .or. pos2 < pos1 .or. pos3 < pos2) then
          print *, "Warning: Invalid condition format in line: ", trim(line)
          cycle
        end if
        key = line(pos1:pos2-1)
        read(line(pos2+1:pos3-1), *, iostat=ios) threshold
        if (ios /= 0) then
          print *, "Warning: Invalid threshold value in line: ", trim(line)
          cycle
        end if
        pos1 = index(line, 'yes=') + 4
        pos2 = index(line(pos1:), ',')
        read(line(pos1:pos1+pos2-2), *, iostat=ios) gotonode
        if (ios /= 0) then
          print *, "Warning: Invalid yes= value in line: ", trim(line)
          cycle
        end if
        ! Add feature to map
        if (all(temp_features(1:feature_count) /= key)) then
          feature_count = feature_count + 1
          if (feature_count > max_features) then
            max_features = max_features * 2
            call reallocate_features(temp_features, max_features)
          end if
          temp_features(feature_count) = key
        end if
      end if

      ! Store in node_mat if allocated
      if (allocated(node_mat)) then
        node_mat(booster, node)%key = key
        node_mat(booster, node)%threshold = threshold
        node_mat(booster, node)%gotonode = gotonode
      end if
    end do

    close(io_unit)

    ! Allocate node_mat based on max node index
    if (.not. allocated(node_mat)) then
      allocate(node_mat(0:num_boost_rounds-1, 0:max_nodes-1))
      node_mat(:,:)%key = ""
      node_mat(:,:)%threshold = 0.0
      node_mat(:,:)%gotonode = -1
      ! Rewind and re-parse to fill node_mat
      open(newunit=io_unit, file=model_txt, status='old', action='read', iostat=ios)
      booster = -1
      do
        read(io_unit, '(A)', iostat=ios) line
        if (ios /= 0) exit
        line = adjustl(trim(line))
        if (line == "") cycle
        if (index(line, 'booster') == 1) then
          pos1 = index(line, '[') + 1
          pos2 = index(line, ']') - 1
          read(line(pos1:pos2), *) booster
          cycle
        end if
        pos1 = index(line, ':')
        node_str = line(1:pos1-1)
        read(node_str, *) node
        is_leaf = (index(line, 'leaf=') > 0)
        if (is_leaf) then
          key = "leaf"
          pos1 = index(line, '=') + 1
          read(line(pos1:), *) threshold
          gotonode = -1
        else
          pos1 = index(line, '[') + 1
          pos2 = index(line, '<')
          pos3 = index(line, ']')
          key = line(pos1:pos2-1)
          read(line(pos2+1:pos3-1), *) threshold
          pos1 = index(line, 'yes=') + 4
          pos2 = index(line(pos1:), ',')
          read(line(pos1:pos1+pos2-2), *) gotonode
        end if
        node_mat(booster, node)%key = key
        node_mat(booster, node)%threshold = threshold
        node_mat(booster, node)%gotonode = gotonode
      end do
      close(io_unit)
    end if

    ! Finalize feature map
    allocate(feature_map%names(feature_count))
    feature_map%names = temp_features(1:feature_count)
    feature_map%n_features = feature_count
    deallocate(temp_features)
    deallocate(node_list)
    deallocate(node_counts)

    ! Set initialization flag
    is_initialized = .true.
  end subroutine init_model

  ! Helper to reallocate feature array
  subroutine reallocate_features(features, new_size)
    character(len=32), allocatable, intent(inout) :: features(:)
    integer                       , intent(in)    :: new_size
    character(len=32), allocatable                :: temp(:)
    allocate(temp(new_size))
    temp(1:size(features)) = features
    call move_alloc(temp, features)
  end subroutine reallocate_features

  ! Helper to reallocate node list
  subroutine reallocate_node_list(node_list, new_size)
    integer, allocatable, intent(inout) :: node_list(:)
    integer             , intent(in)    :: new_size
    integer, allocatable                :: temp(:)
    allocate(temp(new_size))
    temp(1:size(node_list)) = node_list
    call move_alloc(temp, node_list)
  end subroutine reallocate_node_list

  ! Function to compare the actual value with the model
  ! value and navigate to the next node in the tree
  pure integer function condition_mapper(actual_val, node_data) result(next_node)
    real        , intent(in) :: actual_val
    type(node_t), intent(in) :: node_data
    if (actual_val < node_data%threshold) then
      next_node = node_data%gotonode
    else
      next_node = node_data%gotonode + 1
    end if
  end function condition_mapper

  ! Function to find the key name
  pure function key_finder(con_dict) result(key)
    type(node_t), intent(in) :: con_dict
    character(len=32)        :: key
    key = con_dict%key
  end function key_finder

  ! Prediction function
  function frixgb(model_txt, num_boost_rounds, var_dict_names, var_dict_values, max_depth) result(pred)
    character(len=*) , intent(in)           :: model_txt
    integer          , intent(in)           :: num_boost_rounds
    character(len=32), intent(in)           :: var_dict_names(:)
    real             , intent(in)           :: var_dict_values(:)
    integer          , intent(in), optional :: max_depth
    real                                    :: pred
    
    real                                    :: actual_val
    integer                                 :: booster, node, next_node, feature_idx
    character(len=32)                       :: key

    ! Check if model is initialized
    if (.not. is_initialized) then
      print *, "Error: Model not initialized. Call init_model first."
      stop
    end if

    ! Evaluate sample using global base_score
    pred = base_score
    do booster = 0, num_boost_rounds - 1
      node = 0
      do while (.true.)
        key = key_finder(node_mat(booster, node))
        if (key == "leaf") then
          pred = pred + node_mat(booster, node)%threshold
          exit
        end if
        feature_idx = feature_map%get_index(key)
        if (feature_idx < 1) then
          print *, "Error: Feature not found in feature map: ", trim(key)
          pred = 0.0
          exit
        end if
        ! Find feature value in var_dict
        feature_idx = 0
        do feature_idx = 1, size(var_dict_names)
          if (trim(var_dict_names(feature_idx)) == trim(key)) then
            actual_val = var_dict_values(feature_idx)
            exit
          end if
        end do
        if (feature_idx > size(var_dict_names)) then
          print *, "Error: Feature not found in var_dict: ", trim(key)
          pred = 0.0
          exit
        end if
        next_node = condition_mapper(actual_val, node_mat(booster, node))
        node = next_node
      end do
    end do
  end function frixgb

end module parse_model_mod
