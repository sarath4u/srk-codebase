// Area under the curve 4/1+x^2 between 0 and 1
#include <omp.h>
#include <stdio.h>
#define PAD 8 // assuming 64 byte L1 cache line size
#define NUM_THREADS 5
static long num_steps = 100000;
void main(){
	int nthreads; 
//	double sum[NUM_THREADS];
	double sum[NUM_THREADS][PAD];
	double pi = 0.0, x_lim = 1.0;
	double dx = x_lim / num_steps;
	double st = omp_get_wtime();
	omp_set_num_threads(NUM_THREADS);
	#pragma omp parallel
	{
		double x = 0;
		int ID = omp_get_thread_num();
		int nthrds, i;
		nthrds = omp_get_num_threads();
		if (ID == 0) nthreads = nthrds;		// Just to know the total number of threads allocated
//		for (i = ID, sum[ID]= 0.0; i < num_steps; i += nthrds){
		for (i = ID, sum[ID][0] = 0.0; i < num_steps; i += nthrds){
			x = i * dx;
			sum[ID][0] +=  4.0 / (1.0 + x * x);
		}
	}	
	double et = omp_get_wtime();
	printf("n = %d\t", NUM_THREADS);
	printf("time = %0.6fs\t", et - st);
//	for(int i = 0; i < nthreads; i++)pi = pi + sum[i] * dx;
	for(int i = 0; i < nthreads; i++)pi = pi + sum[i][0] * dx;
	printf("pi = %f\n", pi);
}

