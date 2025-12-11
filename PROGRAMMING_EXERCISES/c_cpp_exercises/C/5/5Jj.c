//  Created by SARATH R on 26/09/14. 
//  FUNCTION TO FIND THE DISTANCE B/W TWO POINTS WHICH IS USED TO COMPUTE AREA. 
#include <math.h> 
#include <stdio.h>
int main()
{
     float  dist( float ,  float ,  float ,  float ),x1, y1, x2, y2, x3, y3, a, b, c, s, area( float ,  float ,  float ,  float ), ar;
     printf ( "Enter co-ordinates of the vertices\n" );
     scanf ( "%f%f%f%f%f%f" , &x1, &y1, &x2, &y2, &x3, &y3);
           a =  dist (x1, y1, x2, y2);
           b =  dist (x2, y2, x3, y3);
           c =  dist (x1, y1, x3, y3);
    s = (a + b + c)/ 2 ;
    ar =  area (s, a, b, c);
     printf ( "area : %f\n" , ar);
return 0;
}
float  dist( float  x1,  float  y1,  float  x2, float  y2)
{
     float  side;
    side =  pow (( pow ((x1 - x2),  2 ) +  pow ((y1 - y2),  2 )),  0.5 );
     return  side;
}
float  area( float  s,  float  a,  float  b,  float  c)
{
     float  ar;
    ar =  pow  (s*(s-a)*(s-b)*(s-c),  0.5 );
     return  ar;
}
