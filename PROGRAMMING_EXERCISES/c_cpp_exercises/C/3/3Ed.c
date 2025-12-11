 //  Created by SARATH R on 26/09/14. 
 //PROGRAM TO PRINT ALL COMBINATION OF 123 
#include <stdio.h>
 int main()
{
     int  i,j,k,comb;
     for  (i= 1 ;i<= 3 ;i++)
    {
         for  (j= 1 ; j<= 3  ;j++)
        {
             if  (i==j)
                 continue ;
             for  (k= 1 ; k<= 3 ; k++)
            {
                 if  (k==j || k==i)
                     continue ;
                comb=i* 100 +j* 10 +k;
                    printf ( "\n%d" ,comb);
            }
        }
    }
  printf ( "\n");
return 0;
}
