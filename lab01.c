#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
int main (int argc, char*argv[]){
	if (argc < 2){
		printf("You must specify a filepath\n");
		return EXIT_FAILURE;
	}
	FILE *fp=fopen(argv[1],"r");

	if(!fp){
		printf("Error while opening the file %s\n",argv[1]);
	}
	char line[2048];
	int linecount= 0;
	int quantities[4];
	int termscount=0;
	int numingredients=0;
	char *ingredientsdif[1024];
	int ingredients=0;
	bool band;
	while(fgets(line,2048,fp)){
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

				for(int a=0;a<ingredients;a++){
					int result =strcmp(ingredientsdif[a],word);
					printf("word %s\n",word);
					printf("ingredientdif %s\n",ingredientsdif[a]);
					printf("%d\n",result);
					if(result==0){
						band=true;
					}
				}
				if(band==false){
					printf("new ingredient %s\n",word);
					ingredientsdif[ingredients]=word;
					printf("vector ingredient %s\n",ingredientsdif[ingredients]);
					ingredients++;
				}
				printf("all ingredient: %s", word);
			}
		}
	}
	for(int b=0;b<4;b++){
		printf("quantity: %d\n",quantities[b]);
	}
	for(int c=0;c<ingredients;c++){
		printf("iterate vector ingredients: %s ",ingredientsdif[c]);
	}
	printf("number of diferent ingredients %d\n",ingredients);
	fclose(fp);
}
