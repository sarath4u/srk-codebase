program readtxt
  implicit none

  integer           :: even_count, ii, unit_var, ios, line=0
  character(len=32) :: filename = 'dat.txt'
  open(newunit=unit_var, file=filename, status='old', action='read', iostat=ios)
  if (ios /= 0) then
     print *, "Error opening the file ", trim(filename)
     stop
  end if
  even_count = 0
  do
    read(unit_var, *, iostat=ios) line
    if (ios /= 0) exit
    if (mod(line, 2) == 0) then 
      even_count = even_count + 1
    end if
  end do

  print *, "No of even numbers = ", even_count 
end program readtxt
