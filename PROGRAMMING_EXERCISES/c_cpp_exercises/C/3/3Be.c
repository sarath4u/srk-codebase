/*program to print all the Armstrong Numbers between 1 and 500*/
/*sarath 23.09.14*/
#include <stdio.h>
int main()
{
     int  i= 1 ,h,rh,t,rt,armnum;
     while (i<= 500 )
	{
        h=i/ 100 ;
        rh=i% 100 ;
        t=rh/ 10 ;
        rt=rh% 10 ;
        armnum=rt*rt*rt+t*t*t+h*h*h;
		 if (armnum==i)
             printf ( "%d\n" ,armnum);
        i++;
	}
return 0;
}
