#ifndef LIGHT_H
#define LIGHT_H

#include <stdbool.h>

typedef struct Light {
    float position1[4];
    float position2[4];
    float direction[3];
    float ambient[4];
    float diffuse[4];
    float specular[4];
    float cutoff;
} Light;
void init_light(Light* light);
void update_light(Light *light, float pos1[4], float pos2[4], float dir[3]);
void set_light(Light *light, bool is_on);

#endif