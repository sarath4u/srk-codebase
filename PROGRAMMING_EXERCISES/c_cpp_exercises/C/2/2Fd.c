/*program to find the grade of steel*/
/*sarath 13.09.14*/
#include <stdio.h>
int main()
{
    int  hard,ts;
     float  carb;
     printf ( "Enter hardness value: \n");
     scanf ( "%d" ,&hard);
     printf ( "Enter carbon content: \n");
     scanf ( "%f" ,&carb);
     printf ( "Enter Tensile strength: \n");
     scanf ( "%d" ,&ts);
     /*formula*/ 
     if (hard> 50 &&carb< 0.7 &&ts> 5600 )
         printf ( "Grade of the steel is 10\n");
     else   if (hard> 50 &&carb< 0.7 &&ts<= 5600 )
	 printf ( "Grade of steel is 9\n");
     else   if (hard<= 50 &&carb< 0.7 &&ts> 5600 )
	 printf ( "Grade of the steel is 8\n");
     else   if (hard> 50 &&carb>= 0.7 &&ts> 5600 )
	 printf ( "Grade of the steel is 7\n");
     else   if ((hard<= 50 &&carb>= 0.7 &&ts> 5600 )||(hard<= 50 &&carb>= 0.7 &&ts> 5600 )||(hard> 50 &&carb>= 0.7 &&ts<= 5600 ))
     printf ( "Grade of the steel is 6\n");
     else 
             printf ( "Grade of the steel is 5\n");
return 0;
}
