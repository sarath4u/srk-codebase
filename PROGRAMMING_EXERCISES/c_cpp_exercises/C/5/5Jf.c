 //  Created by SARATH R on 26/09/14. 
 //  sin(x) = x-(x3 /3!)+(x5 /5!)-(x7 /7!) to five significant digits! 
#include  <math.h> 
#include <stdio.h>
 int main()
{
     float  x, sinx;
     float  sine ( float );
     printf ( "Enter any value\n" );
     scanf ( "%f" , &x);
     sinx =  sine (x);
     printf ( "\nSin(%f) = %f\n" , x, sinx);
return 0;
}
 float  sine( float  x)
{
     int  i,j,k,count = 1 ;
     float  si = 0 ;
     for (i= 1 ; i<= 15 ; i = i+ 2 )
    {
        k =  1 ;
         for  (j =  1 ; j<=i; j++)
            k=k*j;
         si = si-(( pow (- 1 , count))*( pow (x,i))/k);
                 printf ( "%d %d %d %d %f\n" ,i,j,k,count,si);
        count ++;
    }
     return  si;
}
