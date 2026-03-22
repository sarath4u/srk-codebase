program test_scalar_vector
  use geo_utils
  implicit none

  real :: arr(3) = [1., 2., 3.]
  real :: scalar = 2.
  print *, scale_vector(arr, scalar)
end program test_scalar_vector


