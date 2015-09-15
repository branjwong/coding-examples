/*hw2.c
 *Solution to Generator Operator Problem
 *Extended case of the Producer-Consumer Problem
 *Using Ptheads, a mutex and condition variables
 *Brandon J Wong
 */

/*
	There are 3 generators, and each produces
	a unique kind of material independently.
	
	All these materials are stored in an input
	buffer with size 10 before they are
	forwarded to the operators.
	
	We have 3 operators with same priority
	who are responsible for producing the
	products based on these materials.
	
	Each product needs 2 different kinds of
	materials.
	
	Each time an operator needs 2 tools for
	this purpose.
	
	There are 3 tools in total provided for
	these operators.
	
	An operator can only process one product
	at one time.
	
	When an operator gets both the materials
	and tools, he can produce a product within
	a limited time varied from 0.01 second to 1 second. Otherwise, he has to wait until all the
	necessities are met.
	
	He can grab the materials or tools first, it does not matter, but he can only get one thing at
	one time.
	
	If an operator decides to make another product before he starts to make the current
	product , he can put the materials and tools back and re-get the new materials and tools.
	The operator has to put the tools back after he finishes a product because other operators
	may need these tools.
	
	All the products are put into a size-unlimited output queue.
	
	An operator cannot start a new product before he puts the product into the output queue.
	
	Some restrictions may apply to the output queue:
	
		No same products can be next to each other in this queue. We say that two products are
		same if they are made from the same kinds of materials.
		
		The difference of the number of any two kinds of products produced should be less than 10,
		for example, we can have 10 of product A and 15 of product B, but it is not allowed if we
		have 10 of A and 21 of B because the difference is 11 which is larger than 10.
*/

#include <time.h>								// for nanosleep()
#include <stdio.h>
#include <stdlib.h>								// for rand(), abs()
#include <pthread.h>

#define MAX 1000000							
#define MAX_OUTPUT 100
#define MAX_BUFFER_SIZE 10
#define MAX_MATERIAL_COUNT 2
#define MAX_MATERIAL_TYPE 3
#define MAX_PRODUCT_TYPE 6
#define TRUE 1
#define FALSE -1
#define EMPTY 8
#define MAT0 0
#define MAT1 1
#define MAT2 2
#define PROD0 0
#define PROD1 1
#define PROD2 2
#define PROD3 3
#define PROD4 4
#define PROD5 5
#define SLEEP_MIN 1
#define SLEEP_MAX 100
#define NUM_GENERATORS 3
#define NUM_OPERATORS 3
#define tenToTheSeven 10000000

struct operInfo {
	int op_id;
	int mat[MAX_MATERIAL_COUNT];
	int p_toBuild;
};

pthread_mutex_t input_mutex, output_mutex;
pthread_cond_t cond_take, cond_put, cond_prod;

int inputBuffer[MAX_BUFFER_SIZE];
int bCount;
int bMatCount[MAX_MATERIAL_COUNT];		
int outputQueue[MAX_OUTPUT];
int qCount;
int qProdCount[MAX_PRODUCT_TYPE];
int bufMatTooMany[MAX_MATERIAL_COUNT];
int queMatTooMany[MAX_PRODUCT_TYPE];
int prodInProgress[MAX_PRODUCT_TYPE];

int isBufferFull();
int isBufferEmpty();
void generateMaterial(int gen_id);							// shared resource: buffer space
void collectMaterials(struct operInfo *opIn);
void takeMaterial(int i, struct operInfo *opIn);			// shared resource: input buffer material
void takeTool();											// shared resource: tools
int productFunction(int *mat);
void makeProduct(struct operInfo *opIn);
int maxDifference(int *arr, int ele, int size);
int tooManyDetect(int *arrCount, int *arrTooMany, int size, int maxDiff, int id);
int* materialFunction (int p_id);
int searchBuffer(int m_id);
int missingMaterial(int p_id, int m_id);
int pickViableProduct();
int isProductViable(int p_id);


void* generator(void *ptr) {
	int i, gen_id;
	int *id_ptr;
	id_ptr = (int *) ptr;
	gen_id = *id_ptr;	
	for (i = 1; i <= MAX; i++) {
		
		generateMaterial(gen_id);

	}
	pthread_exit(0);
}

