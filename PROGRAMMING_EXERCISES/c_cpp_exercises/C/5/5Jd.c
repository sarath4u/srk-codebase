//  Created by SARATH R on 26/09/14. 
//  FUNCTION TO FIND BINARY EQUIVALENT USING RECUSRION 
#include  <math.h> 
#include <stdio.h>
int main()
{
     int  n,i= 0 ,bin= 0 ;
     int bnry(int, int, int);
     printf ( "Enter a number\n" );
     scanf ( "%d" ,&n);
    bnry(n,bin,i);
return 0;
}
int bnry( int  n, int  bin, int  i)
{
     int  rem;
    rem = n% 2 ;
    n = n/ 2 ;
    bin = bin + rem* pow ( 10 ,i);
    i++;
     if  (n ==  0 )
         printf ( "binary equivalent is %d\n" , bin);
     else 
         bnry (n,bin,i);
     return   0 ;
}
