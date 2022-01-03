#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct q_node {
	int data;
	struct q_node *next;
} Qnode;

typedef struct queue {
	Qnode *head, *tail;
} Queue;

Qnode *newNode(int data)
{
	Qnode *ptr = (Qnode*)malloc(sizeof(Qnode));
	if (!ptr)
		return NULL;
	ptr->data = data;
	ptr->next = NULL;
	return ptr;
}

Queue *newQueue()
{
	Queue *qPtr = (Queue*)malloc(sizeof(Queue));
	if (!qPtr)
		return NULL;
	qPtr->head=NULL;
	qPtr->tail=NULL;
	return qPtr;
}

int isEmpty(Queue *q)
{
	if (!q)
		return -1;
	return (q->tail==NULL);
}

int enqueue(Queue *q, int data)
{
	if (!q)
		return 0;
	if (isEmpty(q)) {
		if (!(q->head = q->tail = newNode(data)))
			return 0;
		return data;
	}
	if (!(q->tail->next = newNode(data)))
		return 0;
	q->tail = q->tail->next;
	return data;
}

int addFront(Queue *q, int data)
{
	Qnode *temp;
	if (!q)
		return 0;
	if (isEmpty(q)) {
		return enqueue(q, data);
	}
	if (!(temp = newNode(data)))
		return 0;
	temp->next = q->head;
	q->head = temp;
	return data;
}

int dequeue(Queue *q)
{
	Qnode *temp;
	int tempData;
	if (isEmpty(q))
		return 0;
	temp = q->head;
	tempData = q->head->data;
	if (!(q->head = q->head->next))
		q->tail = NULL;
	free(temp);
	return tempData;
}

int main(int argc, char **argv)
{
	const char sequence[] = "101010";
	const size_t seqLen = strlen(sequence);
	int c, i=0;
	size_t size=1;
	Queue *q = newQueue();
	Qnode *ptr;
	
	while (size<=seqLen && (c=getchar())!=EOF) {
		enqueue(q, c);
		size++;
	}
	
	if (size<=seqLen)
		return EXIT_FAILURE;

	for (i=0; i<seqLen-1; i++)
		printf("0");

	do {
		ptr = q->head;
		while (ptr!=NULL && ptr->data == sequence[i]) {
			ptr = ptr->next;
			i++;
		}
		if (!ptr)
			printf("1");
		else
			printf("0");
		ptr=NULL;
		i=0;
	} while (((c=getchar())=='0' || c=='1') && dequeue(q) && enqueue(q, c));
	printf("\n");

	return 0;
}