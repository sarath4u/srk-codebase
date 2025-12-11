 //  Created by SARATH R on 26/09/14. 
 //  sending both int and float in a function 
#include <stdio.h>
 int main()
{
     int  a =  5 ;
     float  b =  4.5 , ans;
     float  mult( int , float );
    ans =  mult (a,b);
     printf ( "%f\n" , ans);
return 0;
}
 float  mult( int  i,  float  j)
{
     float  re;
    re = i*j;
     return  re;
}
