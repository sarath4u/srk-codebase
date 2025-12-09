/*program to calculate gross salary*/
/*sarath 23.08.14*/
#include <stdio.h>
int main()
{
int bsal; 
float gsal;
printf("Enter basic salary: ");
scanf("%d",&bsal);
/*formula for gross salary*/
gsal=bsal*160/100;
printf("Your Gross salary is %f\n",gsal);
return 0;
}
