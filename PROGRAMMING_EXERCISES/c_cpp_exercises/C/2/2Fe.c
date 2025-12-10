/*program to find the fine dues in a library*/
/*sarath 13.09.14*/
#include <stdio.h>
int main()
{
int  day;
     float  rate= 5.00 ,fine;
     printf ( "How late did the person submit?\n" );
     scanf ( "%d" ,&day);
     /*formula*/ 
     if (day<= 5 )
        rate= 0.50 ;
     else   if (day> 5 &&day<= 10 )
	rate= 1 ;
     else   if (day> 10 &&day<= 30 )
	rate= 5 ;
     else 
         printf ( "Membership cancelled\n" );
    fine=day*rate;
     printf ( "Your dues equal %f\n" ,fine);
return 0;
}
