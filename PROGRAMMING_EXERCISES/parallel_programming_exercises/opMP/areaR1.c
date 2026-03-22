// Area under the curve 4/1+x^2 between 0 and 1
#include <omp.h>
#include <stdio.h>
#define NUM_THREADS 4 
static long num_steps = 100000;
void main(){
	int nthreads; 
	double pi = 0.0, x_lim = 1.0;
	double dx = x_lim / num_steps;
	double st = omp_get_wtime();
	omp_set_num_threads(NUM_THREADS);
	#pragma omp parallel
	{
		double sum, x = 0;
		int ID = omp_get_thread_num();
		int nthrds, i;
		nthrds = omp_get_num_threads();
		if (ID == 0) nthreads = nthrds;		// Just to know the total number of threads allocated
		for (i = ID, sum = 0.0; i < num_steps; i += nthrds){
			x = i * dx;
			sum +=  4.0 / (1.0 + x * x);
		}
		sum = sum * dx;
// 		wait till each sum is computed
//		#pragma omp barrier
//		#pragma omp atomic
		#pragma omp critical
		pi += sum;
	}	
	double et = omp_get_wtime();
	printf("n = %d\t", NUM_THREADS);
	printf("time = %0.6fs\t", et - st);
	printf("pi = %f\n", pi);
}

