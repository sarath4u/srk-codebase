#include <stdio.h>
#include <math.h>
#include <pthread.h>

#define MAX_N 1000000000
#define MAX_THREADS 25

int nthreads, n,
	prime[MAX_N+1], 
	nextbase;
pthread_mutex_t nextbaselock = PTHREAD_MUTEX_INITIALIZER;
pthread_t id[MAX_THREADS];

void* worker(int);
void crossout(int);
