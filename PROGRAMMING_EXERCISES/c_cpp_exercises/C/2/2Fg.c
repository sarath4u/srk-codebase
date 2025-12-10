/*program to find the type of the triangle*/
/*sarath 13.09.14*/
#include <stdio.h>
#include <math.h>
int main()
{
     int  a,b,c,sq1,sq2,sq3,ssq1,ssq2,ssq3;
     printf ( "Enter lengths of the sides?\n" );
     scanf ( "%d%d%d" ,&a,&b,&c);
     /*formula*/ 
     if ((a==b&&b!=c)||(a!=c&&b==c)||(c!=b&&a==c))
         printf ( "Isosceles triangle\n" );
     else   if (a==b&&a==c&&b==c)
	 printf ( "Equilateral triangle\n" );
     else   if (a!=b&&a!=c&&b!=c)
	 printf ( "Scalene triangle\n" );
    sq1= pow (a, 2 );
    sq2= pow (b, 2 );
    sq3= pow (c, 2 );
    ssq1=( pow (a, 2 )+ pow (b, 2 ));
    ssq2=( pow (b, 2 )+ pow (c, 2 ));
    ssq3=( pow (a, 2 )+ pow (c, 2 ));
     if ((sq1==ssq2)||(sq2==ssq3)||(sq3==ssq1))
         printf ( "Right triangle\n" );
return 0;
}
