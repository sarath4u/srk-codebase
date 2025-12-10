/*program to find the youngest of three boys*/
/*sarath 08.09.14*/
#include <stdio.h>
int main()
{
int  r,s,a;
     printf ( "Enter the ages of Ram, Syam & Ajay respectively\n" );
     scanf ( "%d%d%d" ,&r,&s,&a);
     /*formula*/ 
     if (r<=s)
    {
         if (r==s)
        {
             if (r<=a)
			{
				 if (r==a)
                {
                     printf ( "All of them are of the same age\n" );
                }
				 else 
                {
                     printf ( "Ram and Syam are the youngest\n" );
                }
			}
             else 
			{
				 printf ( "Ajay is the youngest\n" );
			}
        }
         else   if (r<=a)
        {
             if (r==a)
            {
                 printf ( "Syam and Ajay are the youngest\n" );
            }
             else 
            {
                 printf ( "Ram is the youngest\n" );
            }
        }
         else 
		{
			 printf ( "Ajay is the youngest\n" );
		}
    }
     else   if (s<=a)
	{
		 if (s==a)
        {
             printf ( "Ajay and Syam are the youngest\n" );
        }
		 else 
        {
             printf ( "Syam is the youngest\n" );
        }
    }
     else 
	{
		 printf ( "Ajay is the youngest\n" );
	}
return 0;
}
