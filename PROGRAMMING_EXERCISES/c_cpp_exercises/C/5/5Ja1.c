 //  Created by SARATH R on 26/09/14. 
 //  Sum of the digits of a five digit number 
#include <stdio.h>
int main()
{
     int  i, sum;
     int digsum(int);
     printf ( "Enter any five digit number\n" );
     scanf ( "%d" ,&i);
    sum = digsum(i);
     printf ( "sum of the digits is %d\n" ,sum);
return 0;
}
int digsum( int  i)
{
     int  z =  10000 , sum =  0 , count, dig;
     for  (count= 1 ; count<= 5 ; count++)
    {
        dig = i/z;
        sum = sum + dig;
        i = i%z;
        z = z/ 10 ;
    }
     return  sum;
}
