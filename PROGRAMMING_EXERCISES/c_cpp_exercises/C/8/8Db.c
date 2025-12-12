//  Created by SARATH R on 26/09/14.
//  Finding positive or negative or odd or even
#include <stdio.h>
int main()
{
    int i, data[25], pos = 0, num, neg = 0, evn = 0, odd = 0;
    printf("Enter 25 Numbers\n");
    for (i = 0; i < 25; i++)
    {
        scanf("%d", &data[i]);
    }
    for (i = 0; i < 25; i++)
    {
        if (data[i] > 0)
            pos++;
        else if (data[i] < 0)
            neg++;
        if (data[i] % 2 == 0 && data[i] !=0)
            evn++;
        else if (data[i] % 2 != 0)
            odd++;
    }
    printf("Number of Positive intigers = %d\n", pos);
    printf("Number of Negetive intigers = %d\n", neg);
    printf("Number of even intigers = %d\n", evn);
    printf("Number of odd intigers = %d\n", odd);
    return 0;
}
