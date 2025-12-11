 //  Created by SARATH R on 26/09/14. 
 //  finding average and percentage of three subjects using function 

float  average( float ,  float ,  float );
float  percentage( float , float , float );
#include <stdio.h>
int main()
{
     float  s1,s2,s3;
     float  avg, per;
     printf ( "Enter marks for s1, s2, s3 respectively\n" );
     scanf ( "%f%f%f" ,&s1,&s2,&s3);
    avg =  average (s1,s2,s3);
    per =  percentage  (s1,s2,s3);
     printf ( "average = %f, percentage = %f\n" , avg,per);
return 0;
}
 float  average( float  a,  float  b,  float  c)
{
     float  av;
    av = (a+b+c)/ 3 ;
     return  av;
}
 float  percentage( float  a,  float  b,  float  c)
{
     float  p;
    p=(a+b+c)/ 300 ;
     return  p;
}
