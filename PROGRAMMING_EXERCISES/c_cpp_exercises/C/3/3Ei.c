// Created by SARATH R on 26/09/14. 
// PROGRAM FUN 
#include <stdio.h>
int main()
{
     int  i= 1 ,j= 1 ;
     int  count, space;
     while  (i<= 4 )
        {
             for  (space= 11 -i; space> 0 ; space--)
            {
                 printf ( " " );
            }
             for  (count=i;count> 0 ;count--)
            {
                 printf ( "%d " ,j);
                j++;
            }
            i++;
             printf ( "\n" );
        }
  return 0;
}
