#ifndef FORKLIFT_H
#define FORKLIFT_H
#include <obj/model.h>
#include <stdbool.h>
#include "texture.h"
#include "wheels.h"
#include "light.h"
#include "boundingbox.h"
#include "pallet.h"

typedef struct Forklift
{
    Model cube_model;
    Set_of_wheels wheels;
    Model model;
    Model fork_model;
    Model steer_model;
    Material material1;
    Material material2;
    GLuint texture_id;
    GLuint fork_texture_id;
    float x;
    float y;
    float z;
    float r; //kanyarodas sugara
    float speed; //xy sikbeli sebesseg nagysaga
    float speed_z; //z iranyu sebesseg nagysaga
    float acceleration; //gyorsulas nagysaga
    float body_turn_angle; //xy sikbeli elfordulas RADIANBAN
    float body_turn_speed; //xy sikbeli elfodulas szogsebessege
    float steer_angle; //kormany elfodulasa FOKBAN, kerek*12
    float fork_speed; //villa felfele mozgasanak sebessege
    float fork_lift_height; //villa z pozicioja
    Bounding_box box;
    Bounding_box fork_box;
    Light spotlight;

} Forklift;
void init_forklift(Forklift *forklift);
void update_forklift(Forklift *forklift, double time, Pallet *pallet);
void render_forklift(Forklift *forklift);
void set_forklift_acceleration(Forklift *forklift, double acc);
void set_fork_speed(Forklift *forklift, double speed);
void stop_colliding_forklift(Forklift *forklift, double time);

#endif
