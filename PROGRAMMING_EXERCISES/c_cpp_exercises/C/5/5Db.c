 //  Created by SARATH R on 26/09/14. 
 //  Power(a,b) using function 
#include <stdio.h>
 int main()
{
     int  a, b, val;
     int power(int, int);
     printf ( "Enter the number to be raised\n" );
     scanf ( "%d" ,&a);
     printf ( "Enter the power to which %d to be raised to\n" ,a);
     scanf ( "%d" ,&b);
     val = power(a,b);
     printf ( "%d to the power %d = %d\n" , a, b, val);
}
int power( int  i,  int  j)
{
     int  count, value;
     value = i;
     for  (count =  1 ; count <= j; count++)
        i = i*value;
     return (i);
return 0;
}
