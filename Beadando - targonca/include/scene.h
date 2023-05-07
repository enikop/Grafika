#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include "utils.h"
#include "forklift.h"
#include "pallet.h"
#include <stdbool.h>

#include <obj/model.h>

typedef struct Scene
{
    Forklift forklift;
    Pallet pallet;
    Model skybox;
    vec3 skybox_position;
    float skybox_angle;
    float skybox_speed;
    Model fence;
    Model road;
    Model buildings[4];
    GLuint building_texture_ids[4];
    GLuint road_texture_id;
    GLuint skybox_texture_id[3];
    GLuint ground_texture_id;
    GLuint grass_texture_id;
    GLuint index_list_origin;
    GLuint index_list_buildings;
    Material material;
    float ambient_light[4];
    float diffuse_light[4];
    Bounding_box arena;
    bool is_manual_visible;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting(const Scene *scene);

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene, double time);
void update_skybox_position(Scene* scene, vec3 pos);

/**
 * Render the scene objects.
 */
void render_scene(Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();
void draw_terrain(Scene *scene);
void increase_light(Scene *scene);

#endif /* SCENE_H */
