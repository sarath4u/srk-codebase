//  Created by SARATH R on 26/09/14. 
//  Sum of the digits of a five digit number with recursion 
#include <stdio.h>
int main()
{
     int  i, z= 10000 , sum= 0 ;
     int digsum(int, int, int);
     printf ( "Enter any five digit number\n" );
     scanf ( "%d" ,&i);
    digsum(i,z,sum);
return 0;
}
int digsum( int  i,  int  z,  int  sum)
{
     int  dig;
        dig = i/z;
        sum = sum + dig;
        i = i%z;
        z = z/ 10 ;
     if  (z >=  1 )
    {
         digsum (i,z,sum);
    }
  else 
     printf ( "sum of the digits is %d\n" ,sum);
     return   0 ;
}
