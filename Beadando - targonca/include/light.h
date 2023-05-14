#ifndef LIGHT_H
#define LIGHT_H

#include <stdbool.h>

//2 egyforma reflektor tipusu fenyforras GL_LIGHT1 és GL_LIGHT2 hasznalataval
typedef struct Light {
    //helyuk
    float position1[4];
    float position2[4];
    //vilagitas iranya
    float direction[3];
    //fenykomponenseik
    float ambient[4];
    float diffuse[4];
    float specular[4];
    //felnyilasszog
    float cutoff;
} Light;

//reflektorok inicializalasa
void init_light(Light* light);

//reflektorok frissitese megadott pozicioval es irannyal
void update_light(Light *light, float pos1[4], float pos2[4], float dir[3]);

//fenybeallitasok alkalmazasa, amennyiben az is_on ertek igaz
void set_light(Light *light, bool is_on);

#endif