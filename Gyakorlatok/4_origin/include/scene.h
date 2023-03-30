#ifndef SCENE_H
#define SCENE_H

#include "camera.h"

typedef struct Scene
{
    double sphere_angle;
    double sphere_rotspeed;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Update the scene.
 */
void update_scene(Scene* scene);

/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();
void draw_triangle();
void draw_chess();
void draw_cylinder();
void draw_sphere(Scene *scene);
void draw_cone();

#endif /* SCENE_H */
