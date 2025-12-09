/*program to reverse the digits of a five digit no*/
/*sarath 23.08.14*/
#include <stdio.h>
int main()
{
int  n,rev,rfi,rfo,rt,rse,fi,fo,t,se;
printf ( "Enter a five digit number: " );
scanf ( "%d" ,&n);
/*formula*/ 
rfi=n% 10000 ;
rfo=rfi% 1000 ;
rt=rfo% 100 ;
rse=rt% 10 ;
fi=n/ 10000 ;
fo=rfi/ 1000 ;
t=rfo/ 100 ;
se=rt/ 10 ;
rev=fi+ 10 *fo+ 100 *t+ 1000 *se+ 10000 *rse;
printf ( "The reversed number: %d\n" ,rev);
return 0;
}
