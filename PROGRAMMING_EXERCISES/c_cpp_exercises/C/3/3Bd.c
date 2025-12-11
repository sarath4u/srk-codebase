/*program to print all the ASCII values and their equivalent characters*/
/*sarath 22.09.14*/
#include <stdio.h>
int main()
{
int  i= 0 ;
     char  C;
     while (i<= 255 )
	{
        C=i;
        i++;
         printf ( "The ASCII value of %c is %d\n" ,C,i);
	}
return 0;
}
