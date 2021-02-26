#include "headerFile.h"

int main(void){

    LinearForm x = {0, 0, NULL}, y = {0, 0, NULL};
    LinearAssign(&x, 3, 223.0, 13453.0);

    double** values = calloc(4, sizeof(double*));
    for (int i = 0; i < 4; ++i){
        values[i] = calloc(2, sizeof(double));
    }
    values[3][0] = 2.0;
    values[3][1] = 4.0;

    double *returned = LinearValue(&x, values);

    printf("%f\n%f\n", x.arrayPointer[3][0], x.arrayPointer[3][1]);
    printf("%f\n%f\n", values[3][0], values[3][1]);
    printf("%f\n%f\n", returned[0], returned[1]);

    LinearAssign(&y, 3, 220.0, 13400.0);
    LinearAdd(&x, &y, -1);
    returned = LinearValue(&x, values);
    printf("%f\n%f\n", returned[0], returned[1]);
    return 0;

}
