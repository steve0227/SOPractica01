#ifndef FILE_H
#define FILE_H
#include <stdio.h>

int getIngredientsQuantities(int quantities[], char ingredientsdif[20][10], FILE * restrict fp);
void getPMatrix(int ingredients, int np, char ingredientsdif[ingredients][10], int p[np][ingredients], FILE * restrict fp);

void writeFile(FILE * fp, char * result);
void writePInFile(int ingredients, int np, int p[np][ingredients], FILE *fw);
void writeApInFile(int ntpp, int ap[ntpp], FILE *fw);
void writeIngredientsQuantity(int sum, FILE *fw);
void writeIngredients(int ingredients, int np, int p[np][ingredients], char ingredientsdif[20][10], int ntpp, int ap[ntpp], int p2, int p3, int p4, FILE * fw);

#endif