 //  Created by SARATH R on 26/09/14. 
 //  Finding leap year using function 
 #include  <stdio.h> 
 int main ()
{
     int  year;
     int leapYear(int);
     printf ( "Enter year: ");
     scanf ( "%d" ,&year);
    leapYear(year);
return 0;
}
int leapYear( int  yr)
{
     if (yr %  4  ==  0  && yr %  100  !=  0 )
         printf ( "leap year\n");
     else 
         printf ( "not  a leap year\n");
     return   0 ;
}
