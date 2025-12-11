#include <stdio.h>
int main()
{
     int i,z= 0 ,p= 0 ,m= 0 ;
     char cont= 'Y' ;
     while  (cont== 'Y' )
    {
         printf ("Enter number\n");
         scanf ("%d" ,&i);
         if  (i== 0 )
            z++;
         else   if  (i> 0 )
            p++;
         else 
            m++;
         printf ( "To continue press Y, else press N\n" );
         scanf ( " %c" ,&cont); /*ENTERING <TAB> BEFORE %c HELPED EXECUTE THE CODE WITHOUT ERRORS!!!!*/ 
    }
         printf  (  "No of Zeros=%d\n" ,z);
         printf  (  "No of positive intigers=%d\n" ,p);
         printf  (  "No of negetive intigers=%d\n" ,m);
      printf ( "%c\n" ,cont);
return 0;
}
