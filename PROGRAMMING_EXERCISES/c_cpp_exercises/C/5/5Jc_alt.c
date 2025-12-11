 //  Created by SARATH R on 26/09/14. 
 //  FIBINACCI SERIES 
#include <stdio.h>
int main()
{
     int  n =  0 ;
     int  count, i =  1 ;
     for ( count =  1 ; i <=  25  ;)
    {
         printf ( "%d\n" , count);
        count = count + n;
        n = count-n;
        i++;
    }
return 0;
}
