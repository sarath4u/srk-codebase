// Created by SARATH R on 26/09/14.
//PROGRAM TO FIND THE RANGE OF A SET
#include <stdio.h>
int main()
{
     int  size,num,max,min,i= 1 ;
     printf ( "Enter the size of the set\n" );
     scanf ( "%d" ,&size);
     printf ( "Enter number: " );
     scanf ( "%d" ,&num);
    min=num;
    max=num;
     while  (i<size)
    {
         printf ( "Enter: " );
         scanf ( "%d" ,&num);
         if  (num<min)
            min=num;
         if  (num>max)
            max=num;
        i++;
    }
     printf ( "RANGE = %d\n" ,max-min);
return 0;
}
