#include <stdio.h>
#include "matrix.h"


int main(int argc, char* argv[])
{
	float a[3][3] = {
        { 1.0f, -2.0f,  3.0f},
        { 5.0f, -3.0f,  0.0f},
        {-2.0f,  1.0f, -4.0f}
    };
	float b[3][3];
	float c[3][3];

    init_zero_matrix(b);
    init_identity_matrix(b);
    b[1][1] =  8.0f;
    b[2][0] = -3.0f;
    b[2][2] =  5.0f;
    printf("A:\n");
    print_matrix(a);
    printf("B:\n");
    print_matrix(b);
    printf("A+B\n");
    add_matrices(a, b, c);
    print_matrix(c);
    printf("3*A\n");
    multiply_scalar(a,3.0f, c);
    print_matrix(c);
    printf("A*B\n");
    multiply_matrices(a,b,c);
    print_matrix(c);
    float vector[3][1]={{3.0f},{2.0f},{1.0f}};
    float result[3][1];
    print_vector(vector);
    printf("Identity matrix shifted (1,1):\n");
    init_identity_matrix(c);
    shift(c, 1, 1);
    print_matrix(c);
    transform_point(c, vector, result);
    print_vector(result);
    printf("Identity matrix scaled (2,2):\n");
    init_identity_matrix(c);
    scale(c, 2, 2);
    print_matrix(c);
    transform_point(c, vector, result);
    print_vector(result);
    printf("Identity matrix rotate by 90 deg:\n");
    init_identity_matrix(c);
    rotate(c, 90);
    print_matrix(c);
    transform_point(c, vector, result);
    print_vector(result);

	return 0;
}

