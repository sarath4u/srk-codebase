/*program to add the sum of the digits of a five digit no*/
/*sarath 23.08.14*/
#include <stdio.h>
int main()
{
int n,s,rfi,rfo,rt,rse,fi,fo,t,se;
printf( "Enter a five digit no.\n");
scanf( "%d",&n);
/*formula*/ 
rfi=n%10000 ;
rfo=rfi%1000 ;
rt=rfo%100 ;
rse=rt%10 ;
fi=n/10000 ;
fo=rfi/1000 ;
t=rfo/100 ;
se=rt/10 ;
s=fi+fo+t+se+rse;
printf("%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n" ,rfi,rfo,rt,rse,fi,fo,t,se);
printf("The sum of the digits =%d\n" ,s);
return 0;
}
