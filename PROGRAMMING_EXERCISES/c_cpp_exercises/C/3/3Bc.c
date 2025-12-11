//  Created by SARATH R on 22/09/14. 
#include  <stdio.h> 
#include  <math.h> 
/* program to raise one number to the power of another*/ 
 int  main()
{
     int  i= 1 ,a,n,p= 1 ;
     printf ( "Enter any number\n" );
     scanf ( "%d" ,&a);
     printf ( "Enter power\n" );
     scanf ( "%d" ,&n);
     while (i<=n)
	{
        p=p*a;
        i++;
	}
     printf ( "%d to the power %d is %d\n" ,a,n,p);
return 0;
}
