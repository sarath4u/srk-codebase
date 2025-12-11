//  Created by SARATH R on 26/09/14. 
//  FUNCTION THAT RECEIVES FIVE INTIGERS THAT RETURNS SUM, AVERAGE AND STANDARD DEVIATION 
#include <math.h> 
#include <stdio.h>
 int main()
{
     int  *i, count;
     float  sm =  0 , av=0, std=0;
     float  average( float ,  int );
     float  sd( float , float, int,  int *);
     float  adds( int *,  float ,  int );
     printf ( "Enter five intigers\n" );
     for  (count =  0 ; count<= 4 ; count ++)
    {
         scanf ( "%d" ,i+count);
        sm =  adds (i+count, sm, count);
         if  (count ==  4 )
        {
            av =  average (sm,count);
        }
        std =  sd (std, av, count, i+count);
    }
     return 0;
}
float adds( int  *i,  float  sm,  int  count)
{
    sm = sm + *i;
     if  (count ==  4 )
    {
         printf ( "Sum = %f" , sm);
    }
     return  sm;
}
 float  average ( float  sm,  int  count)
{
     float  avg = sm/(count+ 1 );
     printf ( "\nAverage = %f" , avg);
     return  avg;
}
 float  sd( float std, float avg, int count, int *i)
{
  std = std + *i * *i;
  if (count == 4)
  {
    std = pow((std / (count + 1)) - avg*avg, 0.5);
    printf("\nStandard Deviation = %f\n", std);
  }
  return std;
}


