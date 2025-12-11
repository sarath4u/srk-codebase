/*program for a game of matchsticks where computer always wins*/
/*sarath 23.09.14*/
#include <stdio.h>
int main()
{
     int  n= 0 ,sum= 0 ,i= 1 ;
     while (i<= 4 )
	{
         printf ( "Pick at most four sticks\n" );
         scanf ( "%d" ,&n);
        n=(i- 1 )* 5 +n;
        sum=(i* 5 )-n;
         printf ( "computer picks %d\n" ,sum);
        i++;
	}
     printf ( "You lose\n" );  /*whoever picks the last stick loses*/ 
return 0;
}
