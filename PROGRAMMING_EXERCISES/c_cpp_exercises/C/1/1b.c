/*program to convert units of distances*/
/*sarath 23.08.14*/
#include <stdio.h>
int main()
{
float distkm, distm, distft, distinch, distcm;
printf("Enter distance in km: ");
scanf("%f",&distkm);
/*formula for conversion*/
distm=distkm * 1000;
distft=distm * 32;
distinch=distft * 12;
distcm=distm * 100;
printf("%f km is %f meters \n %f feet \n %f inches \n %f centimeters\n",distkm, distm, distft, distinch, distcm);
return 0;
}
