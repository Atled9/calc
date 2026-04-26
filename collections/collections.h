#ifndef COLLECTION
#define COLLECTION

typedef struct Collection Collection;

Collection *initStack(void);
Collection *initQueue(void);
void freeCollection(Collection *collection);

void *peek(Collection *collection);

void insertion(Collection *, void *data);
extern void (*push)(Collection *, void *);
extern void (*enqueue)(Collection *, void *);

void *removal(Collection *);
extern void *(*pop)(Collection *);
extern void *(*dequeue)(Collection *);

#endif
