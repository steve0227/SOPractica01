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

void fill_p_0(int ingredients, int np, int p[np][ingredients]){
	for(int i =0;i<np;i++){
		for(int j=0;j<ingredients;j++){
			p[i][j]=0;
		}
	}
}

void fill_ap(int ntpp,int ap[ntpp]){
	for(int i=0; i<ntpp;i++){
		ap[i]=i;
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
	int p2=quantities[1];
	int p3=quantities[2];
	int p4 =quantities[3];
	int ntpp=2*p2+3*p3+4*p4;
	int p[np][ingredients];
	int ap[ntpp];

	fill_p_0(ingredients,np,p);
	int op3=p2*2;
	int op4=2*p2+3*p3;


	fp=fopen(argv[1],"r");
	get_p_matriz(ingredients,np,ingredientsdif,p,fp);
	fclose(fp);

/*	for(int b=0;b<4;b++){
		printf("quantity%d:%d\n",b,quantities[b]);
	}*/
	for(int c=0;c<ingredients;c++){
		printf("vector ingredients %d: %s\n ",c ,ingredientsdif[c]);
	}
/*	printf("number of diferent ingredients %d\n",ingredients);*/

	for(int i =0;i<quantities[0];i++){
		for(int j=0;j<ingredients;j++){
			printf("%d",p[i][j]);
		}
		printf("\n");
	}

	fill_ap(ntpp,ap);
	for(int i=0;i<ntpp;i++){
		printf("ap: %d\n",ap[i]);
	}
	int sum2=0;
	for(int s2=0;s2<=(p2-1);s2++){
		for(int j=0;j<ingredients;j++){
			if(p[ap[2*s2]][j]==1 || p[ap[2*s2+1]][j]==1){
				sum2++;
			}
		}
	}
	printf("sum 2 :%d\n",sum2);
	int sum3=0;
	for(int i=0;i<=(p3-1);i++){
		for(int j=0;j<ingredients;j++){
			if(p[ap[op3+(3*i)]][j]==1 || p[ap[op3+(3*i)+1]][j]==1 || p[ap[op3+(3*i)+2]][j]==1){
				sum3++;
			}
		}
	}
	printf("sum 3 :%d\n",sum3);
	int sum4=0;
	for(int i=0;i<=(p4-1);i++){
		for(int j=0;j<ingredients;j++){
			if(p[ap[op4+(4*i)]][j]==1 || p[ap[op4+(4*i)+1]][j]==1 || p[ap[op4+(4*i)+2]][j]==1 || p[ap[op4+(4*i)+3]][j]==1){
				sum4++;
			}
		}
	}
	printf("sum 4 :%d\n",sum4);

}

