//  Created by SARATH R on 26/09/14. 
//  FUNCTION TO CIIRCULARLY SHIFT THREE NUMBERS. 
#include <stdio.h>
int main()
{
  int  a, b, c;
  int circshift(int, int, int);
  printf ( "Enter three numbers\n" );
  scanf ( "%d%d%d" ,&a, &b, &c);
  circshift (a,b,c);
return 0;
}
int circshift( int  a,  int  b,  int  c)
{
  int e, d;
  for (int i=0; i<3; i++)
  {
    printf ( "a = %d, b = %d, c = %d\n" ,a, b, c);
    e = a;
    d = b;
    a = c;
    b = e;
    c = d; 
  }
  return   0 ;
}
