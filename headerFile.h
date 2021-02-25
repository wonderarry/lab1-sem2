#ifndef LINEAR_MAIN
#define LINEAR_MAIN
#include "linearMain.c"

/*typedef struct imported{
    int effectiveSize;
    int maximumSize;
    double **arrayPointer;
}   LinearForm;*/

typedef struct imported LinearForm;

int LinearLength(const LinearForm *form);
void LinearInit(LinearForm *form);
void LinearResize(LinearForm *form, const int newLength);
void LinearAssign(LinearForm *form, const int itemIndex, const double itemValueRe, const double itemValueIm);
double *LinearValue(LinearForm *form, const double **valueArray);
void LinearAdd(LinearForm *formMain, const LinearForm *formAdded, const int sign);
void LinearMultiply(LinearForm *form, const double *multiplier);

#endif
#include <stdio.h>
#include <stdlib.h>
