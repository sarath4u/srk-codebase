/*program to check a person can be insured*/
/*sarath 13.09.14*/
#include <stdio.h>
int main()
{
  char  health,res,gen;
  int  age;
  printf("Enter gender(M/F): ");
  scanf(" %c" ,&gen);
  printf("Enter age: ");
  scanf("%d" ,&age);
  printf("Whether reside in a city(Y/N): ");
  scanf(" %c" ,&res);
  printf("Enter health status(E-Excellent/P-Poor): ");
  scanf(" %c" ,&health);
  /*formula*/ 
  if (gen== 'M' &&(age>= 25 &&age<= 35 )&&res== 'Y' &&health== 'E')
    printf ("Premium 4 per thousand and policy amount cannot exceed two lakhs\n");
  else   if (gen== 'F' &&(age>= 25 &&age<= 35 )&&res== 'Y' &&health== 'E')
    printf ("Premium 3 per thousand and policy amount cannot exceed one lakh\n");
  else   if (gen== 'M' &&(age>= 25 &&age<= 35 )&&res== 'N' &&health== 'P')
    printf ("Premium 6 per thousand and policy amount cannot exceed ten thousand\n");
  else 
    printf ("cannot be insured,sorry\n");
  return 0;
}
