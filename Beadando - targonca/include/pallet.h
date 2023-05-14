#ifndef PALLET_H
#define PALLET_H

#include <stdbool.h>
#include <obj/model.h>
#include <GL/gl.h>
#include "boundingbox.h"

//raklap
typedef struct Pallet{
    //modell
    Model model;
    //texturak, az ut a vetett arnyekhoz kell
    GLuint texture_id;
    GLuint road_texture_id;
    //kozeppont koordinatak, meretek
    float position[3];
    float dimensions[3];
    float lifted_position[3];
    //y tengelyhez kepesti elfordulas
    float angle;
    //utkozodoboz
    Bounding_box box;
    //fel van-e eppen emelve
    bool is_lifted;
    //zold szinu-e: akkor az, ha emeleshez megfeleloen kozel van hozza a targonca
    bool is_green;
} Pallet;

//raklap adatok inicializalasa
void init_pallet(Pallet *pallet, GLuint road_texture_id);
//raklap adatok frissitese uj helyzettel, szoggel
void update_pallet(Pallet *pallet, float* pos, float angle);
//raklap kirajzolasa, ha emelve van, akkor a letetel helyen is lesz egy teglalap
void render_pallet(Pallet *pallet);
//raklap felvetele, letevese (csak ha a villa megfelelo pozicioju es leteveskor nem kerul ki a raklap az arenabol)
void up_down_pallet(Pallet *pallet, Bounding_box *arena, bool is_fork_down);
#endif