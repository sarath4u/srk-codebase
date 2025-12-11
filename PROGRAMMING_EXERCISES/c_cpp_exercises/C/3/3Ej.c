//  Created by SARATH R on 26/09/14.
//PROGRAM FUN2
#include <stdio.h>
int main()
{
  int i = 1, one = 1, j, k, a=0, b, sum=0;

  for (i = 1; i <= 5; i++)
  {
    for (j = 1; j <5 - i + 1; j++)
      printf(" ");
    for (j = 5-i+1; j <=5+i-1; j++)
      if ((j-i)%2 == 0)
      {
        if (j == 5)
        {
          sum += 1+a;
          printf("%d", sum);
        }
        else if ((i == 4) & (j < 7) & (j > 3))
        { 
          a = sum + 1;
          printf("%d", a);
        }
        else if ((i == 5) & ((j == 3) | (j == 7)))
          printf("%d", a+1);
        else
          printf("%d", 1);
      }
      else
        printf(" ");
      
    for (j = 5+i; j <= 9; j++)
      printf(" ");
    printf("\n");
  }
return 0;
}
