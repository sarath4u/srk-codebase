 //  Created by SARATH R on 26/09/14. 
 //  Factorial using function 

#include <stdio.h>
int main()
{
     int  n,c,f;
     int factorial(int);
     printf ( "Enter any number\n" );
     scanf ( "%d" ,&n);
    f=factorial(n);
    c=n;
     printf ( "%d factorial = %d\n" ,c,f);
}
int factorial(n)
int n;
{
     int  i= 1 ,f= 1 ;
     while (i<=n)
    {
        f=f*n;
        n--;
    }
     return (f);
return 0;
}
