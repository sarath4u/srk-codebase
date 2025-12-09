/*program to calculate aggregate marks and percentage of five subjects*/
/*sarath 23.08.14*/
#include <stdio.h>
int main()
{
float phy, chem, math, bio, eng, agg, per;
printf("Enter your physics marks: ");
scanf("%f",&phy);
printf("Enter your chemistry marks: ");
scanf("%f",&chem);
printf("Enter your maths marks: ");
scanf("%f",&math);
printf("Enter your biology mark: ");
scanf("%f",&bio);
printf("Enter your english mark: ");
scanf("%f",&eng);
/*formula for aggregate*/
agg=phy+chem+math+bio+eng;
/*formula for percentage*/
per=agg/5;
printf("marks: %f\n", per);
printf("your aggregate is %f and percentage is %f\n",agg,per);
return 0;
}
