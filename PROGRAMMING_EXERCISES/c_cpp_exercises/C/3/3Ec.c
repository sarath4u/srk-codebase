 //  Created by SARATH R on 26/09/14. 
 //PROGRAM TO ADD THE FIRST SEVEN DIGITS OF N/N! SERIES 
#include <stdio.h>
 int main()
{
     int  i,n;
     float  fact, ser= 0 ;
     for  (n= 1 ;n< 8 ;n++)
    {
        fact= 1.0 ;
         for  (i= 1 ;i<=n;i++)
        {
        fact=fact*i;
        }
        ser=ser+(n/fact);
        printf ( "%f\n" ,ser);
    }
    return 0;
}
