 //  Created by SARATH R on 26/09/14. 
 //  FUNCTION TO FIND PRIME FACTORS USING RECUSRION 
#include <stdio.h>
int main()
{
     int  i;
     int pf(int);
     printf ( "Enter an intiger\n" );
     scanf ( "%d" , &i);
    pf(i);
     printf ( "\n" );
return 0;
}
int pf( int  i)
{
     int  j, k;
     for  (j= 2 ; j<=i; j++)
    {
        k = i / j;
         if (i % j == 0 )
        {
             printf ( "%d " ,j);
             pf (k);
             break ;
        }
    }
     return   0 ;
}
