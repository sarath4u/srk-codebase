// Created by SARATH R on 26/09/14. 
// PROGRAM TO SEE HOW INTEREST COMPOUND 
#include  <stdio.h> 
#include  <math.h> 
int main()
{
     int  i;
     float  p,n,r,q,a;
     for  (i= 0 ; i<= 9 ; i++)
    {
     printf ( "Enter Principal\n" );
     scanf ( "%f" ,&p);
     printf ( "Enter no. of years\n" );
     scanf ( "%f" ,&n);
         printf ( "Enter rate\n" );
     scanf ( "%f" ,&r);
     printf ( "Enter compound\n" );
         scanf ( "%f" ,&q);
    a=p*( pow (( 1 +(r/q)),n*q));
          printf ( "Amount = %f\n" ,a);
         }
         return 0;
}
