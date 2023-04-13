#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene *scene)
{
    load_model(&(scene->cat), "assets/models/untitled.obj");
    load_model(&(scene->house), "assets/models/house.obj");
    scene->texture_id = load_texture("assets/textures/Cat_diffuse.jpg");

    init_cube(&(scene->cube));
    scene->cat_forward = 0.0;
    scene->cat_forward_speed = 0.0;
    scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 0.0;

    scene->material.specular.red = 1.0;
    scene->material.specular.green = 1.0;
    scene->material.specular.blue = 1.0;

    scene->material.shininess = 20.0;

    scene->diffuse_light[0] = 0.6f;
    scene->diffuse_light[1] = 0.6f;
    scene->diffuse_light[2] = 0.6f;
    scene->diffuse_light[3] = 1.0f;

    scene->ambient_light[0] = 0.0f;
    scene->ambient_light[1] = 0.0f;
    scene->ambient_light[2] = 0.0f;
    scene->ambient_light[3] = 1.0f;
}
void increase_light(Scene *scene)
{
    if (scene->diffuse_light[0] < 1)
    {
        scene->diffuse_light[0] += 0.2f;
    }
    else
    {
        scene->diffuse_light[0] = 0.0f;
    }
    if (scene->diffuse_light[1] < 1)
    {
        scene->diffuse_light[1] += 0.2f;
    }
    else
    {
        scene->diffuse_light[1] = 0.0f;
    }
    if (scene->diffuse_light[2] < 1)
    {
        scene->diffuse_light[2] += 0.2f;
    }
    else
    {
        scene->diffuse_light[2] = 0.0f;
    }
}
void change_light_color(Scene *scene, double time)
{
    float colors[7][4] = {{0.58f, 0.0f, 0.83f}, {0.29f, 0.0f, 0.51f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}};
    int base = time;
    scene->ambient_light[0] = colors[base%7][0];
    scene->ambient_light[1] = colors[base%7][1];
    scene->ambient_light[2] = colors[base%7][2];
}
void set_lighting(Scene *scene)
{
    /*float ambient_light[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float diffuse_light[] = {1.0f, 1.0f, 1.0, 1.0f};*/
    float specular_light[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float position[] = {-3.0f, 5.0f, 10.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, scene->ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, scene->diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material *material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue};

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue};

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene *scene, double time)
{
    scene->cat_forward += scene->cat_forward_speed / 10;
    update_cube(&(scene->cube), time);
    change_light_color(scene, time);
}

void render_scene(const Scene *scene)
{
    set_material(&(scene->material));
    set_lighting(scene);
    draw_origin();
    render_cube(&(scene->cube));
    glBindTexture(GL_TEXTURE_2D, scene->texture_id);
    glEnable(GL_TEXTURE_2D);
    // glColor3f(0,1,1);
    glTranslatef(-0.3, 0.0, 0.75);
    glScalef(0.005, 0.005, 0.005);
    glTranslatef(-scene->cat_forward, 0.0, 0.0);
    draw_model(&(scene->cat));
    glTranslatef(+scene->cat_forward, 0.0, 0.0);
    glScalef(20, 20, 20);
    glBindTexture(GL_TEXTURE_2D, scene->cube.texture_id);
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_TEXTURE_2D);

    glTranslatef(3.0, 0.0, 0.0);
    glScalef(0.01, 0.01, 0.01);
    glRotatef(90, 1, 0, 0);
    glColor3f(1, 1, 1);
    draw_model(&(scene->house));
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_COLOR_MATERIAL);
}

void draw_origin()
{
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glColor3f(1, 1, 1);
    glEnd();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
}
