#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inputFile.h>

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
int sumIngredients(int ntpp, int ap[ntpp], int ingredients, int dishes, int p[dishes][ingredients], int p2,int p3, int p4);
void sumList(list_t * l, int ingredients, int dishes, int p[dishes][ingredients], int p2, int p3, int p4);

void removeSpaces(char* restrict str_trimed, const char* restrict str_untrimmed);

void fillPMatrix(int ingredients, int np, char ingredientsdif[ingredients][10], int p[np][ingredients], int line, char * restrict aux);
void fillPWithZero(int ingredients, int np, int p[np][ingredients]);

void fillAp(int ntpp,int ap[ntpp]);
void swap(int *p1, int *p2);
void permute(int ntpp,int ap[ntpp], list_t * l) ;

void writeFile(FILE * fp, char * result);
void writePInFile(int ingredients, int np, int p[np][ingredients], FILE *fw);
void writeApInFile(int ntpp, int ap[ntpp], FILE *fw);
void writeIngredientsQuantity(int sum, FILE *fw);
void writeIngredients(int ingredients, int np, int p[np][ingredients], char ingredientsdif[20][10], int ntpp, int ap[ntpp], int p2, int p3, int p4, FILE *fw);

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


int sumIngredients(int ntpp, int ap[ntpp], int ingredients, int dishes, int p[dishes][ingredients], int p2, int p3, int p4) {
	int op3 = p2*2;
	int op4 = 2*p2 + 3*p3;
	int sum2 = 0;

	for(int s2 = 0; s2 < = (p2-1); s2++){
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
void sumList(list_t * l, int ingredients, int dishes, int p[dishes][ingredients], int p2,int p3, int p4) {
	node_t * current = l -> head;
	while(current != NULL) {
		current -> sum = sumIngredients(current -> ntpp, current -> ap, ingredients, dishes, p, p2, p3, p4);
		current = current -> next;
	}
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
			n=0;
		} else{
			c[n] = 0;
			n += 1;
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