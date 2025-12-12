//  Created by SARATH R on 26/09/14. 
//  Copyright (c) 2014 SARATH R. All rights reserved. 
//  Bubble Sort 
#include <stdio.h>
int main()
{
     int  i, data[ 25 ], j, temp;
     printf ( "Enter 25 Numbers\n" );
     for  (i =  0 ; i <  25 ; i++)
    {
         scanf ( "%d" , &data[i]);
    }
     for  (j =  0 ; j <  23 ; j++)
    {
         for  (i =  0 ; i <  24  - j; i++)
        {
             if  (data[i] > data[i +  1 ])
            {
                temp = data[i +  1 ];
                data[i +  1 ] = data[i];
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
