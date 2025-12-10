/*program to determine the day on 1st January of an input year*/
/*sarath 25.08.14*/
#include <stdio.h>
#include <stdlib.h>
int main()
{
  int inp, anchor, result, leap_days, num_years, num_cents;
  anchor = 1800;
  printf("Enter year: ");
  scanf("%d",&inp);
  num_years = abs(inp - anchor);
  num_cents = num_years / 100;
  leap_days = (num_years / 4) - (num_cents) - ((num_years % 4) == 0 ? 1 : 0) + ((num_cents > 0? 1: 0));
  if (num_years != 0)
    result = (num_years * 365 + leap_days) % 7;
  else
    printf("1st January of %d is Wednesday\n", inp);
  if (inp > anchor)
  {
    if (result == 1)
      printf("1st January of %d is Thursday\n", inp);
    if (result == 2)
      printf("1st January of %d is Friday\n", inp);
    if (result == 3)
      printf("1st January of %d is Saturday\n", inp);
    if (result == 4)
      printf("1st January of %d is Sunday\n", inp);
    if (result == 5)
      printf("1st January of %d is Monday\n", inp);
    if (result == 6)
      printf("1st January of %d is Tuesday\n", inp);
    if (result == 0)
      printf("1st January of %d is Wednesday\n", inp);
  }
  else
  {
    if (result == 1)
      printf("1st January of %d is Tuesday\n", inp);
    if (result == 2)
      printf("1st January of %d is Monday\n", inp);
    if (result == 3)
      printf("1st January of %d is Sunday\n", inp);
    if (result == 4)
      printf("1st January of %d is Saturday\n", inp);
    if (result == 5)
      printf("1st January of %d is Friday\n", inp);
    if (result == 6)
      printf("1st January of %d is Thursday\n", inp);
    if (result == 0)
      printf("1st January of %d is Wednesday\n", inp);
  }
  printf("");
  return 0;
}
