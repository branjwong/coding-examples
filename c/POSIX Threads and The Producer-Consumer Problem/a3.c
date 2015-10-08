#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX 10000000000			/* Numbers to produce */
#define MAX_BUFFER_SIZE 10
#define EMPTY 0
#define FULL 1
pthread_mutex_t the_mutex;
sem_t pro, con;
int inputBuffer[MAX_BUFFER_SIZE];
int bFront;
int bCount;

void produce();
void consume();

void* producer(void *ptr) {
	int i;

	for (i = 1; i < MAX; i++) {
		sem_wait(&pro);
		pthread_mutex_lock(&the_mutex);
		produce();
		pthread_mutex_unlock(&the_mutex);
		sem_post(&con);
	}
	pthread_exit(0);
}

void* consumer(void *ptr) {
	int i;

	for (i = 1; i < MAX; i++) {
		sem_wait(&con);
		pthread_mutex_lock(&the_mutex);
		consume();
		pthread_mutex_unlock(&the_mutex);
		sem_post(&pro);
	}
	pthread_exit(0);
}

void produce() {
	int bBack = (bFront + bCount) % MAX_BUFFER_SIZE;
	inputBuffer[bBack] = FULL;
	bCount++;
}

void consume() {
	inputBuffer[bFront] = EMPTY;
	bFront = (bFront + 1) % MAX_BUFFER_SIZE;
	bCount--;
}

int main (int argc, char **argc) {
	pthread_t pro[NUM_PRODUCERS], con[NUM_CONSUMERS];

	// Initialize the mutex and semaphore variables
	pthread_mutex_init(&the_mutex, NULL);	
	sem_init(&pro, 0, MAX_BUFFER_SIZE);
	sem_init(&con, 0, 0);

	bFront = 0;	
	bCount = 0;
	
	// Create the threads
	for (i=0; i<NUM_PRODUCERS; i++) {
		pthread_create(&pro[i], NULL, producer, NULL);
	}
	for (i=0; i<NUM_CONSUMERS; i++) {
		pthread_create(&con[i], NULL, consumer, NULL);
	}
	
	// Wait for the threads to finish
	for (i=0; i<NUM_GENERATORS; i++) {
		pthread_join(gen[i], NULL);
	}
	for (i=0; i<NUM_OPERATORS; i++) {
		pthread_join(oper[i], NULL);
	}

	// Cleanup
	pthread_mutex_destroy(&the_mutex);	/* Free up the_mutex */
	sem_destroy(&pro);
	sem_destroy(&con);
}
