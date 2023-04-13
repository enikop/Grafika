#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include "cube.h"

#include <obj/model.h>

typedef struct Scene
{
    Cube cube;
    Model cat;
    Model house;
    Material material;
    GLuint texture_id;
    float ambient_light[4];
    float diffuse_light[4];
    float cat_forward;
    float cat_forward_speed;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting(Scene *scene);

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene, double time);

/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();
void increase_light(Scene *scene);

#endif /* SCENE_H */
