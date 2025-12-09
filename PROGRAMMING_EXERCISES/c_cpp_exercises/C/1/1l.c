/*program to find the cost price of one item*/
/*sarath 24.08.14*/
#include <stdio.h>
int main()
{
float  sp,sp1,p,p1,cp;
printf ( "Enter the selling price of 15 item\n" );
scanf ( "%f" ,&sp);
/*formula*/ 
/*selling price of one item*/ 
sp1=sp/ 15 ;
printf ( "enter total profit: " );
scanf ( "%f" ,&p);
/*profit of one item*/ 
p1=p/ 15 ;
cp=sp1-p1;
printf ( "cost price of one item is %f\n" ,cp);
return 0;
}
