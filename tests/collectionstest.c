#include <stdio.h>
#include <stdlib.h>
#include "../collections/collections.h"

#define TESTSIZE 16

int main()
{
	double *val;
	Collection *stack = initStack();
	Collection *queue = initQueue();

	for (int i = 0; i < TESTSIZE; i++) {
		val = (double *)malloc(sizeof(double));
		*val = i + 1.0;
		push(stack, val);
	}
	for (int i = 0; i < TESTSIZE; i++) {
		printf("%lf ", *(double *)peek(stack));
		printf("%lf ", *(val = (double *)pop(stack)));
		free(val);
	}
	printf("\n");

	printf("\n");

	for (int i = 0; i < TESTSIZE; i++) {
		val = (double *)malloc(sizeof(double));
		*val = i + 1.0;
		enqueue(queue, val);
	}
	for (int i = 0; i < TESTSIZE; i++) {
		printf("%lf ", *(double *)peek(queue));
		printf("%lf ", *(val = (double *)dequeue(queue)));
		free(val);
	}
	printf("\n");

	
	for (int i = 0; i < TESTSIZE; i++) {
		val = (double *)malloc(sizeof(double));
		*val = i + 1.0;
		push(stack, val);
	}

	freeCollection(stack);
	freeCollection(queue);
	return 0;
}
