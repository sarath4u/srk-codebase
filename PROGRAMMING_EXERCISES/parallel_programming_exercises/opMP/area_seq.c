// Area under the curve 4/1+x^2 between 0 and 1
#include <stdio.h>
static long num_steps = 100000;
void main(){
	double sum = 0.0;
	double x_lim = 1.0;
	double dx = x_lim / num_steps;
	double x = 0;
	for (int i = 0; i < num_steps; i++){
		x = i * dx;
		sum +=  4.0 / (1.0 + x * x);
	}
	printf("pi = %f\n", dx * sum);
}

