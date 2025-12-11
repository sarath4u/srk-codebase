#include <math.h> 
#include <stdio.h>
int main()
{
     int  n,i= 0 ,oct= 0 ,rem,num;
     printf ( "Enter a number\n" );
     scanf ( "%d" ,&n);
    num=n;
     while (n!= 0 )
    {
        rem=n% 8 ;
        n=n/ 8 ;
        oct=oct+rem* pow ( 10 ,i);
        i++;
   }
     printf ( "octal equivalent of %d is %d\n" ,num,oct);
return 0;
}
