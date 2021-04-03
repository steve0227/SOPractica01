#include "file.h"
#include "dishes.h"
#include "linkedlist.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main (int argc, char*argv[]){
	if (argc < 3) {
		printf("You must specify an input filepath and an outpu filepth\n");
		return EXIT_FAILURE;
	}
	FILE *fp=fopen(argv[1],"r");

	if(!fp) {
		printf("Error while opening the file %s\n",argv[1]);
		return EXIT_FAILURE;
	}

	int quantities[4];
	char ingredientsdif[20][10];
	int ingredients = getIngredientsQuantities(quantities, ingredientsdif, fp);
	fclose(fp);
	if(ingredients > 0) {
		int np = quantities[0];
		int p2 = quantities[1];
		int p3 = quantities[2];
		int p4 = quantities[3];
		int ntpp = 2*p2 + 3*p3 + 4*p4;
		int p[np][ingredients];
		int ap[ntpp];

		fillPWithZero(ingredients, np, p);
		fp = fopen(argv[1],"r");
		getPMatrix(ingredients, np, ingredientsdif, p, fp);
		fclose(fp);

		fillAp(ntpp,ap);

		list_t * l = (list_t*) malloc(sizeof(list_t));
		listInit(l);
		permute(ntpp, ap, l);

		sumList(l, ingredients, np, p, p2, p3, p4);
		node_t * max = (node_t *) malloc(sizeof(node_t));
		max = apMaximo(l);


		FILE * fw = fopen(argv[2], "w");
		writePInFile(ingredients, np,  p, fw);
		writeApInFile(ntpp, ap,  fw);
		writeIngredientsQuantity(max -> sum, fw);
		writeIngredients(ingredients, np, p, ingredientsdif, ntpp, ap, p2, p3, p4, fw);
		fclose(fw);
	}else{
		if(ingredients == -1) {
			printf("Error: invalid format in the first line of the input file: %s\n", argv[1]);
		}
		if(ingredients == -2){
			printf("Error: invalid ingredients number (NaN)");
		}
		if(ingredients == -3){
			printf("Error: invalid ingredients number (lower than specified)");
		}
		if(ingredients == -4){
			printf("Error: invalid ingredients number (greater than specified)");
		}
		if(ingredients == -5){
			printf("Error: invalid dishes number");
		}
		return EXIT_FAILURE;
	}
}