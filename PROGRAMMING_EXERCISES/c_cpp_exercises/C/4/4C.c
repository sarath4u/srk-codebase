 //  Created by SARATH R on 26/09/14. 
 //  MENU DRIVEN PROGRAM TO FIND FACTORIAL, PRIME, EVEN 
#include <stdio.h>
#include <stdlib.h>
 int main()
{
     int  fact,i,n,j,rem,prime,num,choice;
     while  ( 1 )
    {
     printf ( "1. Factorial\n" );
     printf ( "2. Prime\n" );
     printf ( "3. Odd/Even\n" );
     printf ( "4. Exit\n" );
     printf ( "Your choice?\n" );
     scanf ( "%d" , &choice);
     switch  (choice)
    {
         case   1 :
             printf ( "Enter any no: " );
             scanf ( "%d" ,&fact);
            n=fact;
             for  (i=fact;i> 1 ;i--)
                fact=(i- 1 )*fact;
             printf ( "Factorial of %d is: %d\n" ,n,fact);
             break ;
        
         case   2 :
             printf ( "Enter any number: " );
             scanf ( "%d" ,&prime);
             j= 2 ;
             while (j<prime- 1 )
            {
                rem=prime%j;
                 if  (rem== 0 )
                     break ;
                j++;
            }
             if  ((j==prime- 1 )|| (prime ==  1 ) || (prime ==  2 ))
                 printf ( "%d is a prime number\n" ,prime);
             else 
                 printf ( "%d is a not a prime number\n" ,prime);
              break ;
            
         case   3 :
             printf ( "Enter a number: " );
             scanf ( "%d" ,&num);
             if  (num% 2 == 0 )
                 printf ( "num is an even number\n" );
             else 
                 printf ( "num is an odd number\n" );
             break ;
         case   4 :
             exit ( 0 );
    }
    }
}
