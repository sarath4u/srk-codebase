//  Created by SARATH R on 26/09/14. 
//  Number of occurances of a number in a list of numbers 
#include <stdio.h>
int main()
{
    int i, data[25], j = 0, num;
    printf("Enter 25 Numbers\n");
    for (i = 0; i < 25; i++)
    {
        scanf("%d", &data[i]);
    }
    printf("Enter the number to be searched\n");
    scanf("%d", &num);
    for (i = 0; i < 25; i++)
    {
        if (num == data[i])
        {
            j++;
        }
    }
    printf("The number searched appears %d times in the array\n", j);
}
