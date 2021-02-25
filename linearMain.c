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


struct imported{
    int effectiveSize;
    int maximumSize;
    double **arrayPointer;
};

typedef struct imported LinearForm;


int LinearLength(const LinearForm *form){
    return form->effectiveSize;
}


void LinearInit(LinearForm *form){
    form->arrayPointer = calloc(1, sizeof(double*));
    form->arrayPointer[0] = calloc(2, sizeof(double));

    form->maximumSize = 1;
}


void LinearResize(LinearForm *form, const int newLength){
    if (form->maximumSize = 0){
        LinearInit(form);
    }

    form->arrayPointer = realloc(form->arrayPointer, newLength);
    for (int i = LinearLength(form) + 1; i < newLength; ++i){
        form->arrayPointer[i] = calloc(2, sizeof(double));
    }
}


void LinearAssign(LinearForm *form, const int itemIndex, const double itemValueRe, const double itemValueIm){
    if (form->maximumSize <= itemIndex){
        LinearResize(form, itemIndex * 2);
    }

    form->arrayPointer[itemIndex][0] = itemValueRe;
    form->arrayPointer[itemIndex][1] = itemValueIm;

    if (LinearLength(form) < itemIndex){
        form->effectiveSize = itemIndex + 1;
    }
}


double *LinearValue(LinearForm *form, const double **valueArray){
    double *resultPointer = calloc(2, sizeof(double));

    for (int i = 0; i < LinearLength(form); ++i){
        resultPointer[0] += form->arrayPointer[i][0] * valueArray[i][0] - form->arrayPointer[i][1] * valueArray[i][1];
        resultPointer[1] += form->arrayPointer[i][0] * valueArray[i][1] + form->arrayPointer[i][1] * valueArray[i][0];
    }

    return resultPointer;
}


void LinearAdd(LinearForm *formMain, const LinearForm *formAdded, const int sign){
    if (formMain->maximumSize < LinearLength(formAdded)){
        LinearResize(formMain, LinearLength(formAdded));
    }

    for (int i = 0; i < LinearLength(formAdded); ++i){
        formMain->arrayPointer[i][0] += formAdded->arrayPointer[i][0] * sign;
        formMain->arrayPointer[i][1] += formAdded->arrayPointer[i][1] * sign;
    }

    if (LinearLength(formMain) < LinearLength(formAdded)){
        formMain->effectiveSize = LinearLength(formAdded);
    }
}


void LinearMultiply(LinearForm *form, const double *multiplier){
    for (int i = 0; i < LinearLength(form) + 1; ++i){
        form->arrayPointer[i][0] = form->arrayPointer[i][0] * multiplier[0] - form->arrayPointer[i][1] * multiplier[1];
        form->arrayPointer[i][1] = form->arrayPointer[i][0] * multiplier[1] + form->arrayPointer[i][1] * multiplier[0];
    }
}


/*int main(void){
    return 0;
}*/