void* operator(void *ptr) {
	int i;
	int *id_ptr;
	id_ptr = (int *) ptr;
	struct operInfo operatorInformation;
	struct operInfo *opIn = &operatorInformation;
	opIn->op_id = *id_ptr;	
	opIn->p_toBuild = FALSE;
	
	for (i = 1; i <= MAX; i++) {
	
			opIn->p_toBuild = pickViableProduct();				// pick a viable product to build

			prodInProgress[opIn->p_toBuild]++;					// tell other operators what product it's building
			collectMaterials(opIn);								// collect materials for that product
			// tell operators that materials have been collected?
			// tell operators that it needs tools
			// collect tools
			makeProduct(opIn);									// build product
			// put tools back
			// tell operators that it doesn't need tools any more
			// repeat
			
	}
	pthread_exit(0);
}

int main(int argc, char **argv) {
	int i;
	for(i = 0; i < MAX_BUFFER_SIZE; i++) {
		inputBuffer[i] = EMPTY;
	}
	for(i = 0; i < MAX_OUTPUT; i++) {
		outputQueue[i] = EMPTY;
	}
	bCount = 0;
	qCount = 0;
	
	pthread_t gen[NUM_GENERATORS], oper[NUM_OPERATORS];
	int *threadids[NUM_GENERATORS];
	
	// Initialize the mutex and condition variables
	/* What's the NULL for ??? */
	pthread_mutex_init(&input_mutex, NULL);
	pthread_mutex_init(&output_mutex, NULL);
	pthread_cond_init(&cond_take, NULL);			/* Initialize cond_take condition variable */
	pthread_cond_init(&cond_put, NULL);				/* Initialize cond_put condition variable */
	pthread_cond_init(&cond_prod, NULL); 			/* Initialize cond_prod condition variable */
	
	// Create the threads
	for (i=0; i<NUM_GENERATORS; i++) {
		// pass the type of material for the generator to make
		threadids[i] = (int *)malloc(sizeof(int));
		*threadids[i] = i;
		pthread_create(&gen[i], NULL, generator, (void *)threadids[i]);
		printf("Generator%d created.\n",i);
	}
	//for (i=0; i<1; i++) { 							// to test one operator
	for (i=0; i<NUM_OPERATORS; i++) {
		// pass the operator's id number
		threadids[i] = (int *)malloc(sizeof(int));
		*threadids[i] = i;
		pthread_create(&oper[i], NULL, operator, (void *)threadids[i]);
		printf("Operator%d created.\n",i);
	}
	printf("Debug: All threads created.\n");

	// Wait for the threads to finish
	// Otherwise main might run to the end
	// and kill the entire process when it exits.
	for (i=0; i<NUM_GENERATORS; i++) {
		pthread_join(gen[i], NULL);
	}
	for (i=0; i<NUM_OPERATORS; i++) {
		pthread_join(oper[i], NULL);
	}
	
	// Cleanup -- would happen automatically at end of program
	pthread_mutex_destroy(&input_mutex);			/* Free up input_mutex */
	pthread_mutex_destroy(&output_mutex);			/* Free up output_mutex */
	pthread_cond_destroy(&cond_put);				/* Free up cond_put condition variable */
	pthread_cond_destroy(&cond_take);				/* Free up cond_take condition variable */
	pthread_cond_destroy(&cond_prod);				/* Free up cond_take condition variable */
}

// Generates the Material that corresponds to its id
void generateMaterial(int gen_id) {
	pthread_mutex_lock(&input_mutex);
	while (isBufferFull() == TRUE)
		pthread_cond_wait(&cond_put, &input_mutex);
	
	inputBuffer[bCount] = gen_id;
	bMatCount[gen_id]++;
	
	printf("GEN%d:\tgenMat(%d):\tinBuf[%d] <- %d\t{%d,%d,%d,%d,%d,%d,%d,%d,%d,%d}\t\t\tbMat = {%d,%d,%d}\n", gen_id, bCount, bCount, inputBuffer[bCount], inputBuffer[0], inputBuffer[1], inputBuffer[2], inputBuffer[3], inputBuffer[4], inputBuffer[5], inputBuffer[6], inputBuffer[7], inputBuffer[8], inputBuffer[9], bMatCount[MAT0], bMatCount[MAT1], bMatCount[MAT2]);
	
	bCount++;
	pthread_cond_signal(&cond_put);
	pthread_cond_signal(&cond_take);
	pthread_mutex_unlock(&input_mutex);
}

