#include "PrimeThreads.h"

void crossout(int k){
	int i;
	for (i = 3; i*k <= n; i+=2){
		prime[i*k] = 0;
	}
}

void *worker(int tn){
	int lim, base, work = 0;
	lim = sqrt(n);
	do {
		pthread_mutex_lock(&nextbaselock);
		base = nextbase;
		nextbase += 2;
		pthread_mutex_unlock(&nextbaselock);
		if (base <= lim) {
			if (prime[base]) {
				crossout(base);
				work++;
			}
		}
		else return work;
	} while (1);
}
