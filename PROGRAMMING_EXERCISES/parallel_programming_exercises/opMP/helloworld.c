// hello world
#include<omp.h> 
#include <stdio.h>
int main()
{
	#pragma omp parallel   //give me a bunch of threads or default number of threads
	{
	int ID = omp_get_thread_num();
	printf("hello(%d)", ID);
	printf("world(%d)\n", ID);
	}
}

