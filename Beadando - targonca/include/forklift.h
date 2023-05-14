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
    //modellek
    Model model;
    Model fork_model;
    Model steer_model;
    //anyagok
    Material material_steel;
    Material material_rubber;
    GLuint texture_id; //targonca textura
    GLuint fork_texture_id; //villa textura
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
    Bounding_box box; //targonca befoglalo teglalap (2d)
    Bounding_box fork_box; //villa befoglalo teglalap
    Set_of_wheels wheels; //kerekek
    Light spotlight; //fenyszoro
    bool is_light_on; //be van-e kapcsolva a fenyszoro

} Forklift;

//modellek es texturak betoltese, ertek inicializalas
void init_forklift(Forklift *forklift);
//ertek frissites
void update_forklift(Forklift *forklift, double time, Pallet *pallet);
//a targonca kirajzolasa aktualis allapotaban
void render_forklift(Forklift *forklift);
//gyorsulas beallitasa
void set_forklift_acceleration(Forklift *forklift, double acc);
//villa sebesseg beallitasa
void set_fork_speed(Forklift *forklift, double speed);
//az arena hataraival utkozo targonca megallitasa
void stop_colliding_forklift(Forklift *forklift, double time);
//fenyszoro ki-bekapcsolasa
void switch_spotlight(Forklift *forklift);

#endif
