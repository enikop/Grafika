#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H
#include "utils.h"
#include <stdbool.h>

typedef struct Bounding_box{
    float dimensions[3]; //x,y,z iranyu kiterjedesek
    float center[3]; //kozeppont koordinatai
    float diagonal_angle; //az atlo oldallal bezart szoge radianban (ne kelljen ciklusonkent ujraszamolni)
    float diagonal; //a lapatlo nagysaga
    vec4 fr; //elso jobb pont koordinatai
    vec4 fl; //elso bal pont koordinatai
    vec4 br; //hatso jobb pont koordinatai
    vec4 bl; //hatso bal pont koordinatai
} Bounding_box;

//utkozodoboz inicializalasa, atlo es szogenek kiszamitasa
void init_bounding_box(Bounding_box *box, float* dimensions, float* center);
//utkozodoboz frissitese a kozeppont aktualis helyzete es a doboz y iranyu oldalanak y tengellyen bezart szoge segitsegevel
void update_bounding_box(Bounding_box *box, float *cur_position, float angle);
//doboz kirajzolasa teszteleshez
void draw_bounding_box(const Bounding_box *box);
//utkozik-e ket objektum
bool is_colliding(const Bounding_box box1, const Bounding_box box2);
//benne van-e box1-ben box2
bool is_inside(const Bounding_box box1, const Bounding_box box2);

#endif