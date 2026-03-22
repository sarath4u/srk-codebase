program test
  use geo_utils
  implicit none
  type(Point2D_t) :: A
  type(Point2D_t) :: B
  A%x = 0.
  A%y = 0. 
  B%x = 3.
  B%y = 4. 
  print *, A%distance(B)
end program test
