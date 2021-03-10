#include <stdio.h>
#include <stdlib.h>
#include "headerFile.h"
//Henceforth x and y are LinearForm objects.
//How to use:

//0. Initialize LinearForm with with {0, 0, NULL} values - defined in headerFile

//1. First initialize the LinearForm with LinearAssign

//2. Use LinearAssign(&x) to assign a coefficient (itemValueRe + i*itemValueIm) to the variable with index itemIndex (starts from 0). Returns void
//Example: with empty LinearForm called x LinearAssign(&x, 3, 2, 1) will stand for linear form = x3 * (2 + i)

//3. Use LinearLength() to get the last index of a variable in the LinearForm (indices are counted from 0). Returns an integer - maximum index of a variable.

//4. Use LinearValue() to calculate the value of the LinearForm. Accepts dynamic arrays of with the size of [LinearLength()][2], returns pointer to the [valueRe, valueIm] array.
//Example: If the array is called y, then any of the y[n][0] values is the real value for the element at index n, and y[n][1] is the imaginary value

//5. LinearAdd(&x, &y, sign) adds y coefficients' values to x. Sign has 2 allowed states: 1 (x+y) and -1 (x-y). Only affects x. Returns void

//6. LinearMultiply(&x, multiplier) multiplies all coefficients by dynamic array multiplier's coefficients: [0] for real, [1] for imaginary. Returns void (only x gets changed)


struct importedForm{
    int effectiveSize;
    int maximumSize;
    void **arrayPointer;
    void (*LinearAdd)(void*, void*, int); //First LinearForm, second LinearForm, sign (1 for summation, -1 for detraction)
    void (*LinearMultiply)(void*, void*); //LinearForm, object to multiply on
    void *(*LinearValue)(void*, void**);    //LinearForm, array of objects (x1, x2, ..., xn variables)
    int *isAssigned;
  };

typedef struct importedForm LinearForm;



int LinearLength(const LinearForm *form){
    printf("entered LinearLength. it will return effectiveSize (hopefully)\n");
    return form->effectiveSize;
}


void LinearInit(LinearForm *form){
    printf("entered linearinit if\n" );
    form->arrayPointer = calloc(1, sizeof(void*));
    printf("calloc arrayPointer\n" );
    form->maximumSize = 1;
    printf("maxsize = 1\n" );
    form->isAssigned = calloc(1, sizeof(int));
    printf("calloc isAssigned\n" );
    form->isAssigned[0] = 0;
    printf("isAssigned[0](redundant, safety only) = 0\n" );
}


void LinearResize(LinearForm *form, const int newLength){

    if (form->maximumSize == 0){
        printf("entered linearinit if\n");
        LinearInit(form);
        printf("initted\n" );
    }

    form->arrayPointer = realloc(form->arrayPointer, newLength);
    printf("reallocated arrayPointer\n" );
    form->isAssigned = realloc(form->isAssigned, newLength);
    printf("reallocated isAssigned\n" );
    for (int i = form->maximumSize; i < newLength; ++i){
        printf("i loop, i = %d\n", i);
        form->isAssigned[i] = 0;
        printf("isAssigned[%d] = 0\n", i);
    }
    printf("exited i loop\n" );
    form->maximumSize = newLength;
    printf("changed maximumSize\n" );
}


void LinearAssign(LinearForm *form, const int itemIndex, void *givenItem){
    printf("entered assign\n");
    if (form->maximumSize <= itemIndex){
        printf("entered resize\n" );
        LinearResize(form, itemIndex * 2);
        printf("out of resize\n" );

    }
    printf("out of resize if\n" );
    form->arrayPointer[itemIndex] = givenItem;
    printf("assigned givenItem\n" );
    form->isAssigned[itemIndex] = 1;
    printf("changed isAssigned\n" );
    if (itemIndex > form->effectiveSize){
        printf("entered effectiveSize if\n" );
        form->effectiveSize = itemIndex + 1;
        printf("changed effectiveSize\n" );
    }
    printf("exited assign\n" );
}


void LinearFree(LinearForm *form){
    for (int i = 0; i < form->maximumSize; ++i){
        free(form->arrayPointer[i]);
    }
    free(form->arrayPointer);
    free(form->isAssigned);
}





/*int main(void){
    return 0;
}*/
