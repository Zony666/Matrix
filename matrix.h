#ifndef _matrix_h_
#define _matrix_h_
#include <stdio.h>
#include <stdlib.h>
typedef unsigned char uint8;
typedef float DATA_TYPE;

/* 
矩阵 结构体
成员：
    rows:行数, 
    cols:列数, 
    element:元素指针
*/
typedef struct Matrix
{
    uint8 rows,cols;
    DATA_TYPE* element;
}Matrix;


#define CREATE_MATRIX_ONSTACK(x,y,matrix,initval) \
Matrix matrix;\
DATA_TYPE val##matrix[x*y];\
    matrix.rows = x;\
    matrix.cols = y;\
    matrix.element = val##matrix;\
    if(initval!=NULL) setMatrix(initval, &(matrix));

#define CREATE_DYNAMIC_MATRIX_ONHEAP(x,y,matrix,initval) \
Matrix *matrix = (Matrix*)malloc(sizeof(Matrix));\
matrix->rows = x;\
matrix->cols = y;\
matrix->element = (DATA_TYPE*) malloc(sizeof(DATA_TYPE)*(x)*(y));\
if(initval!=NULL) setMatrix(initval, (matrix));

#define DELETE_DYNAMIC_MATRIX(matrix) \
    free((matrix)->element);\
    free(matrix);


//数组->矩阵赋值
Matrix* setMatrix(DATA_TYPE* const a,Matrix* c);
//复制矩阵
Matrix* copyMatrix(Matrix* const a,Matrix* c);
//行列设置矩阵元素值   row>=1 col>=1
void setMatrixElement(Matrix* c,uint8 row,uint8 col,DATA_TYPE val);
//行列获取矩阵元素值   row>=1 col>=1
DATA_TYPE getMatrixElement(Matrix* const a,uint8 row,uint8 col);
//矩阵转置
Matrix* transMatrix(Matrix* const a,Matrix* a_T);
//方阵转置，不需要额外的空间
Matrix* transMatrix_self(Matrix*a);
//计算余子式         row>=0 col>=0
Matrix* cofactor(uint8 row,uint8 col,Matrix* const in,Matrix* out);
// 矩阵行列式计算
DATA_TYPE detMatrix(Matrix* const a);
//计算伴随矩阵 Adjoint 伴随
Matrix* adjMatrix(Matrix* const in,Matrix* out);
//计算逆矩阵
DATA_TYPE invMatrix(Matrix* const a,Matrix*b);
// 数乘矩阵
Matrix* scaleMatrix(DATA_TYPE s,Matrix*const a,Matrix*c);
//矩阵乘法
Matrix* multiMatrix(Matrix* const a, Matrix* const b,Matrix* c);
//矩阵加法
Matrix* addMatrix(Matrix* const a, Matrix* const b,Matrix* c);
//矩阵简法
Matrix* subMatrix(Matrix* const a, Matrix* const b,Matrix* c);
//控制台输出矩阵
void dispMatrix(Matrix* const a);
#endif