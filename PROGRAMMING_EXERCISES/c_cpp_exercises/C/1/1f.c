/*program to interchange to numbers*/
/*sarath 23.08.14*/
#include <stdio.h>
int main()
{
int A,B, c, d;
printf("Enter first no.: ");
scanf("%d",&A);
printf("Enter second no.: ");
scanf("%d",&B);
c=A;
d=B;
A=d;
B=c;
printf("A=%d\nB=%d\n",A,B);
return 0;
}
