module parse_model_mod
  implicit none
  private
  public :: parse_text_model, condition_mapper, key_finder, get_base_score, xgb_predictor

  ! Derived type to mimic dictionary
  type :: node_t
    character(len=32) :: key = ""  ! Feature name or "leaf"
    real              :: val = 0.0 ! Threshold or leaf value
  end type node_t

  ! Feature map for X indexing
  type :: feature_map_t
    character(len=32), allocatable :: names(:)
    integer                        :: n_features = 0
  contains
    procedure                      :: get_index => feature_map_get_index
  end type feature_map_t

contains

  ! Get column index for a feature name
  pure integer function feature_map_get_index(this, name) result(idx)
    class(feature_map_t), intent(in) :: this
    character(len=*),     intent(in) :: name
    integer                          :: i

    idx = -1
    do i = 1, this%n_features
      if (trim(this%names(i)) == trim(name)) then
        idx = i
        exit
      end if
    end do
  end function feature_map_get_index

  ! Parse the model in text format to build a matrix
  ! The matrix contains a dictionary that pairs the
  ! conditions in each booster to the corresponding output
  subroutine parse_text_model(model_txt, num_boost_rounds, max_depth, node_mat, feature_map)
    character(len=*),          intent(in)  :: model_txt        ! model in text format
    integer,                   intent(in)  :: num_boost_rounds ! total no. of trees
    integer,                   intent(in)  :: max_depth        ! depth of each tree
    type(node_t), allocatable, intent(out) :: node_mat(:,:)    ! Matrix equivalent of the model
    type(feature_map_t),       intent(out) :: feature_map
    
    ! Local variables
    integer                        :: num_leaves               ! total no. of leaves (output)
    integer                        :: num_nodes                ! total no. of nodes (conditions)
    integer                        :: total_size
    integer                        :: io_unit, ios, booster, node
    character(len=512)             :: line
    character(len=32)              :: node_str, key
    real                           :: val
    integer                        :: i, pos1, pos2
    logical                        :: is_leaf
    character(len=32), allocatable :: temp_features(:)
    integer                        :: feature_count, max_features

    ! Calculate sizes
    num_leaves = 2**max_depth
    num_nodes = 0
    do i = 0, max_depth - 1
      num_nodes = num_nodes + 2**i
    end do
    total_size = num_nodes + num_leaves

    ! Allocate output matrix
    allocate(node_mat(0:num_boost_rounds-1, 0:total_size-1))

    ! Initialize matrix
    node_mat(:,:)%key = ""
    node_mat(:,:)%val = 0.0

    ! Initialize feature map
    max_features = 10 ! Initial guess, will reallocate if needed
    allocate(temp_features(max_features))
    feature_count = 0

    ! Open file with newunit
    open(newunit=io_unit, file=model_txt, status='old', action='read', iostat=ios)
    if (ios /= 0) then
      print *, "Error opening file: ", trim(model_txt)
      return
    end if

    booster = -1
    do
      read(io_unit, '(A)', iostat=ios) line
      if (ios /= 0) exit
      line = adjustl(trim(line))
      if (line == "") cycle

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

      is_leaf = (index(line, 'leaf=') > 0)
      if (is_leaf) then
        key = "leaf"
        pos1 = index(line, '=') + 1
        read(line(pos1:), *, iostat=ios) val
        if (ios /= 0) then
          print *, "Warning: Invalid leaf value in line: ", trim(line)
          cycle
        end if
      else
        pos1 = index(line, '[')
        pos2 = index(line, '<')
        if (pos1 < 1 .or. pos2 < pos1) then
          print *, "Warning: Invalid condition format in line: ", trim(line)
          cycle
        end if
        key = line(pos1+1:pos2-1)
        pos1 = pos2 + 1
        pos2 = index(line, ']')
        if (pos2 < pos1) then
          print *, "Warning: Missing ']' in line: ", trim(line)
          cycle
        end if
        read(line(pos1:pos2-1), *, iostat=ios) val
        if (ios /= 0) then
          print *, "Warning: Invalid threshold value in line: ", trim(line)
          cycle
        end if
        ! Add feature to map if new
        if (all(temp_features(1:feature_count) /= key)) then
          feature_count = feature_count + 1
          if (feature_count > max_features) then
            max_features = max_features * 2
            call reallocate_features(temp_features, max_features)
          end if
          temp_features(feature_count) = key
        end if
      end if

      node_mat(booster, node)%key = key
      node_mat(booster, node)%val = val
    end do

    close(io_unit)

    ! Finalize feature map
    allocate(feature_map%names(feature_count))
    feature_map%names = temp_features(1:feature_count)
    feature_map%n_features = feature_count
    deallocate(temp_features)
  end subroutine parse_text_model

  ! Helper to reallocate feature array
  subroutine reallocate_features(features, new_size)
    character(len=32), allocatable, intent(inout) :: features(:)
    integer,                        intent(in)    :: new_size
    character(len=32), allocatable                :: temp(:)
    allocate(temp(new_size))
    temp(1:size(features)) = features
    call move_alloc(temp, features)
  end subroutine reallocate_features

  ! Function to compare the actual value with the model
  ! value and navigate to the next node in the tree
  pure integer function condition_mapper(actual_val, model_val, node) result(next_node)
    real,    intent(in)           :: actual_val, model_val
    integer, intent(in), optional :: node
    integer                       :: local_node
    local_node = 0
    if (present(node)) local_node = node
    if (actual_val < model_val) then
      next_node = 2 * local_node + 1
    else
      next_node = 2 * (local_node + 1)
    end if
  end function condition_mapper

  ! Function to find the key name
  pure function key_finder(con_dict) result(key)
    type(node_t), intent(in) :: con_dict
    character(len=32)        :: key
    key = con_dict%key
  end function key_finder

  ! Function to get the base score of the model. This
  ! value is on which the model output is built upon. 
  ! It is the average of the train data outputs for regression.
  function get_base_score(base_score_file) result(score)
    character(len=*), intent(in) :: base_score_file
    real                         :: score
    integer                      :: io_unit, ios

    ! Open and read file
    open(newunit=io_unit, file=base_score_file, status='old', action='read', iostat=ios)
    if (ios /= 0) then
      print *, "Error: Cannot open base_score file: ", trim(base_score_file)
      stop
    end if

    read(io_unit, *, iostat=ios) score
    if (ios /= 0) then
      print *, "Error: Invalid base_score value in file: ", trim(base_score_file)
      close(io_unit)
      stop
    end if

    close(io_unit)
  end function get_base_score
    
  ! Prediction function
  function xgb_predictor(model_txt, num_boost_rounds, max_depth, X, base_score_file) result(preds)
    character(len=*), intent(in) :: model_txt
    integer,          intent(in) :: num_boost_rounds, max_depth
    real,             intent(in) :: X(:,:)
    character(len=*), intent(in) :: base_score_file
    real, allocatable            :: preds(:)
    
    type(node_t), allocatable    :: node_mat(:,:)
    type(feature_map_t)          :: feature_map
    real                         :: base_score, pred, actual_val, model_val
    integer                      :: n_samples, n_features, i, booster, node, next_node, feature_idx
    character(len=32)            :: key

    ! Get dimensions
    n_samples = size(X, 1)
    n_features = size(X, 2)
    allocate(preds(n_samples))

    ! Parse model
    call parse_text_model(model_txt, num_boost_rounds, max_depth, node_mat, feature_map)

    ! Get base score
    base_score = get_base_score(base_score_file)

    ! Evaluate each sample
    do i = 1, n_samples
      pred = base_score
      do booster = 0, num_boost_rounds - 1
        node = 0
        do while (.true.)
          key = key_finder(node_mat(booster, node))
          if (key == "leaf") then
            pred = pred + node_mat(booster, node)%val
            exit
          end if
          feature_idx = feature_map%get_index(key)
          if (feature_idx < 1) then
            print *, "Error: Feature not found: ", trim(key)
            pred = 0.0
            exit
          end if
          actual_val = X(i, feature_idx)
          model_val = node_mat(booster, node)%val
          next_node = condition_mapper(actual_val, model_val, node)
          node = next_node
        end do
      end do
      preds(i) = pred
    end do
  end function xgb_predictor

end module parse_model_mod
