//  Created by SARATH R on 26/09/14. 
//  FIBINACCI SERIES using RECURSION 
#include <stdio.h>
int main()
{
     int  n =  0 , count = 25 , i=- 1 ;
     int fibi(int, int, int);
    fibi(n,count,i);
    return 0;
}
int fibi( int  n,  int  count,  int  i)
    {
        i = n-i;
        n = n + i;
        count--;
         printf ( "%d\n" , n);
         if  (count >=  1 )
             fibi (n,count,i);
         return   0 ;
}
