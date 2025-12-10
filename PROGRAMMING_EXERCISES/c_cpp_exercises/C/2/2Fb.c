/*program to check whether the character entered is a capital letter, a small letter, digit or special symbol*/
/*sarath 13.09.14*/
#include <stdio.h>
int main()
{
     char  x;
     printf ( "Enter the character\n" );
     scanf ( "%c" ,&x);
     /*formula*/ 
     if (x>= 0 &&x<= 9 )
    {
         printf ( "Upper case letter\n" );
    }
     else   if (x>= 97 &&x<= 122 )
         printf ( "Lower case letter\n" );
     else   if (x>= 48 &&x<= 57 )
         printf ( "single digit\n" );
     else 
         printf ( "Special symbols\n" );
return 0;
}