void takeMaterial(int i, struct operInfo *opIn) {
	int freeHand;
	if (opIn->mat[0] == EMPTY) {
		freeHand = 0;
	}
	else if (opIn->mat[1] == EMPTY) {
		freeHand = 1;
	}
	else {
		printf("ERROR: takeMaterial()\n");
		return;
	}
	opIn->mat[freeHand] = inputBuffer[i];
	bMatCount[inputBuffer[i]]--;
	inputBuffer[i] = EMPTY;

	printf("OPER%d:\ttakeMat(%d):\tmat[%d] <- %d\t{%d,%d,%d,%d,%d,%d,%d,%d,%d,%d}\tmat = {%d,%d}\tbMat = {%d,%d,%d}\n", opIn->op_id, i, freeHand, opIn->mat[freeHand], inputBuffer[0], inputBuffer[1], inputBuffer[2], inputBuffer[3], inputBuffer[4], inputBuffer[5], inputBuffer[6], inputBuffer[7], inputBuffer[8], inputBuffer[9], opIn->mat[0], opIn->mat[1], bMatCount[MAT0], bMatCount[MAT1], bMatCount[MAT2]);
	
	bCount--;
}

void collectMaterials(struct operInfo *opIn) {
	int i;
	int *m_id;
	m_id = materialFunction(opIn->p_toBuild);
	while (opIn->mat[0] != m_id[0] || opIn->mat[0] != m_id[1]) {
		pthread_mutex_lock(&input_mutex);
		while (isBufferEmpty() == TRUE)
			pthread_cond_wait(&cond_take, &input_mutex);
		if (searchBuffer(m_id[0]) != FALSE) {
			i = searchBuffer(m_id[0]);
			takeMaterial(i, opIn);
		}
		else if (searchBuffer(m_id[1]) != FALSE) {
			i = searchBuffer(m_id[1]);
			takeMaterial(i, opIn);
		}
		pthread_cond_signal(&cond_put);
		pthread_cond_signal(&cond_take);
		pthread_mutex_unlock(&input_mutex);
	}
	while (opIn->mat[1] != m_id[0] || opIn->mat[1] != m_id[1]) {
		pthread_mutex_lock(&input_mutex);
		if (searchBuffer(missingMaterial(opIn->p_toBuild, opIn->mat[0])) != FALSE) {
			i = searchBuffer(missingMaterial(opIn->p_toBuild, opIn->mat[0]));
			takeMaterial(i, opIn);
		}
		else if (searchBuffer(missingMaterial(opIn->p_toBuild, opIn->mat[0])) != FALSE) {
			i = searchBuffer(missingMaterial(opIn->p_toBuild, opIn->mat[0]));
			takeMaterial(i, opIn);
		}
		pthread_mutex_unlock(&input_mutex);
	}
}

// make product depending on input
// randomly pick a value to stall for
void makeProduct(struct operInfo *opIn) {
	struct timespec t1;
	t1.tv_nsec = tenToTheSeven*(rand() % 100 + 1);
	t1.tv_sec = 0;
	nanosleep(&t1, NULL);
	
	if (opIn->p_toBuild == FALSE) {
		printf("ERROR: makeProduct()\n");
		return;
	}
	outputQueue[qCount] = opIn->p_toBuild;
	qProdCount[opIn->p_toBuild]++;

	printf("OPER%d:\tmakeProd(%d,%d):\toutQ[%d] <- %d\t{%d,%d,%d,%d,%d,%d,%d,%d,%d,%d}\tmat[] <- {%d,%d}\tbProd = {%d,%d,%d,%d,%d,%d}\n", opIn->op_id, opIn->mat[0], opIn->mat[1], qCount, outputQueue[qCount], inputBuffer[0], inputBuffer[1], inputBuffer[2], inputBuffer[3], inputBuffer[4], inputBuffer[5], inputBuffer[6], inputBuffer[7], inputBuffer[8], inputBuffer[9], EMPTY, EMPTY, qProdCount[PROD0], qProdCount[PROD1], qProdCount[PROD2], qProdCount[PROD3], qProdCount[PROD4], qProdCount[PROD5]);

	opIn->mat[0] = EMPTY;
	opIn->mat[1] = EMPTY;
	opIn->p_toBuild = FALSE;
	qCount++;

}

