#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inputFile.h>

int getIngredientsQuantities(int quantities[], char ingredientsdif[20][10], FILE * restrict fp) {
	char line[1024];
	int linecount = 0;
	int termscount = 0;
	int numIngredients = 0;
	int ingredients = 0;
	bool band;
	while(fgets(line,1024,fp)) {
		char *word;
		char *rest = line;
		if(linecount == 0){
			while (word = strtok_r(rest," ",&rest)) {
				quantities[termscount] = atoi(word);
				termscount++;
			}
			if((2*quantities[1] + 3*quantities[2] + 4*quantities[3]) != quantities[0]){
				return -1;
			}
			linecount++;
		} else{
			word= strtok_r(rest," ", &rest);
			numIngredients = atoi(word);
			if (numIngredients == 0){
				return -2;/*NaN*/
			}
			for (int i =0; i < numIngredients; i++) {
				word = strtok_r(rest," ", &rest);
				band = false;
				if ((word == NULL) || (word[0] =='\0')){
					return -3;/*menos palabras*/
				}
				char *aux = (char*) malloc(sizeof(char*));
				removeSpaces(aux, word);
				for (int a = 0; a < ingredients; a++) {
					int result = strcmp(ingredientsdif[a], aux);
					if(result == 0){
						band = true;
					}
				}
				if (band == false) {
					strcpy(ingredientsdif[ingredients], aux);
					ingredients++;
				}
				/*if(i == numIngredients - 1){
					word= strtok_r(rest," ", &rest);
					if((word != NULL) || (word[0] != '\0')){
						return -4;/*mas palabras
					}
				}*/
			}
		linecount++;
		}
	}
	if ((linecount-1) != quantities[0]) {
		return -5; /*no cocinciden los platos con las lineas*/
	}
	return ingredients;
}

void getPMatrix(int ingredients, int np, char ingredientsdif[ingredients][10], int p[np][ingredients], FILE* restrict fp){
	char line[1024];
	int linecount = 0;
	int numIngredients = 0;
	while (fgets(line, 1024, fp)) {
		char *word;
		char *rest = line;
		if (linecount == 0) {
			linecount++;
		} else {
			word = strtok_r(rest, " ", &rest);
			numIngredients = atoi(word);
			for (int i = 0; i < numIngredients; i++) {
				word = strtok_r(rest," ", &rest);
				char *aux = (char*) malloc(sizeof(char*));
				removeSpaces(aux, word);
				fillPMatrix(ingredients, np, ingredientsdif, p, linecount, aux);
			}
			linecount++;
		}
	}
}