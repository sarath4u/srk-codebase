#include <stdio.h>

int main(int argc, char* argv[]){

int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int search = 6, i;
int flag = 1;
for (i = 0; i < 10; i++){
	if (arr[i] == search){
		printf("Number %d found at index %d\n", search, i);
		flag = 0;
		break;
		}
	};
if (flag) printf("Number %d is not in the array\n", search);
};
