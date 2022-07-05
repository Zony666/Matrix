#include"matrix.h"
int main(){
    DATA_TYPE d[]={
        1,2,3,
        2,2,1,
        3,4,3
    };
    DATA_TYPE d_[]={
        1,2,
        2,2,
        3,4,
    };
    CREATE_MATRIX_ONSTACK(3,3,m1,d);
    CREATE_MATRIX_ONSTACK(3,3,m2,d);
    CREATE_MATRIX_ONSTACK(3,2,m3,d_);
    CREATE_MATRIX_ONSTACK(3,2,res,d_);
    printf("Matrix m1:");
    dispMatrix(&m1);
    printf("\nTransposed m1:");
    transMatrix(&m1,&m2);
    dispMatrix(&m2);
    printf("\nThe m1 determinant:%f\n",detMatrix(&m1));
    printf("\nInverse m1:");
    invMatrix(&m1,&m2);
    dispMatrix(&m2);
    printf("---------------------------\n");
    printf("Matrix m3:");
    dispMatrix(&m3);
    multiMatrix(&m1,&m3,&res);
    printf("m1*m3:");
    dispMatrix(&res);
    return 0;
}