/*program to reverse a number a five digit no and check if they are equal*/
/*sarath 02.09.14*/
#include <stdio.h>
int main()
{
  int  n,r,fi,fir,fo,four,t,tr,s,sr;
  printf ( "Enter the five digit no: " );
  scanf ( "%d" ,&n);
  /*formula*/ 
  fi=n/ 10000 ;
  fir=n% 10000 ;
  fo=fir/ 1000 ;
  four=fir% 1000 ;
  t=four/ 100 ;
  tr=four% 100 ;
  s=tr/ 10 ;
  sr=tr% 10 ;
  r=sr* 10000 +s* 1000 +t* 100 +fo* 10 +fi;
  if (r==n)
    printf ( "surprise,numeric palindrome\n" );
  else 
    printf ( "reversed no is %d\n" ,r);
  return 0;
}
