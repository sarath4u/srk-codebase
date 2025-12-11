 //  Created by SARATH R on 26/09/14. 
 //PROGRAM TO PRINT THE MULTIPLICATION TABLE OF ANY NUMBER 
#include <stdio.h>
int main()
{
     int  i,num,m;
     printf ( "Enter a number\n" );
     scanf ( "%d" ,&num);
     for  (i= 1 ; i<= 10 ; i++)
    {
        m=i*num;
         printf ( "%d*%d=%d\n" ,num,i,m);
    }
    return 0;
}
