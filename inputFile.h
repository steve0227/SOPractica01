#ifndef INPUTFILE_H_INCLUDED
#define INPUTFILE_H_INCLUDED

int getIngredientsQuantities(int quantities[], char ingredientsdif[20][10], FILE * restrict fp);
void getPMatrix(int ingredients, int np, char ingredientsdif[ingredients][10], int p[np][ingredients], FILE * restrict fp);

#endif