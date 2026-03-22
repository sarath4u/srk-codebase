#include "PrimeThreads.h"
#include "pthread.h"
#include "math.h"
#include "stdio.h"
main(int argc, char **argv)
{	int nprimes, i, work;
	n = atoi(argv[1]);
	nthreads = atoi(argv[2]);
	for (i = 3; i <=n; i++){
		if (i%2 == 0) prime[i] = 0;
		else prime[i] = 1;
	}
	nextbase = 3;
	for (i = 0; i < nthreads; i++) {
		pthreads_create(&id[i], NULL, worker, i);
	}
	for (i = 0; i < nthreads; i++) {
		pthreads_join(id[i], &work);
		printf("%d values of base done\n", work);
	}
	nprimes = 1;
	for (i = 3; i <= n; i++)
		if (prime[i]) {
			nprimes++;
		}
	printf("the number of primes found was %d\n", nprimes); 
}
