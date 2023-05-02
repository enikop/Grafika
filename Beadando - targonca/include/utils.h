#ifndef UTILS_H
#define UTILS_H

/**
 * GLSL-like three dimensional vector
 */
typedef struct vec3
{
    float x;
    float y;
    float z;
} vec3;

typedef struct vec4
{
    float x;
    float y;
    float z;
    float w;
} vec4;


/**
 * Color with RGB components
 */
typedef struct Color
{
    float red;
    float green;
    float blue;
} Color;

/**
 * Material
 */
typedef struct Material
{
    struct Color ambient;
    struct Color diffuse;
    struct Color specular;
    float shininess;
} Material;

/**
 * Calculates radian from degree.
 */
double degree_to_radian(double degree);
void print_matrix(float *mx);
void convert_to_vec4(vec3 input, vec4 *output);
void multiply_by_matrix(float* mx, vec4 input, vec4 *output);
void print_vector(vec4 vector);
void init_vector(vec4 *vector);
void construct_2d_line(vec4 point1, vec4 point2, vec3 *output);
void project_point_to_line(vec4 point, vec3 line, vec4 *output);

#endif /* UTILS_H */
