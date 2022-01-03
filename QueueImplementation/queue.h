#ifndef _QUEUE_H
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct queue_node{
	int data;
	struct queue_node *next;
} Qnode;

typedef struct queue {
	Qnode *front, *rear;
} Queue;

#endif