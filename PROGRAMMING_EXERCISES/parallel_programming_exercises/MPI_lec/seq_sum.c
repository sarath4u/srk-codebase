#include <stdio.h>

int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

int main(int argc, char* argv[])
{
	int i;
	int sum = 0;

	for ( i = 0; i < 10; i++ )
		sum += arr[i];
 	printf("Sum of the array is %d\n", sum);
}
