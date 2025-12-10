/*program to find leap year or not*/
/*sarath 25.08.14*/
#include <stdio.h>
int main()
{
  int  n;
  printf ( "Enter year\n" );
  scanf ( "%d" ,&n);
  /*formula*/ 
  if (n% 4 == 0 && n% 100 != 0 )
    printf ( "leap year\n" );
  else 
    printf ( "not a leap year\n" );
return 0;
}
