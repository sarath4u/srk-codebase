 // Created by SARATH R on 26/09/14. 
 // PROGRAM FUN2 
#include  <stdio.h> 
#include  <stdlib.h> 
#include  <math.h> 
 int main()
{
     float  x,lg= 0 ,a,i;
     printf ( "Enter any number\n" );
     scanf ( "%f" ,&x);
     if  (x== 0 )
    {
         printf ( "Cannot be determined\n" );
         exit ( 0 );
    }
 else 
{
     for  (i= 1 ;i<= 6 ;i++)
    {
        lg=lg+( 1 /i)*( pow (((x- 1 )/x),i));
    }
     printf ( "Natural logrithm of %f = %f\n" ,x,lg);
}
return 0;
}
