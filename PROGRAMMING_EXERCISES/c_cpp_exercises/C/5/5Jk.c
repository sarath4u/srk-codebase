//  Created by SARATH R on 26/09/14. 
//  FUNCTION TO FIND THE GREATEST COMMON DIVISOR BY EUCLID"S ALGORITHM 
#include <stdio.h>
int main()
{
     int  a, b, greatest_common_divisor, gcd(int, int);
     printf ( "Enter two numbers\n" );
     scanf ( "%d%d" , &a, &b);
     if (a>b)
        greatest_common_divisor = gcd(a, b);
     else 
        greatest_common_divisor = gcd(b, a);
     printf ( "The greatest common divisor of %d and %d is %d\n" , a, b, greatest_common_divisor);
   return 0;
}
int gcd( int  a,  int  b)
{
     int  rem =  1 ;
     while (rem !=  0 )
    {
        rem = a%b;
        a = b;
        b = rem;
    }
     return  a;
}
