/*program to no of currency notes to issue*/
/*sarath 24.08.14*/
#include <stdio.h>
int main()
{
   int  n,h,rh,f,rf,t;
     printf ( "Enter the amount: " );
     scanf ( "%d" ,&n);
     /*formula*/ 
     /*total no of 100s*/ 
    h=n/100 ;
    rh=n%100 ;
     /*total no of 50s*/ 
    f=rh/50 ;
    rf=rh%50 ;
     /*no of 10s*/ 
    t=rf/10 ;
     printf ( "no of 100s, 50s, 10s are %d,%d,%d respectively\n" ,h,f,t);
return 0;
}
