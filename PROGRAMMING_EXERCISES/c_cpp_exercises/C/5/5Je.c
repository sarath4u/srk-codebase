//  Created by SARATH R on 26/09/14. 
//  RECURSIVE FUNCTION TO FIND RUNNING SUM OF FIRST 25 NATURAL NUMBERS 
#include <stdio.h>
int main()
{
     int  n =  0 , i =  0 ;
     int runsum(int, int);
    runsum(n, i);
return 0;
}
int runsum( int  n,  int  i)
{
    n = n+i ;
    i = i+ 1 ;
     if  (i <= 25 )
         runsum (n,i);
     else 
         printf ( "Running total: %d\n" , n);
     return   0 ;
}
