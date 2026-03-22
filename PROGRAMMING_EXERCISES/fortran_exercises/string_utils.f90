module string_utils
  implicit none
  private
  public :: to_upper
contains
  character function to_upper(c) result(cap)
    character, intent(inout) :: c
    cap = achar(iachar(c) - 32)
    c = cap
  end function to_upper
end module string_utils
