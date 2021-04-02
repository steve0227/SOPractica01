#include "dishes.h"
#include "file.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void removeSpaces(char* restrict str_trimed, const char* restrict str_untrimmed) {
	while(*str_untrimmed != '\0') {
		if(!isspace(*str_untrimmed)) {
			*str_trimed = *str_untrimmed;
			str_trimed++;
		}
		str_untrimmed++;
	}
	*str_trimed = '\0';
}

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

void writeFile(FILE * fp, char * result) {
	fprintf(fp, "%s\n", result);
}

void writePInFile(int ingredients, int np, int p[np][ingredients], FILE *fw) {
	writeFile(fw, "Esta es la matriz de los dishes:\n");
	char * line = (char *) malloc(sizeof(char) * 1024);
	char * auxLine = (char *) malloc(sizeof(char) * 10);
	for(int j = 0; j < ingredients; j++){
		strcpy(line, "");
		for(int i = 0; i < np ; i++){
			sprintf(auxLine, "%d", p[i][j]);
			strcat(line, auxLine);
			strcat(line, " ");
		}
		writeFile(fw, line);
	}
}  

void writeApInFile(int ntpp, int ap[ntpp], FILE *fw) {
	char * line = (char *) malloc(sizeof(char) * 1024);
	char * auxLine = (char *) malloc(sizeof(char) * 10);
	strcpy(line, "\nEste es el vector de solucion: ");
	for(int i = 0; i < ntpp; i++){
		sprintf(auxLine, "%d", ap[i]);
		strcat(line, auxLine);
		strcat(line, " ");
	}
	strcat(line, "\n");
	writeFile(fw, line);
}

void writeIngredientsQuantity(int sum, FILE *fw){
	char * line = (char *) malloc(sizeof(char) * 1024);
	char * auxLine = (char *) malloc(sizeof(char) * 10);
	strcpy(line, "La cantidad de ingredientes totales es: ");
	sprintf(auxLine, "%d", sum);
	strcat(line, auxLine);
	strcat(line, "\n");
	writeFile(fw, line);
}

void writeIngredients(int ingredients, int np, int p[np][ingredients], char ingredientsdif[20][10], int ntpp, int ap[ntpp], int p2, int p3, int p4, FILE *fw ){
	char * line = (char *) malloc(sizeof(char) * 1024);
	char * auxLine = (char *) malloc(sizeof(char) * 10);
	int order = 0;
	char * auxLine2 = (char *) malloc(sizeof(char) * 1024);
	int op3 = p2*2;
	int op4 = 2*p2 + 3*p3;
	for(int s2 = 0; s2 <= (p2-1); s2++) {
		strcpy(auxLine2, "");
		for(int j = 0; j < ingredients; j++) {
			if(p[ap[2*s2]][j] == 1 || p[ap[2*s2+1]][j] == 1) {
				strcat(auxLine2, ingredientsdif[j]);
				strcat(auxLine2, " ,");
			}
		}
		sprintf(auxLine, "%d", order);
		strcpy(line, "El pedido ");
		strcat(line, auxLine);
		strcat(line, " contiene: ");
		strcat(line, auxLine2);
		writeFile(fw, line);
		order++;
	}
	for(int i = 0; i <= (p3-1); i++) {
		strcpy(auxLine2, "");
		for(int j = 0; j < ingredients; j++) {
			if(p[ap[op3+(3*i)]][j] == 1 || p[ap[op3+(3*i)+1]][j] == 1 || p[ap[op3+(3*i)+2]][j] == 1) {
				strcat(auxLine2, ingredientsdif[j]);
				strcat(auxLine2, " ,");
			}
		}
		sprintf(auxLine, "%d", order);
		strcpy(line, "El pedido ");
		strcat(line, auxLine);
		strcat(line, " contiene: ");
		strcat(line, auxLine2);
		writeFile(fw, line);
		order++;
	}
	for(int i = 0; i <= (p4-1); i++) {
		strcpy(auxLine2, "");
		for(int j = 0; j < ingredients; j++) {
			if(p[ap[op4 + (4*i)]][j] == 1 || p[ap[op4 + (4*i) + 1]][j] == 1 || p[ap[op4 + (4*i) + 2]][j] == 1 || p[ap[op4 + (4*i) + 3]][j] == 1) {
				strcat(auxLine2, ingredientsdif[j]);
				strcat(auxLine2, " ,");
			}
		}
		sprintf(auxLine, "%d", order);
		strcpy(line, "El pedido ");
		strcat(line, auxLine);
		strcat(line, " contiene: ");
		strcat(line, auxLine2);
		writeFile(fw, line);
		order++;
	}

}
