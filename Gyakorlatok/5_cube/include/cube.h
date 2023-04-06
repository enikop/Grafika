#ifndef CUBE_H
#define CUBE_H

#include "texture.h"

#include <obj/model.h>

typedef struct Cube
{
    Model cube_model;
    GLuint texture_id;
    float x;
    float y;
    float z;
    float angle;
    float rotation_speed;

} Cube;
void init_cube(Cube *cube);
void update_cube(Cube *cube, double time);
void render_cube(const Cube *cube);

#endif
