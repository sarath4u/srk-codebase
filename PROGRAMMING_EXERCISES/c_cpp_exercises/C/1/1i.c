/*program to find the sum of the first and last digits of a four digit no*/
/*sarath 23.08.14*/
#include <stdio.h>
int main()
{
int  n,sum,rfo,rt,rse,fo;
printf ( "Enter a four digit no: " );
scanf ( "%d" ,&n);
/*formula*/ 
rfo=n% 1000 ;
rt=rfo% 100 ;
rse=rt% 10 ;
fo=n/ 1000 ;
sum=fo+rse;
printf ("The sum of the first and last digit is %d\n" ,sum);
return 0;
}
