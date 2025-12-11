//  Created by SARATH R on 26/09/14. 
//PROGRAM TO FIND PRINT ALL PRIME NUMBERS BELOW 300 
#include <stdio.h>
 int main()
{
     int  i,j,n;
     printf ( "1 2" );
     for  (i= 3 ; i<= 300 ; i++)
    {
         for  (j= 2 ;j<i;j++)
        {
            n=i%j;
             if (n== 0 )
                 break ;
             if (j==i- 1 )
                 printf ( " %d" ,i);
        }
        
    }
  printf("\n");
return 0;
}
