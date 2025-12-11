/*program to calculate the overtime pay of ten employees*/
/*sarath 22.09.14*/
#include <stdio.h>
int main()
{
  int  hrs,pay= 0 ;
     printf ( "Enter no of hours\n" );
     scanf ( "%d" ,&hrs);
     /*formula*/ 
     while (hrs> 400 )
    {
        pay=(hrs- 400 )* 12 ;
         break ;
    }
     printf ( "Overtme pay = %d\n" ,pay);
return 0;
}
