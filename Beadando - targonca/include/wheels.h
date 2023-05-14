#ifndef WHEELS_H
#define WHEELS_H

#include "texture.h"
#include <obj/model.h>

//4 kerek, hatso kerekek fordulokepesek
typedef struct Set_of_wheels
{
    //elso ket kerek tengellyek osszekotve es a ket hatso
    Model front_wheels;
    Model back_right;
    Model back_left;
    //textura
    GLuint texture_id;
    //forgas szoge es sebessege 
    float rot_angle;
    float rot_speed;
    //kanyarodo elfordulas szoge es sebessege
    float turn_speed;
    float turn_angle;
    //elso-hatso kerekek sugaranak aranya
    float radius_ratio;

} Set_of_wheels;

//kerekek inicializalasa
void init_wheels(Set_of_wheels *wheels);

//kerekek allasanak frissitese az ido fuggvenyeben
void update_wheels(Set_of_wheels *wheels, double time);

//kerekek kirajzolasa
void render_wheels(const Set_of_wheels *wheels);

//elfordulas sebessegenek beallitasa
void set_turn_speed(Set_of_wheels *wheels, double speed);

#endif
