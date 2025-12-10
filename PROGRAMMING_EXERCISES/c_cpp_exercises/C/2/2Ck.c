/*program to check where a point lies with respect to a circle*/
/*sarath 13.09.14*/
#include <stdio.h>
#include <math.h>
int main()
{
  int  x,y,r,a,b,dist;
     printf ( "Enter the centre of the circle\n" );
     scanf ( "%d%d" ,&x,&y);
     printf ( "Enter radius\n" );
     scanf ( "%d" ,&r);
     printf ( "Enter the point\n" );
     scanf ( "%d%d" ,&a,&b);
     /*formula*/ 
    dist= sqrt ( pow ((x-a), 2 )+ pow ((y-b), 2 ));
     if (dist==r)
	{
         printf ( "point lies on the circle\n" );
	}
     else   if (dist>r)
         printf ( "point lies outside the circle\n" );
         else 
             printf ( "Point lies inside the circle\n" );
return 0;
}
