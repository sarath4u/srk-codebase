/*program to check area is larger than perimeter*/
/*sarath 13.09.14*/
#include <stdio.h>
int main()
{
  float  l,b;
     printf ( "Enter the length and breadth\n" );
     scanf ( "%f%f" ,&l,&b);
     /*formula*/ 
     if (l*b> 2 *(l+b))
	{
		 printf ( "area is greater than perimeter\n" );
	}
     else   if (l*b< 2 *(l+b))
	{
         printf ( "perimeter is greater than area\n" );
	}
     else 
         printf ( "perimeter is equal to area\n" );
return 0;
}
