/*program to calculate area and perimeter of a rectangle and circle*/
/*sarath 23.08.14*/
#include <stdio.h>
int main()
{
float l,b,r,ar,ac,pr,pc;
printf("Enter length of the rectangle: ");
scanf("%f",&l);
printf("Enter breadth of the rectangle: ");
scanf("%f",&b);
printf("Enter radius of the circle: ");
scanf("%f",&r);
/*formulas*/
ar=l*b;
pr=2*(l+b);
ac=3.14*r*r;
pc=2*3.14*r;
printf("Area of the rectangle is %f \n Perimeter of the rectangle is %f \n Area of the circle is %f perimeter of the circle is %f\n",ar,pr,ac,pc);
return 0;
}
