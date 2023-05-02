#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H
#include "utils.h"
#include <stdbool.h>

typedef struct Bounding_box{
    float dimensions[3];
    float center[3];
    float diagonal_angle; //radian
    float diagonal;
    vec4 fr; //front right
    vec4 fl;
    vec4 br;
    vec4 bl;
} Bounding_box;

void init_bounding_box(Bounding_box *box, float* dimensions, float* center);
void update_bounding_box(Bounding_box *box, float *cur_position, float angle);
void draw_bounding_box(const Bounding_box *box);
bool is_colliding(const Bounding_box box1, const Bounding_box box2);
bool is_inside(const Bounding_box box1, const Bounding_box box2);

#endif