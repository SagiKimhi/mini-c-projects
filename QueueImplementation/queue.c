#include "queue.h"

Qnode *newNode(int data)
{
	Qnode *ptr;
	if (!data)
		return NULL;
	if (!(ptr = (Qnode*) malloc(sizeof(Queue))))
		return NULL;
	ptr->data = data;
	ptr->next = NULL;
	return ptr;
}

Queue *newQueue()
{
	Queue *qPtr = (Queue *)malloc(sizeof(Queue));
	if (!qPtr)
		return NULL;
	qPtr->front = NULL;
	qPtr->rear = NULL;
	return qPtr;
}

int isEmpty(Queue *q)
{
	return (q->rear==NULL);
}

int enqueue(Queue *q, int data)
{
	if (isEmpty(q)) {
		if (!(q->front = q->rear = newNode(data)))
			return 0;
		return 1;
	}
	if (!(q->rear->next = newNode(data)))
		return 0;
	q->rear = q->rear->next;
	return 1;
}

int dequeue(Queue *q)
{
	Qnode *temp;
	if (isEmpty(q))
		return 0;
	temp = q->front;
	if (!(q->front = q->front->next))
		q->rear=NULL;
	free(temp);
	return 1;
}

int main(int argc, char **argv)
{
	int i;
	Queue *q = newQueue();
	if (!q)
		return EXIT_FAILURE;
	for (i=0; i<1000; i++) {
		enqueue(q, i);
	}
	while (!isEmpty(q)) {
		printf("Item in queue:\t%d\n", q->front->data);
		dequeue(q);
	}
	printf("Success! :D\n");

	return EXIT_SUCCESS;
}