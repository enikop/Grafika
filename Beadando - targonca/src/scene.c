#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

void init_scene(Scene *scene)
{
    load_model(&(scene->skybox), "assets/models/sky.obj");
    load_model(&(scene->fence), "assets/models/fence.obj");
    load_model(&(scene->road), "assets/models/road.obj");
    load_model(&(scene->buildings[0]), "assets/models/b1_ready.obj");
    load_model(&(scene->buildings[1]), "assets/models/b2_ready.obj");
    load_model(&(scene->buildings[2]), "assets/models/b3_ready.obj");
    load_model(&(scene->buildings[3]), "assets/models/b4_ready.obj");
    scene->skybox_texture_id[0] = load_texture("assets/textures/sky.jpg");
    scene->skybox_texture_id[1] = load_texture("assets/textures/sky_night.jpg");
    scene->skybox_texture_id[2] = scene->skybox_texture_id[0];
    scene->ground_texture_id = load_texture("assets/textures/beton.jpg");
    scene->road_texture_id = load_texture("assets/textures/road.jpg");
    scene->building_texture_ids[0]=load_texture("assets/textures/b1.jpg");
    scene->building_texture_ids[1]=load_texture("assets/textures/b2.jpg");
    scene->building_texture_ids[2]=load_texture("assets/textures/b3.jpg");
    scene->building_texture_ids[3]=load_texture("assets/textures/b4.jpg");

    init_forklift(&(scene->forklift));
    init_pallet(&(scene->pallet), scene->ground_texture_id);

    scene->skybox_angle=0;
    scene->skybox_speed=0.002;
    scene->is_manual_visible = false;

    float dimensions[] = {25.535f, 22.15f, 10.0f};
    float center[] = {-8.0f, 1.43f, 1.0f};
    init_bounding_box(&(scene->arena), dimensions, center);
    update_bounding_box(&(scene->arena), center, 0.0f);

    scene->material.ambient.red = 0.2;
    scene->material.ambient.green = 0.2;
    scene->material.ambient.blue = 0.2;

    scene->material.diffuse.red = 0.5;
    scene->material.diffuse.green =0.5;
    scene->material.diffuse.blue = 0.5;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 120.0;

    scene->diffuse_light[0] = 0.6f;
    scene->diffuse_light[1] = 0.3882f;
    scene->diffuse_light[2] = 0.2784f;
    scene->diffuse_light[3] = 1.0f;

    scene->ambient_light[0] = 0.125f;
    scene->ambient_light[1] = 0.125f;
    scene->ambient_light[2] = 0.125f;
    scene->ambient_light[3] = 1.0f;
    scene->index_list_origin = glGenLists(1);
    glNewList(scene->index_list_origin, GL_COMPILE);
    draw_origin();
    draw_terrain(scene);
    glEndList();

    scene->index_list_buildings=glGenLists(1);
    glNewList(scene->index_list_buildings, GL_COMPILE);
    int i;
    for(i=0; i<4; i++){
            glBindTexture(GL_TEXTURE_2D, scene->building_texture_ids[i]);
            glEnable(GL_TEXTURE_2D);
            draw_model(&(scene->buildings[i]));
        }
        glBindTexture(GL_TEXTURE_2D, scene->road_texture_id);
        glEnable(GL_TEXTURE_2D);
        glTranslatef(0,0,0.3f);
        draw_model(&(scene->road));
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_COLOR_MATERIAL);
        glColor3f(0.26f, 0.26f, 0.26f);
        draw_model(&(scene->fence));
        glColor3f(1,1,1);
        glEnable(GL_TEXTURE_2D);
        glDisable(GL_COLOR_MATERIAL);
    glEndList();
}
void increase_light(Scene *scene)
{
    scene->skybox_texture_id[2]= scene->skybox_texture_id[0];
    scene->diffuse_light[0] = 0.6f;
    scene->diffuse_light[1] = 0.3882f;
    scene->diffuse_light[2] = 0.4f;
    scene->diffuse_light[3] = 1.0f;
    if (scene->ambient_light[0] < 0.5)
    {
        scene->ambient_light[0] += 0.0625f;
        scene->ambient_light[1] += 0.0625f;
        scene->ambient_light[2] += 0.0625f;
    }
    else
    {
        scene->ambient_light[0] = 0.0f;
        scene->ambient_light[1] = 0.0f;
        scene->ambient_light[2] = 0.0f;
        scene->diffuse_light[0] = 0.0f;
        scene->diffuse_light[1] = 0.0f;
        scene->diffuse_light[2] = 0.0f;
        scene->diffuse_light[3] = 1.0f;
    }
    if(scene->ambient_light[0]<0.125f){
        scene->skybox_texture_id[2]= scene->skybox_texture_id[1];
    } else if(scene->ambient_light[0]<0.25){
        scene->diffuse_light[0] = 0.3f;
        scene->diffuse_light[1] = 0.19f;
        scene->diffuse_light[2] = 0.2f;
        scene->diffuse_light[3] = 1.0f;
    }
}
void set_lighting(const Scene *scene)
{
    /*float ambient_light[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float diffuse_light[] = {1.0f, 1.0f, 1.0, 1.0f};*/
    float specular_light[] = {0.3f, 0.3f, 0.3f, 1.0f};
    float position[] = {0.0f, 0.0f, 2.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, scene->ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, scene->diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glFogf(GL_FOG_MODE, GL_EXP2);
    glFogf(GL_FOG_DENSITY, 0.04);
    glFogf(GL_FOG_START, 50);
    glFogf(GL_FOG_END, 90);
    float fog[]={0.4f, 0.4f, 0.4f, 0.1f};
    glFogfv(GL_FOG_COLOR, fog);
    //glEnable(GL_FOG);
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
void show_manual()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, 1, -3);
    glTexCoord2f(1, 0);
    glVertex3f(1, 1, -3);
    glTexCoord2f(1, 1);
    glVertex3f(1, -1, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, -3);
    glEnd();

    glEnable(GL_CULL_FACE);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}
