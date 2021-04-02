#include "dishes.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int sumIngredients(int ntpp, int ap[ntpp], int ingredients, int dishes, int p[dishes][ingredients], int p2, int p3, int p4) {
	int op3 = p2*2;
	int op4 = 2*p2 + 3*p3;
	int sum2 = 0;

	for(int s2 = 0; s2 <= (p2-1); s2++){
		for(int j = 0; j < ingredients; j++){
			if(p[ap[2*s2]][j] == 1 || p[ap[2*s2+1]][j] ==1 ){
				sum2++;
			}
		}
	}
	int sum3 = 0;
	for(int i = 0; i <= (p3-1); i++){
		for(int j = 0; j < ingredients; j++){
			if(p[ap[op3+(3*i)]][j] ==1 || p[ap[op3+(3*i)+1]][j] == 1 || p[ap[op3+(3*i)+2]][j] == 1){
				sum3++;
			}
		}
	}
	int sum4 = 0;
	for(int i = 0; i <= (p4-1); i++){
		for(int j = 0; j < ingredients; j++){
			if(p[ap[op4+(4*i)]][j] == 1 || p[ap[op4+(4*i)+1]][j] == 1 || p[ap[op4+(4*i)+2]][j] == 1 || p[ap[op4+(4*i)+3]][j] == 1) {
				sum4++;
			}
		}
	}
	return sum2 + sum3 + sum4;
}

void fillPMatrix(int ingredients, int np, char ingredientsdif[ingredients][10], int p[np][ingredients], int line, char* restrict aux){
	for(int i = 0; i < ingredients; i++) {
		int result = strcmp(ingredientsdif[i], aux);
		if(result == 0){
			p[line-1][i] = 1;
			i = ingredients;
		}
	}
}

void fillPWithZero(int ingredients, int np, int p[np][ingredients]){
	for(int i = 0; i < np; i++) {
		for(int j = 0; j < ingredients; j++){
			p[i][j] = 0;
		}
	}
}

void fillAp(int ntpp, int ap[ntpp]) {
	for(int i = 0; i < ntpp; i++){
		ap[i] = i;
	}
}