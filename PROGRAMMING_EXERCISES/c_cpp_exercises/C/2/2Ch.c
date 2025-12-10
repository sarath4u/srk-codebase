/*program to find the absolute value of a number*/
/*sarath 08.09.14*/
#include <stdio.h>
int main()
{
  int  a,abs;
     printf ( "Enter the number\n" );
     scanf ( "%d" ,&a);
     /*formula*/ 
     if (a>= 0 )
	{
		 printf ( "%d\n" ,a);
	}
     else 
	{
        abs=a*(- 1 );
         printf ( "%d\n" ,abs);
	}
return 0;
}
