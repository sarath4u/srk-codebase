/*program to find the factorial*/
/*sarath 22.09.14*/
#include <stdio.h>
int main()
{
     int  n,i= 1 ,f= 1 ,c;
     printf ( "Enter any number\n" );
     scanf ( "%d" ,&n);
    c=n;
     /*formula*/ 
     while (i<=n)
	{
        f=f*n;
        n--;
	}
     printf ( "%d factorial = %d\n" ,c,f);
return 0;
}
