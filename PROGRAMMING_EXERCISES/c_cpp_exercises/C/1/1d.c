/*program to convert temperature in fahrenheit to degree centigrade*/
/*sarath 23.08.14*/
#include <stdio.h>
int main()
{
float far,deg;
printf("Enter temperature in fahrenheit: ");
scanf("%f",&far);
/*formula for conversion*/
deg=5*(far-32)/9;
printf("Temperature in degree celsius is %f\n",deg);
return 0;
}
