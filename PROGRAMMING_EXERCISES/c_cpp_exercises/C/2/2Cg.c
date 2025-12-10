/*program to check if a triangle is valid if the angles are input*/
/*sarath 08.09.14*/
#include <stdio.h>
int main()
{
  float  a,b,c,sum;
     printf ( "Enter the angles\n" );
     scanf ( "%f%f%f" ,&a,&b,&c);
     /*formula*/ 
    sum=a+b+c;
     if (sum== 180 )
	{
		 if (a== 0 ||b== 0 ||c== 0 )
                 printf ( "Invalid angles\n" );
         else 
             printf ( "The angles are of a valid triangle\n" );
	}
     else 
         printf ( "Invalid angles\n" );
return 0;
}
