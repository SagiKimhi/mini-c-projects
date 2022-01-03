#include "LL-Sorting.h"

int main(int argc, char *argv[])
{
	LIST *head = NULL, *tail = NULL;
	Bool emptyList = TRUE;
	int num;
	printf("Enter a list of ints to be printed and sorted and printed again:\n");
	if (scanf("%d", &num) == 1){
		head = newElement(num);
		tail = head;
		emptyList = FALSE;
		while (scanf("%d", &num) == 1)
			tail = addEnd(tail, newElement(num));
	}
	if (!feof(stdin) || emptyList)
		printf("Error! Invalid type entered!\nPlease only use integers!\n");
	else {
		printf("Original List:\n");
		printList(head);
		head = mergeSort(head);
		printf("Sorted list:\n");
		printList(head);
	}
	deleteList(head);
	return 0;
}

LIST *newElement(int val)
{
	LIST *new = (LIST *) malloc (sizeof(LIST));
	if (new!=NULL) {
		new->val = val;
		new->next = NULL;
		return new;
	}
	return NULL;
}

LIST *deleteElement(LIST *head, LIST *element)
{
	LIST *prev = NULL, *curr=NULL;
	for (curr = head; curr != NULL; curr = curr->next) {
		if (curr == element) {
			if (prev == NULL)
				head = curr->next;
			else
				prev->next = curr->next;
			free(curr);
			curr = NULL;
			break;
		}
		else
			prev = curr;
	}
	return head;
}

LIST *deleteList(LIST *head)
{
	while (head != NULL)
		head = deleteElement(head, head);
	return NULL;
}

LIST *removeVal(LIST *head, int val)
{
	LIST *prev, *curr;
	prev = curr = head;
	while (curr != NULL && curr->val != val) {
		prev = curr;
		curr = curr->next;
	}
	if (curr == NULL)
		return head;
	prev->next = curr->next;
	free(curr);
	return head;
}

LIST *addFront(LIST *head, LIST *newp)
{
	newp->next = head;
	return newp;
}

LIST *addEnd (LIST *tail, LIST *newp)
{	
	if (tail == NULL)
		return newp;
	tail->next = newp;
	return newp;
}

LIST *addmiddle (LIST *head, LIST *newp)
{
	Bool found = FALSE;
	LIST *prev, *curr; 	
	if (head == NULL) {
		head = addFront(head, newp);
		return head;
	}
	prev = curr = head ; 
	while (!found) {
  		if ((found = (curr->val > prev->val) ? TRUE: FALSE)) {
			if (curr == head) { 
					head = addFront(head, newp); 
					return(head);
		        }
			else {
				prev -> next = newp;;
				newp -> next = curr;
				return head;
	  		}
	  	} 
	if  (curr -> next == NULL) {
		head = addEnd(head, newp); 
		return head;
	}
	prev = curr; 
	curr = curr -> next; 
	}
	return head;
}

LIST *mergeSort(LIST *node)
{
	LIST *node2;
	if (node == NULL || node->next == NULL)
		return node;
	node2 = split(node);
	node = mergeSort(node);
	node2 = mergeSort(node2);

	return merge(node, node2);
}

LIST *split(LIST *node)
{
	LIST *node2;
	if (node == NULL || node->next == NULL)
		return NULL;
	node2 = node->next;
	node->next = node2->next;
	node2->next = split(node2->next);

	return node2;
}

LIST *merge(LIST *node1, LIST *node2)
{
	if (node1 == NULL)
		return node2;
	if (node2 == NULL)	
		return node1;
	if (node1->val < node2->val) {
		node1->next = merge(node1->next, node2);
		return node1;
	}
	else if (node1->val > node2->val) {
		node2->next = merge(node1, node2->next);
		return node2;
	}
	else {
		node1->next = merge(node1->next, node2->next);
		return node1;
	}
}

int listLen(LIST *head)
{
	LIST *p = head;
	int i = 0;
	while (p!=NULL) {
		p = p->next;
		i++;
	}
	return i;
}

void printList(LIST *head)
{
	LIST *p;
	for (p=head; p!=NULL; p = p->next)
		printf("%d ", p->val);
	printf("\n");
}