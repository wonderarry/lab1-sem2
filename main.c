#include "headerFile.h"


void ComplexAdd(LinearForm *formMain, const LinearForm *formAdded, const int sign){ //Allows to sum values of two LinearForm, given that they store 2 double values as coefficients
    double **x = (double**)formMain->arrayPointer;
    double **y = (double**)formAdded->arrayPointer;
    //printf("x and y assigned\n");
    if (formMain->maximumSize < LinearLength(formAdded)){
        LinearResize(formMain, LinearLength(formAdded));
        //printf("we're inside if\n");
    }
    //printf("we're after if\n");
    //printf("%d linearlength\n", LinearLength(formAdded));
    for (int i = 0; i < LinearLength(formAdded); ++i){
        //printf("i == %d\n", i);
        if (formMain->isAssigned[i] == 1 && formAdded->isAssigned[i] == 1){
            //printf("entered the for if\n");
            x[i][0] += y[i][0] * sign;
            x[i][1] += y[i][1] * sign;
        }
    }
    //printf("we're after for\n");
    if (LinearLength(formMain) < LinearLength(formAdded)){
        //printf("we're inside second if\n");
        formMain->effectiveSize = LinearLength(formAdded);
    }
    //printf("we're after second if\n");
}


void ComplexMultiply(LinearForm *form, const double *multiplier){ //Allows to multiply values of two LinearForm, given that they store 2 double values as coefficients
    double **x = (double**)form->arrayPointer;
    double *y = (double*)multiplier;
    //printf("multi assigned\n" );
    for (int i = 0; i < LinearLength(form) + 1; ++i){
        if (form->isAssigned[i] == 1){
            x[i][0] = x[i][0] * y[0] - x[i][1] * y[1];
            x[i][1] = x[i][0] * y[1] + x[i][1] * y[0];
        }
    }
}


double *ComplexValue(LinearForm *form, const double **valueArray){ //Allows to calculate the value of a LinearForm, given that it stores 2 double values as coefficients
    double *resultPointer = calloc(2, sizeof(double));
    double **x = (double**)form->arrayPointer;

    for (int i = 0; i < LinearLength(form); ++i){
        if (x[i] != NULL){
            resultPointer[0] += x[i][0] * valueArray[i][0] - x[i][1] * valueArray[i][1];
            resultPointer[1] += x[i][0] * valueArray[i][1] + x[i][1] * valueArray[i][0];
        }
    }

    return resultPointer;
}

void UILinearAssign(LinearForm *form){
    int enteredIndex;
    double* assignedValue = malloc(2 * sizeof(double));
    printf("------------Assigning value to the LinearForm coefficient------------\n");
    printf("Enter item index: ");
    scanf("%d\n", enteredIndex);
    printf("Enter the real part of the coefficient: ");
    scanf("%f\n", assignedValue[0]);
    printf("Enter the iamginary part of the coefficient: ");
    scanf("%f\n", assignedValue[1]);
    LinearAssign(&form, enteredIndex, (void*)assignedValue);
    printf("------------Assigned [(%f) + (%f) * i] to the index %d------------\n", assignedValue[0], assignedValue[1], enteredIndex);
}

void UILinearMultiply(LinearForm *form){
    double* multiplier = malloc(2 * sizeof(double));
    printf("------------Multiplying LinearForm------------\n");
    printf("Enter the real part of the multiplier: ");
    scanf("%f\n", multiplier[0]);
    printf("Enter the iamginary part of the multiplier: ");
    scanf("%f\n", multiplier[1]);
    form->LinearMultiply(&form, multiplier);
    printf("------------Multiplied the LinearForm by coefficient [(%f) + (%f) * i]------------\n", multiplier[0], multiplier[1]);
}

void UILinearValue(LinearForm *form){
    double **valueArray = malloc(LinearLength(form) * sizeof(double*));
    printf("------------Calculating value of LinearForm------------\n");
    for (int i = 0; i < LinearLength(form); ++i){
        printf("Assigning x%d:\n", i);
        valueArray[i] = malloc(2 * sizeof(double));
        printf("Enter the real part of the variable: ");
        scanf("%f\n", valueArray[i][0]);
        printf("Enter the iamginary part of the variable: ");
        scanf("%f\n", valueArray[i][1]);
    }
    double *resultPointer = form->LinearValue(form, (void**)valueArray);
    printf("Result is [(%f) + (%f) * i]\n", resultPointer[0], resultPointer[1]);
    printf("------------Finished calculating------------\n");
}


int main(void){
    LinearForm x = {0, 0, NULL, ComplexAdd, ComplexMultiply, (void*)ComplexValue, NULL};
    LinearForm y = {0, 0, NULL, ComplexAdd, ComplexMultiply, (void*)ComplexValue, NULL};
    double* assignedX = malloc(2*sizeof(double));
    double* assignedY = malloc(2*sizeof(double));
    assignedX[0] = 223.0;
    assignedX[1] = 13453.0;
    assignedY[0] = 220.0;
    assignedY[1] = 13450.0;
    LinearAssign(&y, 3, (void*)assignedY);
    //printf("it just doesn't work\n" );
    LinearAssign(&x, 3, (void*)assignedX);

    double **values = (double**)x.arrayPointer;
    //printf("Real value by index 3: %f\n Imaginary value by index 3: %f\n", values[3][0], values[3][1]);
    //printf("x done;\n");

    //printf("something goes wrong here\n" );

    //printf("assigned y 0: %f 1: %f\n",assignedY[0], assignedY[1] );

    //printf("x linearlength: %d\n", LinearLength(&x));
    x.LinearAdd(&x, &y, -1);
    //printf("Real value by index 3: %f\n Imaginary value by index 3: %f\n", values[3][0], values[3][1]);
    //printf("x isAssigned %d\ny isAssigned%d\n",x.isAssigned[3], y.isAssigned[3] );
    x.LinearMultiply(&x, assignedY);
    //printf("multi done\n" );
    //double* valuesForCalculation = malloc(2*sizeof(double));
    //valuesForCalculation[0] = 3;
    //valuesForCalculation[1] = 4;
    //double *answer = x.LinearValue(&x, valuesForCalculation);
    //printf("real: %f imag: %f\n", answer[0], answer[1]);
    //double** values = calloc(4, sizeof(double*));
    //for (int i = 0; i < 4; ++i){
    //    values[i] = calloc(2, sizeof(double));
    //}
    //values[3][0] = 2.0;
    //values[3][1] = 4.0;

    //double *returned = LinearValue(&x, values);

    //printf("%f\n%f\n", x.arrayPointer[3][0], x.arrayPointer[3][1]);
    //printf("%f\n%f\n", values[3][0], values[3][1]);
    //printf("%f\n%f\n", returned[0], returned[1]);

    //LinearAssign(&y, 3, 220.0, 13400.0);
    //LinearAdd(&x, &y, -1);
    //returned = LinearValue(&x, values);
    //printf("%f\n%f\n", returned[0], returned[1]);
    return 0;

}
