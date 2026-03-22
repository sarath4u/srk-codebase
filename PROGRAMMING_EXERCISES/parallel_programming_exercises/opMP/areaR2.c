// Area under the curve 4/1+x^2 between 0 and 1
/*
	typedef enum omp_sched_t{
	omp_sched_static = 1
	omp_sched_dynamic = 2
	omp_sched_guided = 3
	omp_sched_auto = 4
	}omp_sched_t;
*/

#include <omp.h>
#include <stdio.h>
#define NUM_THREADS 4
static long num_steps = 10000000;
void main(){
	int i;
	omp_sched_t kind;
	int chunk;
 	double sum = 0.0;
	double x_lim = 1.0;
	double dx = x_lim / num_steps;
	double st = omp_get_wtime();

//	omp_set_schedule(omp_sched_dynamic, 25000);
//	omp_set_schedule(omp_sched_static, 25000);
	omp_get_schedule(&kind, &chunk);
	printf("%d\t%d\n", kind, chunk);

	#pragma omp parallel
	{
	double x;
	#pragma omp for reduction (+:sum)
//	#pragma schedule(runtime)
	#pragma schedule(auto)
	for (i = 0; i < num_steps; i++){
		x = i * dx;
		sum +=  4.0 / (1.0 + x * x);
		}
	}
	double et = omp_get_wtime();
	printf("n = %d\ttime = %0.6f\tpi = %f\n", NUM_THREADS, et-st, dx * sum);
}

