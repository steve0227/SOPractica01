#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct node {
	int ntpp;
	int * ap;
	int sum;
	struct node * next;
} node_t;

typedef struct list{
	node_t * head;
} list_t;

void pushNode(list_t * l, int ntpp, int ap[ntpp]);
void listInit(list_t * l);
node_t * apMaximo(list_t * l);
void swap(int *p1, int *p2);
void permute(int ntpp,int ap[ntpp], list_t * l) ;
void sumList(list_t * l, int ingredients, int dishes, int p[dishes][ingredients], int p2, int p3, int p4);

#endif