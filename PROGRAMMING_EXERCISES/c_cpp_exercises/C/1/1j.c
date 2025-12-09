/*program to find the no of illiterate men and women in a village*/
/*sarath 24.08.14*/
#include <stdio.h>
int main()
{
int  n,m,w,l,lm,lw,im,iw;
printf ( "Enter total no.of people: " );
scanf ( "%d" ,&n);
/*formula*/ 
/*total no of men*/ 
m=n* 52 / 100 ;
/*total no of women*/ 
w=n-m;
/*no of literate people*/ 
l=n* 48 / 100 ;
/*no of literate men*/ 
lm=m* 35 / 100 ;
/*no of literate women*/ 
lw=l-lm;
/*total no of illiterate men*/ 
im=m-lm;
/*total no of illiterate women*/ 
iw=w-lw;
printf ( "Total no of illiterate men and women are %d and %d\n" ,im,iw);
return 0;
}
