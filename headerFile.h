#ifndef LINEAR_MAIN
#define LINEAR_MAIN
#include "linearMain.c"

//struct importedForm{
//    int effectiveSize;
//    int maximumSize;
//    void **arrayPointer;
//    void (*LinearAdd)(void*, void*, int); //First LinearForm, second LinearForm, sign (1 for summation, -1 for detraction)
//    void (*LinearMultiply)(void*, void*); //LinearForm, object to multiply on
//    void *(*LinearValue)(void*, void**);    //LinearForm, array of objects (x1, x2, ..., xn variables)
//};

typedef struct importedForm LinearForm;

int LinearLength(const LinearForm *form);
void LinearInit(LinearForm *form);
void LinearResize(LinearForm *form, const int newLength);
void LinearAssign(LinearForm *form, const int itemIndex, void *givenItem);


#endif
#include <stdio.h>
#include <stdlib.h>
