/*program to determine profit or loss*/
/*sarath 25.08.14*/
#include <stdio.h>
int main()
{
int  sp,cp,dif;
printf ( "Enter the cost price and selling price of the item: " );
scanf ( "%d%d" ,&cp,&sp);
/*formula*/ 
dif=sp-cp;
if (dif> 0 )
  printf("your profit is %d\n" ,dif);
else if (dif< 0 )
printf("your loss is %d\n" ,dif);
else 
  printf ("no profit or loss\n");
return 0;
}
