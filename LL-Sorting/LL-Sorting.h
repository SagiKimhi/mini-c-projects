#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct list {
	int val;
	struct list *next;
} LIST;

typedef enum bool {
	FALSE,
	TRUE
} Bool;

LIST *newElement(int val);
LIST *deleteElement(LIST *head, LIST *element);
LIST *deleteList(LIST *head);
LIST *removeVal(LIST *head, int val);
LIST *addFront(LIST *head, LIST *newp);
LIST *addEnd(LIST *tail, LIST *newp);
LIST *addmiddle (LIST *head, LIST *newp);
LIST *mergeSort(LIST *node);
LIST *split(LIST *node);
LIST *merge(LIST *node1, LIST *node2);
int listLen(LIST *head);
void printList(LIST *head);