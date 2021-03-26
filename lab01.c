#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
void remove_spaces(char* restrict str_trimed,const char* restrict str_untrimmed)
{
	while(*str_untrimmed!='\0')
	{
		if(!isspace(*str_untrimmed))
		{
			*str_trimed=*str_untrimmed;
			str_trimed++;
		}
		str_untrimmed++;
	}
	*str_trimed='\0';
}

int get_ingredients_quantities(int quantities[], char ingredientsdif[20][10], FILE * restrict fp){
	char line[1024];
	int linecount= 0;
	int termscount=0;
	int numingredients=0;
	int ingredients=0;
	bool band;
	while(fgets(line,1024,fp)){
		char *word;
		char *rest=line;
		if(linecount==0){
			while (word=strtok_r(rest," ",&rest)){
			quantities[termscount] = atoi(word);
			termscount++;
			}
		linecount++;
		}else{
			word= strtok_r(rest," ", &rest);
			numingredients = atoi(word);

			for(int i =0; i<numingredients;i++){
				word= strtok_r(rest," ", &rest);
				band=false;
				char *aux=(char*)malloc(sizeof(char*));
				remove_spaces(aux,word);
				for(int a=0;a<ingredients;a++){
					int result =strcmp(ingredientsdif[a],aux);
					if(result==0){
						band=true;
					}
				}
				if(band==false){
					strcpy(ingredientsdif[ingredients],aux);
					ingredients++;
				}
			}
		}
	}
	return ingredients;
}
void fill_p_matriz(int ingredients, int np, char ingredientsdif[ingredients][10], int p[np][ingredients],int line, char* restrict aux){
	for(int i=0;i<ingredients;i++){
		int result=strcmp(ingredientsdif[i],aux);
/*		printf("vector %s\n",ingredientsdif[i]);
		printf("palabra %s\n",aux);
		printf("result %d\n",result);*/
		if(result==0){
			p[line-1][i]=1;
			i=ingredients;
/*			printf("i value %d\n",i);
			printf("p value %d\n",p[line][i]);*/
		}
	}
}


void get_p_matriz(int ingredients, int np, char ingredientsdif[ingredients][10], int p[np][ingredients],FILE* restrict fp){
	char line[1024];
	int linecount= 0;
	int numingredients=0;
	while(fgets(line,1024,fp)){
		char *word;
		char *rest=line;
		if(linecount==0){
/*			word=strtok_r(rest," ",&rest);
			int np = atoi(word);
			int p[np][ingredients]*/
			linecount++;
		}else{
			word= strtok_r(rest," ", &rest);
			numingredients = atoi(word);
			for(int i =0; i<numingredients;i++){
				word= strtok_r(rest," ", &rest);
				char *aux=(char*)malloc(sizeof(char*));
				remove_spaces(aux,word);
				fill_p_matriz(ingredients,np,ingredientsdif,p,linecount,aux);
			}
			linecount++;
		}
	}
}

int main (int argc, char*argv[]){
	if (argc < 2){
		printf("You must specify a filepath\n");
		return EXIT_FAILURE;
	}
	FILE *fp=fopen(argv[1],"r");

	if(!fp){
		printf("Error while opening the file %s\n",argv[1]);
	}

	int quantities[4];
	char ingredientsdif[20][10];
	int ingredients=get_ingredients_quantities(quantities,ingredientsdif,fp);
	fclose(fp);
	int np=quantities[0];
	int ntpp=quantities[1]*2+quantities[2]*3+quantities[3]*4;
	int p[np][ingredients];
	int ap[ntpp];

	int op2=2*quantities[1];
	int op3=op2+3*quantities[2];

	fp=fopen(argv[1],"r");
	get_p_matriz(ingredients,np,ingredientsdif,p,fp);
	fclose(fp);

	for(int b=0;b<4;b++){
		printf("quantity: %d\n",quantities[b]);
	}
	for(int c=0;c<ingredients;c++){
		printf("iterate vector ingredients: %s\n ",ingredientsdif[c]);
	}
	printf("number of diferent ingredients %d\n",ingredients);

	for(int i =0;i<quantities[0];i++){
		for(int j=0;j<ingredients;j++){
			if(p[i][j]!=1){
				printf("0");
			}
			else{
				printf("%d",p[i][j]);
			}
		}
		printf("\n");
	}

}