// gives the maximum difference between arr[ele] and all of the other arr[i]s
int maxDifference(int *arr, int ele, int size) {
	int i;
	int maxDiff = 0;
	for (i = 0; i<size; i++) {
		if (maxDiff < (arr[ele] - arr[i]))
			maxDiff = arr[ele] - arr[i];
	}
	return maxDiff;
}

int pickViableProduct() {
	int i = rand() % MAX_PRODUCT_TYPE;
	int result = EMPTY;
	pthread_mutex_lock(&input_mutex);
	while (result == EMPTY) {
		if (isProductViable(i) == TRUE) {
			return i;
		}
		else {
			i = (i + 1) % MAX_PRODUCT_TYPE;
		}
	}
	pthread_mutex_unlock(&input_mutex);
}

int isProductViable(int p_id) {
	tooManyDetect(qProdCount, queMatTooMany, MAX_PRODUCT_TYPE, 10, p_id);
	if (queMatTooMany[p_id] == TRUE)
		return FALSE;
	else
		return TRUE;
}

int tooManyDetect(int *arrCount, int *arrTooMany, int size, int maxDiff, int id) {
	int i;
	for (i = 0; i<size; i++) {
		if (maxDifference(arrCount, i, size) >= maxDiff)
			arrTooMany[i] = TRUE;
		else
			arrTooMany[i] = FALSE;
	}
	return arrTooMany[id];
}

int searchBuffer(int m_id) {
	int i;
	for (i = 0; i < MAX_BUFFER_SIZE; i++) {
		if (inputBuffer[i] == m_id)
			return i;
	}
	return -1;
}

int isBufferFull() {
	if (bCount == MAX_BUFFER_SIZE)
		return TRUE;
	else
		return FALSE;
}

int isBufferEmpty() {
	if (bCount == EMPTY)
		return TRUE;
	else
		return FALSE;
}

int productFunction (int *mat){
	if (mat[0] == MAT0 && mat[1] == MAT0){
		return PROD0;
	} 
	else if ((mat[0] == MAT0 && mat[1] == MAT1) || (mat[0] == MAT1 && mat[1] == MAT0)){
		return PROD1;
	}
	else if ((mat[0] == MAT0 && mat[1] == MAT2) || (mat[0] == MAT2 && mat[1] == MAT0)){
		return PROD2;
	}
	else if (mat[0] == MAT1 && mat[1] == MAT1){
		return PROD3;
	}
	else if ((mat[0] == MAT1 && mat[1] == MAT2) || (mat[0] == MAT2 && mat[1] == MAT1)){
		return PROD4;
	}
	else if (mat[0] == MAT2 && mat[1] == MAT2){
		return PROD5;
	}
	else {
		return FALSE;
	}

}

int* materialFunction(int p_id) {
	int *m_id;
	if (p_id == PROD0) {
		m_id[0] = MAT0;
		m_id[1] = MAT0;
		return m_id;
	}
	if (p_id == PROD1) {
		m_id[0] = MAT0;
		m_id[1] = MAT1;
		return m_id;
	}
	if (p_id == PROD2) {
		m_id[0] = MAT0;
		m_id[1] = MAT2;
		return m_id;
	}
	if (p_id == PROD3) {
		m_id[0] = MAT1;
		m_id[1] = MAT1;
		return m_id;
	}
	if (p_id == PROD4) {
		m_id[0] = MAT1;
		m_id[1] = MAT2;
		return m_id;
	}
	if (p_id == PROD5) {
		m_id[0] = MAT2;
		m_id[1] = MAT2;
		return m_id;
	}
	else {
		printf("ERROR: materialFunction()\n");
		return 0;
	}
}

int missingMaterial(int p_id, int m_id) {
	if (p_id == PROD0) {
		return MAT0;
	}
	if (p_id == PROD1) {
		if (m_id = MAT0)
			return MAT1;
		else
			return MAT0;
	}
	if (p_id == PROD2) {
		if (m_id = MAT0)
			return MAT2;
		else
			return MAT0;
	}
	if (p_id == PROD3) {
		return MAT1;
	}
	if (p_id == PROD4) {
		if (m_id == MAT1)
			return MAT2;
		else
			return MAT1;
	}
	if (p_id == PROD5) {
		return MAT2;
	}
	else
		return FALSE;
}
