#include <stdlib.h>
#include "circular_list.h"

typedef struct {
	List *list;
	void (*nsrt)(List *, void *);
	void *(*rmve)(List *);
} Collection;

Collection *initStack(void)
{
	Collection *stack = (Collection *)malloc(sizeof(Collection));
	stack->list = initList();

	stack->nsrt = inserthead;
	stack->rmve = removehead;

	return stack;
}
Collection *initQueue(void)
{
	Collection *queue = (Collection *)malloc(sizeof(Collection));
	queue->list = initList();

	queue->nsrt = inserttail;
	queue->rmve = removehead;

	return queue;
}
void freeCollection(Collection *collection)
{
	freeList(collection->list);
	free(collection);
}

void *peek(Collection *collection)
{
	return getdata(collection->list);
}

void insertion(Collection *collection, void *data)
{
	collection->nsrt(collection->list, data);
}
void (*push)(Collection *, void *) = insertion;
void (*enqueue)(Collection *, void *) = insertion;

void *removal(Collection *collection)
{
	return collection->rmve(collection->list);
}
void *(*pop)(Collection *) = removal;
void *(*dequeue)(Collection *) = removal;

