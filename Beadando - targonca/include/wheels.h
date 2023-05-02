#ifndef WHEELS_H
#define WHEELS_H

#include "texture.h"

#include <obj/model.h>

typedef struct Set_of_wheels
{
    Model front_wheels;
    Model back_right;
    Model back_left;
    GLuint texture_id;
    float rot_angle;
    float rot_speed;
    float turn_speed;
    float turn_angle;
    float radius_ratio;

} Set_of_wheels;
void init_wheels(Set_of_wheels *wheels);
void update_wheels(Set_of_wheels *wheels, double time);
void render_wheels(const Set_of_wheels *wheels);
void set_turn_speed(Set_of_wheels *wheels, double speed);

#endif
