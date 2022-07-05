#include "matrix.h"

uint8 isSquareMatrix(Matrix* mat){
    if(mat->cols!=mat->rows) return 0;
    else return 1;
}
uint8 isSameShape(Matrix* m1,Matrix*m2){
    if(m1->cols==m2->cols&&m1->rows==m2->rows)return 1;
    else return 0;
}

Matrix* setMatrix(DATA_TYPE* const a,Matrix* c){
    uint8 col=c->cols;
    uint8 row=c->rows;
    for(int i=0;i<col*row;i++){
        c->element[i]=a[i];
    }
    return c;
}

Matrix* copyMatrix(Matrix* const a,Matrix* c){
    for(int i=0;i<(c->cols*c->rows);i++){
        c->element[i]=a->element[i];
    }
    return c;
}
void setMatrixElement(Matrix* a,uint8 row,uint8 col,DATA_TYPE val){
    a->element[(row-1)*a->cols+(col=1)]=val;
}
DATA_TYPE getMatrixElement(Matrix* const a,uint8 row,uint8 col){
    return a->element[(col-1)*a->rows+row-1];
}

Matrix* transMatrix(Matrix* const a,Matrix* c){
    if(a->rows!=c->cols) return NULL;
    if(a->cols!=c->rows) return NULL;
    uint8 x=a->rows;
    uint8 y=a->cols;

    for(int i=0;i<x;i++){
        for (int j=0;j<y;j++){
            c->element[j*x+i]=a->element[i*y+j];
        }
    }
    return c;
}
Matrix* transMatrix_self(Matrix*a){
    if(!isSquareMatrix(a))return NULL;
    uint8 x=a->rows;
    uint8 y=a->cols;
    DATA_TYPE tmp;
    for(int i=0;i<x;i++){
        for (int j=i;j<y;j++){
            tmp=a->element[i*y+j];
            a->element[i*y+j]=a->element[j*x+i];
            a->element[j*x+i]=tmp;
        }
    }
    return a;
}
Matrix* cofactor(uint8 row,uint8 col,Matrix* const in,Matrix* out) {
    if(!isSquareMatrix(in))return NULL;
    if(!isSquareMatrix(out))return NULL;
    if(in->rows != (out->rows+1)) return NULL;
    uint8 x=in->rows;
    uint8 y=in->cols;
    uint8 idx=0;
    uint8 sidx=0;
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            if(!(i==row||j==col)) {
                out->element[idx] = in->element[sidx];
                idx++;
            }
            sidx++;
        }
    }
    return out;
}
DATA_TYPE detMatrix(Matrix* const in){
    uint8 x = in->rows;
    uint8 y = in->cols;
    if(x!=y) {
        printf("ERROR:Det Matrix input is not sqare matrix!");
        return 0;
    }
    if(x==0 ) {
        printf("ERROR:Det Matrix input is zero!");
        return 0;
    }
    if(x==1 ) return in->element[0];
    DATA_TYPE *a =in->element;
    if(x==2) return(a[0]*a[3]-a[1]*a[2]);
    
    DATA_TYPE result = 0;
    signed char sign = 1;
    CREATE_DYNAMIC_MATRIX_ONHEAP(x-1,y-1,ret,NULL);
    for(uint8 i=0;i<y;++i) {
        cofactor(0,i,in,ret);
        result += sign*a[i]*detMatrix(ret);
        sign = - sign;
    }
    DELETE_DYNAMIC_MATRIX(ret);
    return result;

}
Matrix* adjMatrix(Matrix* const in,Matrix* out) {
    if(!isSameShape(in,out))return NULL;
    int index = 0;
    uint8 x = in->rows;
    uint8 y = in->cols;
    CREATE_DYNAMIC_MATRIX_ONHEAP(x-1,y-1,ret,NULL);
    signed char sign1 = 1;
    signed char sign2 = 1;
    for(uint8 ii=0;ii<x;++ii) {
        sign2 = sign1;
        index = ii;
        for(uint8 jj=0;jj<y;++jj) {
            cofactor(ii,jj,in,ret);
            out->element[index] = sign2*detMatrix(ret);
            sign2 = - sign2;    
            index+=y;
        }

        sign1 = - sign1;
    }
    DELETE_DYNAMIC_MATRIX(ret);
    return out;
}
DATA_TYPE invMatrix(Matrix* const a,Matrix*b){
    DATA_TYPE d=detMatrix(a);
    if(d==0) return 0;
    adjMatrix(a,b);
    scaleMatrix(1/d,b,b);
    return 1;
}
Matrix* scaleMatrix(DATA_TYPE s,Matrix*const a,Matrix*c){
    if(!isSameShape(a,c)) return NULL;
    uint8 t=a->cols*a->rows;
    for (uint8 i = 0; i < t; i++)
    {
        c->element[i]=s*a->element[i];
    }
    return c;
}
Matrix* multiMatrix(Matrix* const a, Matrix* const b,Matrix* c){
    if(a->cols!=b->rows)return NULL;
    if(c==a||c==b)return NULL;
    if(c->rows!=a->rows||c->cols!=b->cols)return NULL;
    for(int i=0;i<a->rows;i++){
        for(int m=0;m<b->cols;m++){
            c->element[i*c->cols+m]=0;
            for(int j=0;j<a->cols;j++){
                c->element[i*c->cols+m]+=a->element[i*a->cols+j]*b->element[j*b->cols+m]; 
            }   
        }
    }
    return c;
}
Matrix* addMatrix(Matrix* const a, Matrix* const b,Matrix* c){
    if(!isSameShape(a,b))return NULL;
    if(!isSameShape(c,b))return NULL;
    uint8 t=a->rows*a->cols;
    for (uint8 i = 0; i < t; i++)
    {
        c->element[i]=a->element[i]+b->element[i];
    }
    return c;
}
Matrix* subMatrix(Matrix* const a, Matrix* const b,Matrix* c){
    if(!isSameShape(a,b))return NULL;
    if(!isSameShape(c,b))return NULL;
    uint8 t=a->rows*a->cols;
    for (uint8 i = 0; i < t; i++)
    {
        c->element[i]=a->element[i]-b->element[i];
    }
    return c;
}
void dispMatrix(Matrix* const a){
    printf("\n");
    for(int i=0;i<a->rows;i++){
        for(int j=0;j<a->cols;j++){
            printf("%.3f  ",a->element[i*a->cols+j]);
        }
        printf("\n");
    }
}


