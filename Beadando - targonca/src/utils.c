#include "utils.h"

#include <math.h>
#include <stdio.h>

void init_vector(vec4 *vector){
	vector->x = 0.0f;
	vector->y = 0.0f;
	vector->z = 0.0f;
	vector->w = 1.0f;
}
double degree_to_radian(double degree)
{
	return degree * atan(1)*4 / 180.0;
}
void print_matrix(float* mx)
{
    int i;
    int j;

    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j) {
            printf("%.4f ", mx[4*j+i]);
        }
        printf("\n");
    }
    printf("\n");
}
void print_vector(vec4 vector){
	printf("vector: %.4f %.4f %.4f %.4f\n", vector.x, vector.y, vector.z, vector.w);
}
void convert_to_vec4(vec3 input, vec4 *output){
	output->x=input.x;
	output->y=input.y;
	output->z=input.z;
	output->w=1.0f;
}
void multiply_by_matrix(float* mx, vec4 input, vec4 *output){
	output->x = input.x*mx[0]+input.y*mx[4]+input.z*mx[8]+input.w*mx[12];
	output->y = input.x*mx[1]+input.y*mx[5]+input.z*mx[9]+input.w*mx[13];
	output->z = input.x*mx[2]+input.y*mx[6]+input.z*mx[10]+input.w*mx[14];
	output->w = input.x*mx[3]+input.y*mx[7]+input.z*mx[11]+input.w*mx[15];
}
//Ax+By+C=0 alakban A=line.x stb
void construct_2d_line(vec4 point1, vec4 point2, vec3 *output){
	output->x=point2.y-point1.y;
	output->y=point1.x-point2.x;
	output->z= -(output->x*point1.x+output->y*point1.y);
}
void project_point_to_line(vec4 point, vec3 line, vec4 *output){
	float len =  pow(line.x * line.x + line.y * line.y, 0.5);
	float dist = (line.x * point.x + line.y * point.y + line.z) / len;
	output->x = point.x - dist * line.x / len;
	output->y = point.y - dist * line.y / len;

}


