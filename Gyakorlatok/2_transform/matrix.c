#include "matrix.h"

#include <stdio.h>
#include <math.h>

void init_zero_matrix(float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            matrix[i][j] = 0.0;
        }
    }
}
void init_identity_matrix(float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            matrix[i][j] = 0.0;
            if(i==j) matrix[i][j] = 1.0;
        }
    }
}
void multiply_scalar(float matrix[3][3], float l, float result[3][3]){
    int i;
    int j;
    init_zero_matrix(result);
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            result[i][j]=l*matrix[i][j];
        }
    }
}
void multiply_matrices(float matrixa[3][3], float matrixb[3][3], float matrixc[3][3]){
    int i, j, k;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            matrixc[i][j]=0;
            for(k=0; k<3; k++){
                matrixc[i][j]+= matrixa[i][k]*matrixb[k][j];
            }
        }
    }
}
void transform_point(float matrix[3][3], float vector[3][1], float result[3][1]){
    int i;
    int j;
    for (i = 0; i < 3; ++i) {
        result[i][0]=0;
        for (j = 0; j < 3; ++j) {
            result[i][0]+=matrix[i][j]*vector[j][0];
        }
    }
}

void scale(float matrix[3][3], float s_x, float s_y){
    int i,j;
    float tmatrix[3][3];
    init_identity_matrix(tmatrix);
    float result[3][3];
    init_identity_matrix(result);
    tmatrix[0][0]=s_x;
    tmatrix[1][1]=s_y;
    multiply_matrices(tmatrix, matrix, result);
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            matrix[i][j]=result[i][j];
        }
    }

};
void shift(float matrix[3][3], float d_x, float d_y){
    int i,j;
    float tmatrix[3][3];
    init_identity_matrix(tmatrix);
    float result[3][3];
    init_identity_matrix(result);
    tmatrix[0][2]=d_x;
    tmatrix[1][2]=d_y;
    multiply_matrices(tmatrix, matrix, result);
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            matrix[i][j]=result[i][j];
        }
    }
};
void rotate(float matrix[3][3], float angle){
    int i,j;
    float anglerad=angle/180*(atan(1)*4);
    float tmatrix[3][3];
    init_identity_matrix(tmatrix);
    float result[3][3];
    init_identity_matrix(result);
    tmatrix[0][0]=cos(anglerad);
    tmatrix[0][1]=-sin(anglerad);
    tmatrix[1][0]=sin(anglerad);
    tmatrix[1][1]=cos(anglerad);
    multiply_matrices(tmatrix, matrix, result);
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            matrix[i][j]=result[i][j];
        }
    }

};

void print_matrix(const float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            printf("%4.4f ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void print_vector(const float vector[3][1])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        printf("%4.4f ", vector[i][0]);
        printf(" ");
    }
    printf("\n");
}


void add_matrices(const float a[3][3], const float b[3][3], float c[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

