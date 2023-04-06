#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    load_model(&(scene->cat), "assets/models/cat.obj");
    load_model(&(scene->house), "assets/models/house.obj");
    //scene->texture_id = load_texture("assets/textures/cube.png");

    init_cube(&(scene->cube));
    scene->cat_forward = 0.0;
    scene->cat_forward_speed = 0.0;
    scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 0.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;
}

void set_lighting()
{
    float ambient_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0, 1.0f };
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene* scene, double time)
{
    scene->cat_forward += scene->cat_forward_speed/1000;
    update_cube(&(scene->cube), time);
}

void render_scene(const Scene* scene)
{
    set_material(&(scene->material));
    set_lighting();
    draw_origin();
    render_cube(&(scene->cube));
    glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);

    glColor3f(0,1,1);
    glTranslatef(-0.3, 0.0, 0.75);
    glScalef(0.05,0.05,0.05);
    glTranslatef(0.0, -scene->cat_forward, 0.0);
    glRotatef(90, 1, 0, 0);
    draw_model(&(scene->cat));
    glRotatef(-90, 1, 0, 0);
    glTranslatef(0.0, +scene->cat_forward, 0.0);
    glScalef(20,20,20);

    glTranslatef(0.3, 0.0, 0.0);
    glScalef(0.001,0.001,0.001);
    glRotatef(90, 1, 0, 0);
    glColor3f(0,0,1);
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
	
    glColor3f(1,1,1);
    glEnd();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
}


