 //  Created by SARATH R on 26/09/14. 
 //  Converting year to Roman numerals using function 
#include <stdio.h>
 int main()
{
     int  yr;
     int rc(int);
     printf ( "Enter an year\n" );
     scanf ( "%d" ,&yr);
     rc(yr);
     return 0;
}
int rc( int  year)
{
     int  m, mr, i, d, dr, j, c, cr, k, l, lr, n, xr, x, v, vr, p, q, o;
     m = year /  1000 ;
     mr = year %  1000 ;
     for  (i =  1 ; i <= m; i++)
         printf ( "m" );
     d = mr /  500 ;
     dr = mr %  500 ;
     for  (j =  1 ; j <= d; j++)
         printf ( "d" );
     c = dr /  100 ;
     cr = dr %  100 ;
     for  (k =  1 ; k <= c; k++)
         printf ( "c" );
     l = cr /  50 ;
     lr = cr %  50 ;
     for  (n =  1 ; n <= l; n++)
         printf ( "l" );
     xr = lr %  10 ;
     x = lr /  10 ;
     for  (o =  1 ; o <= x; o++)
         printf ( "x" );
     v = xr /  5 ;
     vr = xr %  5 ;
     for  (p =  1 ; p <= v; p++)
         printf ( "v" );
     for  (q =  1 ; q <= vr; q++)
         printf ( "i" );
     printf ( "\n" );
     return ( 0 );
}
