 //  Created by SARATH R on 26/09/14. 
 //PROGRAM TO ESTIMATE THE LIFE OF A MACHINE 
#include <stdio.h>
 int main()
{
     int  n= 1 ;
     float  net,other= 0 ;
 while  ( 1 )
{
    net=n* 1000 - 6000 - 2000 ;
    other= 6000 * 0.12 *n;
     printf ( "%f  %f\n" ,net,other);
     if  (net>=other && net> 0 )
    {
         printf ( "\n%d" ,n);
         break ;
    }
    n++;
}
return 0;
}
