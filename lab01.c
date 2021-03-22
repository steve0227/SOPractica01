#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
int main (int argc, char*argv[]){
	if (argc < 2){
		printf("You must specify a filepath\n");
		return EXIT_FAILURE;
	}
	FILE*fp=fopen(argv[1],"r");

	if(!fp){
		printf("Error while opening the file %s\n",argv[1]);
	}
	char line[1024];
	int linecount= 0;
	int quantities[4];
	int termscount=0;
	int numingredients=0;
	char *ingredientsdif[10];
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

				for(int a=0;a<=10;a++){
					if(strcmp(ingredientsdif[a],word)==0){
						band=true;
					}
				}
				if(band==false){
					ingredientsdif[ingredients]=word;
/*					ingredients++;*/
				}
				printf("ingredient: %s\n", word);
			}
		}
	}
	for(int i=0;i<4;i++){
		printf("quantity: %d\n",quantities[i]);
	}
/*	for(int i=0;i<10;i++){
		printf("ingredients: %s\n",ingredientsdif[i]);
	}
	printf("number of diferent ingredients %d\n",ingredients);*/
	fclose(fp);
}
