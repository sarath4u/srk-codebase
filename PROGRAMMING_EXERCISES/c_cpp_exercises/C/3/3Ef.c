//  Created by SARATH R on 26/09/14. 
// PROGRAM TO PRINT THE FOLLOWING PATTERN:
// A B C D E F G F E D C B A
// A B C D E F   F E D C B A
// A B C D E       E D C B A
// A B C D           D C B A
// A B C               C B A
// A B                   B A
// A                       A

#include <stdio.h>
int main()
  {
  char  c= 'A' ;
  int  i,j,k;
  for (j= 6 ;j>= 0 ;j--)
    {
      printf ( "\n" );
      for  (i= 'A' ; i<= 'A' +j;i++)
        {
        c=i;
        printf ( "%c " ,c);
        }
      for  (k= 0 ; k< 4*(6 -j)-2;k++)
        {
        printf (" ");
        }
      for  (i=c ; i>= 'A' ;i--)
        {
          if (i == 'G') continue;
        c=i;
        printf ( "%c " ,c);
        }
    }
    printf("\n\n");
  return 0;
  }
