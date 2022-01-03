#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_N 1000000
#define MIN_N 1
#define MIN_DISK_SIZE 1

#define skipToNextLine()\
	{\
		int c;\
		while ((c=getchar())!=EOF && c!='\n');\
	}


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

int main (int argc, char **argv)
{
	int N, max, day, disk, i;
	Queue *tower = newQueue();
	if (!tower)
		return EXIT_FAILURE;
	/* scan the first line and save to N */
	if (scanf("%d", &N)!=1 || N<MIN_N || N>MAX_N)
		return EXIT_FAILURE;
	skipToNextLine();
	if (feof(stdin))
		return EXIT_FAILURE;
		max = N;
	for (i=0, day=1; day<=N; i++, day++) {
		if (scanf("%d", &disk)!=1 || disk<MIN_DISK_SIZE || disk>N)
			return EXIT_FAILURE;
		addFront(tower, disk);
		if (disk == max){
			max = (isEmpty(tower)) ? disk-1: tower->tail->data-1;
			while (!isEmpty(tower))
				printf("%d ", dequeue(tower));
		}
		printf("\n");
	}
	return 0;
}