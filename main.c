#include "headerFile.h"


void ComplexAdd(LinearForm *formMain, const LinearForm *formAdded, const int sign){ //Allows to sum values of two LinearForm, given that they store 2 double values as coefficients
    printf("entered ComplexAdd\n");
    double **x = (double**)formMain->arrayPointer;
    printf("got first arrayPointer\n");
    double **y = (double**)formAdded->arrayPointer;
    printf("got second arrayPointer\n");
    if (formMain->maximumSize < LinearLength(formAdded)){
        printf("entered if: first form has maximumSize < than LinearLength of the second form. will go to LinearResize\n");
        LinearResize(formMain, LinearLength(formAdded));
        printf("exited LinearResize\n");
    }
    printf("exited if: first form has maximumSize < than LinearLength of the second form\n" );
    for (int i = 0; i < LinearLength(formAdded); ++i){
        printf("entered for loop, i = %d\n", i);
        if (formMain->isAssigned[i] == 1 && formAdded->isAssigned[i] == 1){
            printf("entered if: formMain->isAssigned[i] == 1 && formAdded->isAssigned[i] == 1\n");
            x[i][0] += y[i][0] * sign;
            x[i][1] += y[i][1] * sign;
            printf("assignment completed for i = %d\n", i);
        }
    }
    printf("exited for loop\n" );
    if (LinearLength(formMain) < LinearLength(formAdded)){
        printf("entered if: LinearLength(formMain) < LinearLength(formAdded)\n");
        formMain->effectiveSize = LinearLength(formAdded);
        printf("formMain->effectiveSize = LinearLength(formAdded)\n");
    }
    printf("exited if: LinearLength(formMain) < LinearLength(formAdded)\n");
}


void ComplexMultiply(LinearForm *form, const double *multiplier){ //Allows to multiply values of two LinearForm, given that they store 2 double values as coefficients
    printf("entered ComplexMultiply. Going to create a double ** pointer - equivalent of the arrayPointer\n" );
    double **x = (double**)form->arrayPointer;
    printf("obtained arrayPointer of the form\n");
    double *y = (double*)multiplier;
    printf("obtained multiplier pointer\n");

    for (int i = 0; i < LinearLength(form) + 1; ++i){
        printf("entered for loop, i = %d\n", i);
        if (form->isAssigned[i] == 1){
            printf("entered if: form->isAssigned[i] == 1\n");
            x[i][0] = x[i][0] * y[0] - x[i][1] * y[1];
            x[i][1] = x[i][0] * y[1] + x[i][1] * y[0];
            printf("assignment completed for i = %d\n", i);
        }
    }
    free(y);
    printf("exited for loop, function end\n");
}


double *ComplexValue(LinearForm *form, const double **valueArray){ //Allows to calculate the value of a LinearForm, given that it stores 2 double values as coefficients
    printf("entered ComplexValue\n" );
    double *resultPointer = calloc(2, sizeof(double));
    printf("resultPointer callocated\n" );
    double **x = (double**)form->arrayPointer;
    printf("form arrayPointer pointer obtained\n");

    for (int i = 0; i < LinearLength(form); ++i){
        printf("entered for loop, i = %d \n", i);
        if (x[i] != NULL){
            printf("entered if: x[i] != NULL\n");
            resultPointer[0] += x[i][0] * valueArray[i][0] - x[i][1] * valueArray[i][1];
            resultPointer[1] += x[i][0] * valueArray[i][1] + x[i][1] * valueArray[i][0];
            printf("assignment completed for i = %d\n", i);
        }
    }
    printf("exited for loop, going to return resultPointer\n" );

    return resultPointer;
}


void UILinearAssign(LinearForm *form){
    int enteredIndex;
    double* assignedValue = calloc(2, sizeof(double));
    printf("------------Assigning value to the LinearForm coefficient------------\n");
    printf("Enter item index: ");
    scanf("%d", &enteredIndex);
    printf("\nEnter the real part of the coefficient: ");
    scanf("%lf", &assignedValue[0]);
    printf("\nEnter the imaginary part of the coefficient: ");
    scanf("%lf", &assignedValue[1]);
    printf("\nEntered values\n" );
    LinearAssign(form, enteredIndex, (void*)assignedValue);
    printf("Assigned val\n" );
    printf("\n------------Assigned [(%f) + (%f) * i] to the index %d------------\n", assignedValue[0], assignedValue[1], enteredIndex);
}


void UILinearMultiply(LinearForm *form){
    printf("entered UILinearMultiply\n" );
    //double* uniqueMultiplier = malloc(2 * sizeof(double) + 1);
    double uniqueMultiplier[2];
    printf("------------Multiplying LinearForm------------\n");
    printf("Enter the real part of the multiplier: ");
    scanf("%lf", &uniqueMultiplier[0]);
    printf("\nEnter the imaginary part of the multiplier: ");
    scanf("%lf", &uniqueMultiplier[1]);
    form->LinearMultiply(form, &uniqueMultiplier);
    printf("\n------------Multiplied the LinearForm by coefficient [(%f) + (%f) * i]------------\n", uniqueMultiplier[0], uniqueMultiplier[1]);
}


void UILinearValue(LinearForm *form){
    printf("entered LinearValue\n");
    double **valueArray = malloc(LinearLength(form) * sizeof(double*));
    printf("------------Calculating value of LinearForm------------\n");
    for (int i = 0; i < LinearLength(form); ++i){
        printf("Assigning x%d:\n", i);
        valueArray[i] = malloc(2 * sizeof(double));
        printf("Enter the real part of the variable: ");
        scanf("%lf", valueArray[i][0]);
        printf("\nEnter the imaginary part of the variable: ");
        scanf("%lf", valueArray[i][1]);
    }
    double *resultPointer = form->LinearValue(form, (void**)valueArray);
    printf("\nResult is [(%f) + (%f) * i]\n", resultPointer[0], resultPointer[1]);
    printf("------------Finished calculating------------\n");
}


int main(void){
    LinearForm x = {0, 0, NULL, ComplexAdd, ComplexMultiply, (void*)ComplexValue, NULL};
    LinearForm y = {0, 0, NULL, ComplexAdd, ComplexMultiply, (void*)ComplexValue, NULL};
    double* assignedY = malloc(2*sizeof(double));
    assignedY[0] = 220.0;
    assignedY[1] = 13450.0;
    LinearAssign(&y, 3, (void*)assignedY);

    UILinearAssign(&x);
    printf("finished LinearAssign\n" );
    x.LinearAdd(&x, &y, -1);
    printf("finised linearadd\n" );
    UILinearMultiply(&x);
    printf("finished LinearMultiply\n");
    UILinearValue(&x);

    double **values = (double**)x.arrayPointer;

    printf("\nReal - %f, imaginary - %f", values[3][0], values[3][1]);
    //x.LinearMultiply(&x, assignedY);
    return 0;

}
