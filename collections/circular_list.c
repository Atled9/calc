#include <stdlib.h>

typedef struct Node {
	void *data;
	struct Node *next;
} Node;

typedef struct {
	Node *tail;
} List;

List *initList(void)
{
	List *list = (List *)malloc(sizeof(List));
	list->tail = NULL;

	return list;
}
void freeList(List *list)
{
	if (!list->tail) {
		free(list);
		return;
	}
	Node *current = list->tail;
	Node *temp = NULL;
	do {
		temp = current;
		current = current->next;
		free(temp->data);
		free(temp);
	} while (current != list->tail);

	free(list);
}

void *getdata(List *list)
{
	if (!list->tail)
		return NULL;
	
	return list->tail->next->data;
}

void inserthead(List *list, void *data)
{
	Node *newnode = (Node *)malloc(sizeof(Node));
	newnode->data = data;

	if (!list->tail) {
		list->tail = newnode;
		newnode->next = newnode;
		return;
	}
	newnode->next = list->tail->next;
	list->tail->next = newnode;
}
void inserttail(List *list, void *data)
{
	Node *newnode = (Node *)malloc(sizeof(Node));
	newnode->data = data;

	if (!list->tail) {
		list->tail = newnode;
		newnode->next = newnode;
		return;
	}
	newnode->next = list->tail->next;
	list->tail->next = newnode;
	list->tail = newnode;
}

void *removehead(List *list)
{
	if (!list->tail) {
		return NULL;
	}
	Node *temp = list->tail->next;
	void *data = list->tail->next->data;

	if (temp == list->tail)
	{
		list->tail = NULL;
		free(temp);
		return data;
	}
	list->tail->next = list->tail->next->next;
	free(temp);
	return data;
}
/*void *removetail(List *list)
{
	if (!list->tail) {
		return NULL;
	}
	Node *temp = list->tail;
	void *data = list->tail->data;

	if (temp == list->tail->next) {
		list->tail = NULL;
		free(temp);
		return data;
	}
	Node *current = list->tail->next;

	while (current->next != list->tail)
		current = current->next;
	
	current->next = list->tail->next;
	list->tail = current;
	return data;
	free(temp);
}*/
