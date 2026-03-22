program initialize
  use geo_utils
  implicit none

  integer :: n = 5
  allocate(dat(n)) 
  dat = [1, 2, 3, 4, 5]
  is_set = .true.

  print *, dat
  print *, is_set
end program initialize
