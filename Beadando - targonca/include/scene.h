#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include "utils.h"
#include "forklift.h"
#include "pallet.h"
#include <stdbool.h>

#include <obj/model.h>


//jatek jelenet darabjainak egyuttese
typedef struct Scene
{
    //targonca, raklap es skybox
    Forklift forklift;
    Pallet pallet;
    Model skybox;
    //skybox kozeppont koordinatai
    vec3 skybox_position;
    //skybox elfordulasi sebessege es szoge
    float skybox_angle;
    float skybox_speed;
    //skybox texturak halmaza, az elso harom kulonbozik, a negyedikbe kerul mindig az aktualisan betoltendo azonositoja
    GLuint skybox_texture_id[4];
    //kerites, ut es epulet modellek, texturaik
    Model fence;
    Model road;
    Model buildings[4];
    GLuint building_texture_ids[4];
    GLuint road_texture_id;
    GLuint ground_texture_id;
    GLuint grass_texture_id;
    //az origot es az epuleteket kirajzolo display listak indexei
    GLuint index_list_origin;
    GLuint index_list_buildings;
    //a hatterelemek anyaga
    Material material;

    //a fo fenyforras kornyezeti es diffuz osszetevoi
    float ambient_light[4];
    float diffuse_light[4];

    //a terulet utkozodoboza, amire a targonca mozgasa korlatozodik
    Bounding_box arena;

    //lathato-e eppen a hasznalati utmutato, tovabba annak texturaja
    bool is_manual_visible;
    GLuint instructions_texture_id;
} Scene;

//modell, texture betoltes, display listak letrehozasa
void init_scene(Scene* scene);

//fo feny beallitasa
void set_lighting(const Scene *scene);

//anyag beallitasa
void set_material(const Material* material);

//jelenet elemeinek beallitasa ido fuggvenyeben
void update_scene(Scene* scene, double time);

//a skybox beallitasa a kamera pozicio fuggvenyeben (koveti a kamerat)
void update_skybox_position(Scene* scene, vec3 pos);

//objektumok kirajzolasa
void render_scene(Scene* scene);

//koordinatatengelyek kirajzolasa teszteleshez
void draw_origin();

//targonca placcanak es a tavolabbi fuves reszeknek kirajzolasa
void draw_terrain(Scene *scene);

//feny novelese es csokkentese, egyben napszakvaltassal is jarhat (skybox texturacsere)
void increase_light(Scene *scene);
void decrease_light(Scene *scene);

#endif /* SCENE_H */
