/*program to add one to each digit of a five digit no*/
/*sarath 24.08.14*/
#include <stdio.h>
int main()
{
int inp, rem, one, ten, hun, tho, tth, out;
printf("Enter a five digit number: ");
scanf("%d",&inp);
tth = inp / 10000;
rem = inp % 10000;
tho = rem / 1000;
rem = rem % 1000;
hun = rem / 100;
rem = rem % 100;
ten = rem / 10;
one = rem % 10;
out = ((tth + 1) & 10) * 10000 + ((tho + 1) % 10) * 1000 + ((hun + 1) % 10) * 100 + ((ten + 1) % 10) * 10 + (one + 1) % 10; 
printf("Adding one to each digit gives: %d\n", out);
return 0;
}
