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
int main (int argc, char*argv[]){
	if (argc < 2){
		printf("You must specify a filepath\n");
		return EXIT_FAILURE;
	}
	FILE *fp=fopen(argv[1],"r");

	if(!fp){
		printf("Error while opening the file %s\n",argv[1]);
	}
	char line[1024];
	int linecount= 0;
	int quantities[4];
	int termscount=0;
	int numingredients=0;
	char ingredientsdif[10][10];
	int ingredients=0;
	bool band;
	
/*	char *a1="ajo ";
	char *a2="ajo";
	char a3[2][6];
	strcpy(a3[1],a2);
	int r1=strcmp(a1,a2);
	int r2=strcmp(a1,a3[1]);
	printf("r1: %d\n",r1);
	printf("r2: %d\n",r2);
	char *a4=(char*)malloc(sizeof(char*));
	remove_spaces(a4,a1);
	int r3=strcmp(a4,a3[1]);
	printf("r3: %d\n",r3);*/

	
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
					printf("word %s\n",word);
					printf("ingredientdif %s\n",ingredientsdif[a]);
					printf("%d\n",result);
					if(result==0){
						band=true;
					}
				}
				if(band==false){
					printf("new ingredient %s\n",word);
					strcpy(ingredientsdif[ingredients],aux);
					printf("vector ingredient %s\n",ingredientsdif[ingredients]);
					ingredients++;
				}
				printf("all ingredient:%s",word);
			}
		}
	}
	for(int b=0;b<4;b++){
		printf("quantity: %d\n",quantities[b]);
	}
	for(int c=0;c<ingredients;c++){
		printf("iterate vector ingredients: %s\n ",ingredientsdif[c]);
	}
	printf("number of diferent ingredients %d\n",ingredients);
	fclose(fp);
}


