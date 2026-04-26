#ifndef LIST
#define LIST

typedef struct List List;

List *initList(void);
void freeList(List *list);

void *getdata(List *list);

void inserthead(List *list, void *data);
void inserttail(List *list, void *data);

void *removehead(List *list);
void *removetail(List *list);


#endif
