/*program to fine odd or even*/
/*sarath 25.08.14*/
#include <stdio.h>
int main()
  {
  int  n,r;
  printf ( "Enter number: " );
  scanf ( "%d" ,&n);
  /*formula*/ 
  r=n% 2 ;
  if  (r== 0 )
  {
    if (n== 0 )
    printf ( "neither even nor odd\n" );
    else 
    printf ( "even number\n" );
    }
  else 
    printf ( "odd number\n" );
return 0;
}
