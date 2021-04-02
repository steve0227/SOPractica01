#include "dishes.h"
#include "linkedlist.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void pushNode(list_t * l, int ntpp, int ap[ntpp]) {
	node_t * current, * tmp;
	current = l -> head;
	if (current == NULL) {
		current = (node_t *) malloc(sizeof(node_t));
		current -> next = NULL;
		current -> ap = (int *) malloc(sizeof(int)*ntpp);
		current -> ntpp = ntpp;
		for(int i = 0; i < ntpp; i++) {
			current -> ap[i] = ap[i];
		}
		l -> head = current;
	} else {
		while(current -> next != NULL) {
			current = current -> next;
		}
		tmp = (node_t *) malloc(sizeof(node_t));
		tmp -> ntpp = ntpp;
		tmp -> ap = (int *) malloc(sizeof(int)*ntpp);
		for(int i = 0; i < ntpp; i++) {
			tmp -> ap[i] = ap[i];
		}
		tmp -> next = NULL;
		current -> next = (node_t *) malloc(sizeof(node_t));
		current -> next = tmp;
	}
}

void listInit(list_t * l) {
	l -> head = NULL;
}

node_t * apMaximo(list_t * l) {
	node_t * current = l -> head;
	node_t * maxSum = (node_t *) malloc(sizeof(node_t));
	int aux = 0;
	while(current != NULL) {
		if(current -> sum > aux) {
			maxSum = current;
			aux = current -> sum;
		}
		current = current -> next;
	}
	return maxSum;
}

void swap(int *p1, int *p2){
	int aux = *p1;
	*p1 = *p2;
	*p2 = aux;
}

void permute(int ntpp, int ap[ntpp], list_t * l) {
	int c[ntpp];
	for(int i = 0; i < ntpp; i++) {
		c[i] = 0;
	}
	pushNode(l, ntpp, ap);
	int n = 0;
	while(n < ntpp) {
		if(c[n] < n){
			if(n%2 == 0){
				swap(&ap[0], &ap[n]);
			} else {
				swap(&ap[c[n]], &ap[n]);
			}
			pushNode(l, ntpp, ap);
			c[n] += 1;
			n = 0;
		} else{
			c[n] = 0;
			n += 1;
		}
	}
}

void sumList(list_t * l, int ingredients, int dishes, int p[dishes][ingredients], int p2, int p3, int p4) {
	node_t * current = l -> head;
	while(current != NULL) {
		current -> sum = sumIngredients(current -> ntpp, current -> ap, ingredients, dishes, p, p2, p3, p4);
		current = current -> next;
	}
}