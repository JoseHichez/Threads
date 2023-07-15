/*
Jose Hichez
PID: 6186740
I affirm that I wrote this program myself without any help from the internet or any other people or sources

This C program uses 8 threads to increment a shared variable. Each thread loops 10 times, incrementing the shared variable by its Thread ID in every
iteration of the loop.  

*/

//starts program
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//defining number of threads
#define NUM_THREADS 8  
//create thread argument struct for thr_func()
typedef struct _thread_data_t {
	int tid;
	double stuff;
}thread_data_t;
//shared data between threads
double shared_x;
pthread_mutex_t lock_x;

void *thr_func(void *arg) {
	thread_data_t *data = (thread_data_t *)arg;

	printf("Thread %d has finished.\n", data->tid);//print that the threads have finished 
	//get mutex before modifying and printing 
	pthread_mutex_lock(&lock_x);
	//start loop
	for(int i =0; i<10; i++){
	
		shared_x += data->tid;
	}
	pthread_mutex_unlock(&lock_x);

	pthread_exit(NULL);

}

int main (int argc, char **argv) {
	pthread_t thr[NUM_THREADS];
	int i, rc;
	//create a thread_data_t argument array
	thread_data_t thr_data[NUM_THREADS];
	//initialize shared data
	shared_x =0;
	/*initialize pthread mutex protecting "shared_x"*/
	pthread_mutex_init(&lock_x, NULL);
	//create threads
	for (i = 0; i < NUM_THREADS; ++i) {
		thr_data[i].tid = i;
		thr_data[i].stuff = (i + 1) * NUM_THREADS ;
		if ((rc = pthread_create(&thr[i], NULL, thr_func, &thr_data[i]))) {
			fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
			return EXIT_FAILURE;
		}
	}
	//block until all threads are complete
	for (i = 0; i < NUM_THREADS; ++i) {
		pthread_join(thr[i], NULL);
	}
	printf("x = %f\n", shared_x);//print output
	return EXIT_SUCCESS;//exit program
}

