#ifndef PALLET_H
#define PALLET_H

#include <stdbool.h>
#include <obj/model.h>
#include <GL/gl.h>
#include "boundingbox.h"

typedef struct Pallet{
    Model model;
    GLuint texture_id;
    GLuint road_texture_id;
    float position[3];
    float dimensions[3];
    float lifted_position[3];
    float angle;
    Bounding_box box;
    bool is_lifted;
    bool is_green;
} Pallet;

void init_pallet(Pallet *pallet, GLuint road_texture_id);
void update_pallet(Pallet *pallet, float* pos, float angle);
void render_pallet(Pallet *pallet);
void up_down_pallet(Pallet *pallet, bool is_fork_down);
#endif