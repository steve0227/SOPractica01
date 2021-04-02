#ifndef DISHES_H
#define DISHES_H
#include <stdio.h>

int sumIngredients(int ntpp, int ap[ntpp], int ingredients, int dishes, int p[dishes][ingredients], int p2,int p3, int p4);

void fillPMatrix(int ingredients, int np, char ingredientsdif[ingredients][10], int p[np][ingredients], int line, char * restrict aux);
void fillPWithZero(int ingredients, int np, int p[np][ingredients]);

void fillAp(int ntpp, int ap[ntpp]);

#endif