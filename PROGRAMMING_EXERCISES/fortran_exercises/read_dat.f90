program reverse_write
  implicit none

  type :: person_t
    character(len=32) :: nam
    integer           :: age
  end type person_t

  type(person_t), allocatable :: person(:) 
  integer                     :: ios, unitread, unitwrite, indx, ii, cnt
  character(len=32)           :: fileread = 'name_age.txt', filewrite='rev_dat.txt', line
  open(newunit=unitread, file=fileread, status='old', action='read', iostat=ios)
  if (ios /= 0) then
    print *, "Error opening file ", trim(fileread)
    stop
  end if
  allocate(person(8))
  cnt = 0
  do 
    read(unitread, "(A)", iostat=ios) line
    if (ios /= 0) exit
    line = adjustl(trim(line))
    cnt = cnt + 1
    person(cnt)%age = 0 
    indx = index(line, ' ')
    person(cnt)%nam = line(:indx) 
    read(line(indx+1:indx+2), "(I32)", iostat=ios) person(cnt)%age
  end do
  open(newunit=unitwrite, file=filewrite, status='replace', action='write', iostat=ios)
  do ii=1, cnt
    write(unitwrite, *, iostat=ios) person(ii)%age, person(ii)%nam
  end do
  deallocate(person)
end program reverse_write
