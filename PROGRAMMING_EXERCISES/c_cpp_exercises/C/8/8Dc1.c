//  Created by SARATH R on 26/09/14. 
//  Selection Sort 
#include <stdio.h>
int main()
{
     int  i, data[ 25 ], j, temp;
     printf ( "Enter 25 Numbers\n" );
     for  (i =  0 ; i <  25 ; i++)
    {
         scanf ( "%d" , &data[i]);
    }
     for  (i =  0 ; i <  25 ; i++)
    {
         for  (j = i+ 1 ; j <  25 ; j++)
        {
             if  (data[i] > data[j])
            {
                temp = data[j];
                data[j] = data[i];
                data[i] = temp;
            }
        }
    }
     for  (i =  0 ; i <  25 ; i++)
    {
         printf ( "\n%d" , data[i]);
    }
     printf("\n");
return 0;
}
