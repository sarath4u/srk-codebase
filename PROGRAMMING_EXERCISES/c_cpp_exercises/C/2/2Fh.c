/*program to find efficiency of workers*/
/*sarath 19.09.14*/
#include <stdio.h>
int main()
{
  int  a;
     printf ( "Enter the no of hours\n");
     scanf ( "%d" ,&a);
     /*formula*/ 
     if (a>= 2 &&a<= 3 )
         printf ( "Highly efficient\n");
     else   if (a>= 3 &&a<= 4 )
	 printf ( "You have to improve speed\n");
     else   if (a>= 4 &&a<= 5 )
	 printf ( "You have to attend the training\n");
     else 
         printf ( "You are fired\n");
return 0;
}
