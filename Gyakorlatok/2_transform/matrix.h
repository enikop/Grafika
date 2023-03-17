#ifndef MATRIX_H
#define MATRIX_H

/**
 * Initializes all elements of the matrix to zero.
 */
void init_zero_matrix(float matrix[3][3]);
void init_identity_matrix(float matrix[3][3]);
void multiply_scalar(float matrix[3][3], float l, float result[3][3]);
void multiply_matrices(float matrixa[3][3], float matrixb[3][3], float matrixc[3][3]);
void transform_point(float matrix[3][3], float vector[3][1], float result[3][1]);
void print_vector(const float vector[3][1]);

void scale(float matrix[3][3], float s_x, float s_y);
void shift(float matrix[3][3], float d_x, float d_y);
void rotate(float matrix[3][3], float angle);
/**
 * Print the elements of the matrix.
 */
void print_matrix(const float matrix[3][3]);

/**
 * Add matrices.
 */
void add_matrices(const float a[3][3], const float b[3][3], float c[3][3]);

#endif // MATRIX_H

