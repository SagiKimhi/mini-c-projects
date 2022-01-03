#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SEQ_TO_FIND 1000

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
		return 1;
	}
	if (!(q->tail->next = newNode(data)))
		return 0;
	q->tail = q->tail->next;
	return 1;
}

int dequeue(Queue *q)
{
	Qnode *temp;
	if (isEmpty(q))
		return 0;
	temp = q->head;
	if (!(q->head = q->head->next))
		q->tail = NULL;
	free(temp);
	return 1;
}

int main(int argc, char **argv)
{
	Queue *q = newQueue();
	Qnode *ptr;
	size_t seqLen, size=1;
	char sequence[MAX_SEQ_TO_FIND+1];
	int c=0, i=0;
	
	printf("\nPlease enter the sequence which you wish to find (up to %d characters):\n", MAX_SEQ_TO_FIND);
	while (!isspace((c=getchar()))) {
		if (c==EOF) {
			printf("Error! reached end of file.");
			return EXIT_FAILURE;
		}
		if (i>=MAX_SEQ_TO_FIND)
			break;
		sequence[i++] = c;
	}
	sequence[i] = '\0';
	seqLen = strlen(sequence);

	printf("\nEnter your stream to scan (program will stop at end of stream):\n");

	while (size<=seqLen && (c=getchar())!=EOF) {
		enqueue(q, c);
		size++;
	}
	
	if (size<=seqLen) {
		printf("Error: stream is smaller than the actual sequence.");
		return EXIT_FAILURE;
	}

	for (i=0; i<seqLen-1; i++)
		printf("0");

	do {
		i=0;
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
		while ((c=getchar())!=EOF && !isalnum(c))
			putchar(c);
	} while (c!=EOF && dequeue(q) && enqueue(q, c));
	printf("\n");

	return 0;
}