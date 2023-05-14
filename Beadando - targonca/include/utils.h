#ifndef UTILS_H
#define UTILS_H

//3 dimenzios vektor
typedef struct vec3
{
    float x;
    float y;
    float z;
} vec3;

//4 dimenzios vektor
typedef struct vec4
{
    float x;
    float y;
    float z;
    float w;
} vec4;

//rgb szin
typedef struct Color
{
    float red;
    float green;
    float blue;
} Color;

//anyag
typedef struct Material
{
    struct Color ambient;
    struct Color diffuse;
    struct Color specular;
    float shininess;
} Material;

//fokbol radianba valtas
double degree_to_radian(double degree);

//matrix kiiras
void print_matrix(float *mx);

//Descartes koordinatak homogen koordinatakka
void convert_to_vec4(vec3 input, vec4 *output);

//Matrixok szorzasa
void multiply_by_matrix(float* mx, vec4 input, vec4 *output);

//vektor kiiras
void print_vector(vec4 vector);

//vektor inicializalas
void init_vector(vec4 *vector);

//2 pontra illeszkedo egyenes keplete Ax+By+C=0 alakra (A,B,C)-t ad vissza
void construct_2d_line(vec4 point1, vec4 point2, vec3 *output);

//pont meroleges vetitese egyenesre (utkozesvizsgalathoz)
void project_point_to_line(vec4 point, vec3 line, vec4 *output);

#endif /* UTILS_H */
