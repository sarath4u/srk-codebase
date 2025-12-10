/*program to find if a student gets a degree*/
/*sarath 20.09.14*/
#include <stdio.h>
int main()
{
    float  a,b;
     printf ( "Enter your percentage marks in A & B respectively\n");
     scanf ( "%f%f" ,&a,&b);
     /*formula*/ 
     if (a>= 0.55 &&b>= 0.45 )
         printf ( "Passed\n");
     else   if (a<= 0.55 &&a>= 0.45 &&b>= 0.55 )
	 printf ( "Passed\n");
     else   if (a>= 0.65 &&b<= 0.45 )
	 printf ( "You can reappear in B\n");
     else 
         printf ( "Failed\n");
return 0;
}
