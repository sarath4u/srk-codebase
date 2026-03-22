module geo_utils
  implicit none
  private
  public :: scale_vector, is_set, dat

  type :: Point2D_t
   real :: x = 0.,  y = 0.
   
   contains
   procedure :: distance => Point2D_distance
  end type Point2D_t

  integer, allocatable :: dat(:)
  logical              :: is_set = .false.
  contains
  real function Point2D_distance(this, A) result (dist)
     class(point2d_t), intent (in) :: this
     type(point2d_t) , intent (in) :: A
     dist = ((A%x - this%x)**2 + (A%y - this%y)**2)**0.5
  end function Point2D_distance

  pure function scale_vector(arr, scalar) result(sc_arr)
     real,              intent(in) :: arr(:)
     real, allocatable             :: sc_arr(:)
     real,              intent(in) :: scalar
     integer                       :: m, i

     m = size(arr)
     allocate(sc_arr(m))
     do i = 1, m
       sc_arr(i) = arr(i) * scalar
     end do
  end function scale_vector 

end module geo_utils

