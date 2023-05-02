#ifndef LIGHT_H
#define LIGHT_H

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
void update_light(Light *light, float pos1[4], float pos2[4], float dir[4]);
void set_light(Light *light);

#endif