void update_skybox_position(Scene *scene, vec3 pos){
    scene->skybox_position.x = pos.x;
    scene->skybox_position.y = pos.y;
    scene->skybox_position.z = 3;
}
void update_scene(Scene *scene, double time)
{
    float distance;
    update_forklift(&(scene->forklift), time, &(scene->pallet));
    float pos[]={scene->forklift.x, scene->forklift.y, scene->forklift.fork_lift_height};
    update_pallet(&(scene->pallet),pos, scene->forklift.body_turn_angle);
    if(!is_inside(scene->arena, scene->forklift.box)){
        stop_colliding_forklift(&(scene->forklift), time);
    }
    scene->skybox_angle+=scene->skybox_speed;
    if(scene->skybox_angle>=360) scene->skybox_angle=0;
    distance = pow(pow(scene->pallet.position[0]-scene->forklift.x, 2)+pow(scene->pallet.position[1]-scene->forklift.y, 2), 0.5);
    if(distance<3 && !scene->pallet.is_lifted )scene->pallet.is_green=true;
    else scene->pallet.is_green=false;
    /*if(!scene->pallet.is_lifted && is_colliding(scene->forklift.box, scene->pallet.box)){
        stop_colliding_forklift(&(scene->forklift), time);
    }*/
}
void render_scene(Scene *scene)
{
    draw_bounding_box(&(scene->forklift.box));
    draw_bounding_box(&(scene->pallet.box));
    set_material(&(scene->material));
    set_lighting(scene);
    glCallList(scene->index_list_origin);
    glDisable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glPushMatrix();
        glTranslatef(10.0f, -10.0f, -0.8f);
       glCallList(scene->index_list_buildings);
    glPopMatrix();
    glPushMatrix();
        glRotatef(180, 0, 0, 1);
        glTranslatef(26.0f, -15.7f, -0.8f);
        glCallList(scene->index_list_buildings);
    glPopMatrix();
    glEnable(GL_CULL_FACE);
    glPushMatrix();
        glDisable(GL_COLOR_MATERIAL);
        glBindTexture(GL_TEXTURE_2D, scene->skybox_texture_id[2]);
        glEnable(GL_TEXTURE_2D);
        glTranslatef(scene->skybox_position.x, scene->skybox_position.y, scene->skybox_position.z);
        glRotatef(scene->skybox_angle, 0, 0,1);
        glScalef(3,3,3);
        draw_model(&(scene->skybox));
        glEnable(GL_COLOR_MATERIAL);
    glPopMatrix();
    glEnable(GL_LIGHTING);
    render_forklift(&(scene->forklift));
    render_pallet(&(scene->pallet));
    if(scene->is_manual_visible) show_manual();
}

void draw_terrain(Scene *scene){
    glEnable(GL_COLOR_MATERIAL);
    glBindTexture(GL_TEXTURE_2D, scene->ground_texture_id);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glTexCoord2f(0,128);
    glVertex3f(40, -40, -0.451667);
    glTexCoord2f(128,128);
    glVertex3f(40, 40, -0.451667);
    glTexCoord2f(0,128);
    glVertex3f(-40, 40, -0.451667);
    glTexCoord2f(0,0);
    glVertex3f(-40, -40, -0.451667);
    glEnd();
}
void draw_origin()
{
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(-3, 0, 0);
    glVertex3f(3, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, -3, 0);
    glVertex3f(0, 3, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glColor3f(1, 1, 1);
    glEnd();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
}