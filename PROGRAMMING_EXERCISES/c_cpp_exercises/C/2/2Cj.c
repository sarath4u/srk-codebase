/*program to check if three points lie on the same line*/
/*sarath 13.09.14*/
#include <stdio.h>
int main()
{
     int  x1,x2,x3,y1,y2,y3;
     float  m1,m2;
     printf ( "Enter first point\n" );
     scanf ( "%d%d" ,&x1,&y1);
     printf ( "Enter second point\n" );
     scanf ( "%d%d" ,&x2,&y2);
     printf ( "Enter third point\n" );
     scanf ( "%d%d" ,&x3,&y3);
     /*formula*/ 
    m1=(y2-y1)/(x2-x1);
    m2=(y3-y1)/(x3-x1);
     if (m1==m2)
	{
         printf ( "all points lie on the same line\n" );
	}
     else 
     printf ( "Points fall on different lines\n" );
return 0;
}
