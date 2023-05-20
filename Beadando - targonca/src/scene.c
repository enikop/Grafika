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
    load_model(&(scene->road), "assets/models/road3.obj");
    load_model(&(scene->buildings[0]), "assets/models/b1_ready.obj");
    load_model(&(scene->buildings[1]), "assets/models/b2_ready.obj");
    load_model(&(scene->buildings[2]), "assets/models/b3.obj");
    load_model(&(scene->buildings[3]), "assets/models/b4_ready.obj");
    load_model(&(scene->container), "assets/models/container.obj");
    scene->skybox_texture_id[0] = load_texture("assets/textures/sky.jpg");
    scene->skybox_texture_id[1] = load_texture("assets/textures/sky_dawn2.jpg");
    scene->skybox_texture_id[2] = load_texture("assets/textures/sky_night.jpg");
    scene->skybox_texture_id[3] = scene->skybox_texture_id[0];
    scene->ground_texture_id = load_texture("assets/textures/beton.jpg");
    scene->grass_texture_id = load_texture("assets/textures/grass.jpg");
    scene->road_texture_id = load_texture("assets/textures/road.jpg");
    scene->container_texture_id = load_texture("assets/textures/container.jpg");
    scene->instructions_texture_id=load_texture("assets/textures/instructions.jpg");
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

    float cont_dimensions[]={1.72f, 3.12f, 1.9f};
    float cont_center[]={-19.8f, 0, 0.95f};
    init_bounding_box(&(scene->container_box), cont_dimensions, cont_center);
    update_bounding_box(&(scene->container_box), cont_center, 0.0f);

    float timer_pos[] = {2.4f, -1.3f};
    float hs_pos[] = {2.46f, -1.04f};
    init_timer(&(scene->timer), 1, timer_pos);
    init_timer(&(scene->high_score), 0.5, hs_pos);
    read_high_score(&(scene->high_score));

    scene->material.ambient.red = 0.1;
    scene->material.ambient.green = 0.1;
    scene->material.ambient.blue = 0.1;

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

    scene->ambient_light[0] = 0.15f;
    scene->ambient_light[1] = 0.15f;
    scene->ambient_light[2] = 0.15f;
    scene->ambient_light[3] = 1.0f;
    scene->index_list_origin = glGenLists(1);
    glNewList(scene->index_list_origin, GL_COMPILE);
    //draw_origin();
    draw_terrain(scene);
    glEndList();

    scene->index_list_buildings=glGenLists(1);
    glNewList(scene->index_list_buildings, GL_COMPILE);
    int i;
    glDisable(GL_COLOR_MATERIAL);
    for(i=0; i<4; i++){
            glBindTexture(GL_TEXTURE_2D, scene->building_texture_ids[i]);
            glEnable(GL_TEXTURE_2D);
            draw_model(&(scene->buildings[i]));
        }
        glBindTexture(GL_TEXTURE_2D, scene->road_texture_id);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_COLOR_MATERIAL);
        //glTranslatef(0,0,0.1f);
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
    if (scene->ambient_light[0] <= 0.3f)
    {
        scene->ambient_light[0] += 0.05f;
        scene->ambient_light[1] += 0.05f;
        scene->ambient_light[2] += 0.05f;
    }
    if(scene->ambient_light[0]>=0.2f){
        scene->diffuse_light[0] = 0.9f;
        scene->diffuse_light[1] = 0.5823f;
        scene->diffuse_light[2] = 0.6f;
    } else if(scene->ambient_light[0]>0.1f){
        scene->diffuse_light[0] = 0.6f;
        scene->diffuse_light[1] = 0.3882f;
        scene->diffuse_light[2] = 0.4f;
    } else if(scene->ambient_light[0]>=0.05){
        scene->diffuse_light[0] = 0.3f;
        scene->diffuse_light[1] = 0.19f;
        scene->diffuse_light[2] = 0.2f;
    }
    if(scene->ambient_light[0]>=0.15f){
        scene->skybox_texture_id[3]= scene->skybox_texture_id[0];
    }else if(scene->ambient_light[0]>=0.1f){
        scene->skybox_texture_id[3]= scene->skybox_texture_id[1];
    }
}
void decrease_light(Scene *scene){
    if (scene->ambient_light[0] >= 0.05f)
    {
        scene->ambient_light[0] -= 0.05f;
        scene->ambient_light[1] -= 0.05f;
        scene->ambient_light[2] -= 0.05f;
    }
    if(scene->ambient_light[0]<0.1f){
        scene->skybox_texture_id[3]= scene->skybox_texture_id[2];
    }else if(scene->ambient_light[0]<0.15f){
        scene->skybox_texture_id[3]= scene->skybox_texture_id[1];
    }
    if(scene->ambient_light[0]<0.05f) {
        scene->diffuse_light[0] = 0.0f;
        scene->diffuse_light[1] = 0.0f;
        scene->diffuse_light[2] = 0.0f;
    }else if(scene->ambient_light[0]<=0.1f){
        scene->diffuse_light[0] = 0.3f;
        scene->diffuse_light[1] = 0.19f;
        scene->diffuse_light[2] = 0.2f;
    }else if(scene->ambient_light[0]<0.2f){
        scene->diffuse_light[0] = 0.6f;
        scene->diffuse_light[1] = 0.3882f;
        scene->diffuse_light[2] = 0.4f;
    }
}
void set_lighting(const Scene *scene)
{
    float specular_light[] = {0.3f, 0.3f, 0.3f, 1.0f};
    float position[] = {0.0f, 0.0f, 10.0f, 1.0f};

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

void reset_scene(Scene *scene){
    reset_pallet(&(scene->pallet));
    reset_forklift(&(scene->forklift));
    reset_timer(&(scene->timer));
}
void show_manual(Scene *scene)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_COLOR_MATERIAL);
    glBindTexture(GL_TEXTURE_2D,  scene->instructions_texture_id);
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-2.4, 1.6f, -3);
    glTexCoord2f(1, 0);
    glVertex3f(2.4, 1.6f, -3);
    glTexCoord2f(1, 1);
    glVertex3f(2.4, -1.6f, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-2.4, -1.6f, -3);
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
    if(!is_inside(scene->arena, scene->forklift.box) || !is_inside(scene->arena, scene->forklift.fork_box)  || is_colliding(scene->container_box,  scene->forklift.box) || (is_colliding(scene->container_box,  scene->forklift.fork_box) && scene->forklift.fork_lift_height<1.5)){
        stop_colliding_forklift(&(scene->forklift), time);
    }else if(is_colliding(scene->container_box,  scene->forklift.fork_box)){
        scene->forklift.is_fork_free_to_lower=false;
    }
    scene->skybox_angle+=scene->skybox_speed;
    if(scene->skybox_angle>=360) scene->skybox_angle=0;
    distance = pow(pow(scene->pallet.position[0]-scene->forklift.x, 2)+pow(scene->pallet.position[1]-scene->forklift.y, 2), 0.5);
    if((distance<3 && !scene->pallet.is_lifted) || (is_colliding(scene->container_box, scene->pallet.box) && scene->pallet.is_lifted))scene->pallet.is_green=true;
    else scene->pallet.is_green=false;
    if(!is_inside(scene->arena, scene->pallet.box) || is_colliding(scene->container_box, scene->pallet.box)) scene->pallet.is_lifted = true;
    update_timer(&(scene->timer), time);

}
void render_scene(Scene *scene)
{
    //draw_bounding_box(&(scene->forklift.box));
    //draw_bounding_box(&(scene->pallet.box));
    //draw_bounding_box(&(scene->container_box));
    set_material(&(scene->material));
    set_lighting(scene);
    glCallList(scene->index_list_origin);
    glDisable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, scene->container_texture_id);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
        glTranslatef(-19.8f, 0, -0.451667f);
        glRotatef(180, 0, 0,1);
        draw_model(&(scene->container));
    glPopMatrix();
    glPushMatrix();
        glTranslatef(10.0f, -10.0f, -0.5f);
       glCallList(scene->index_list_buildings);
    glPopMatrix();
    glPushMatrix();
        glRotatef(180, 0, 0, 1);
        glTranslatef(26.0f, -15.7f, -0.5f);
        glCallList(scene->index_list_buildings);
    glPopMatrix();
    glEnable(GL_CULL_FACE);
    glPushMatrix();
        glDisable(GL_COLOR_MATERIAL);
        glBindTexture(GL_TEXTURE_2D, scene->skybox_texture_id[3]);
        glEnable(GL_TEXTURE_2D);
        glTranslatef(scene->skybox_position.x, scene->skybox_position.y, scene->skybox_position.z+10);
        glRotatef(scene->skybox_angle, 0.0f, 0.0f, 1.0f);
        glScalef(20,20,20);
        draw_model(&(scene->skybox));
        glEnable(GL_COLOR_MATERIAL);
    glPopMatrix();
    glEnable(GL_LIGHTING);
    render_forklift(&(scene->forklift));
    render_pallet(&(scene->pallet));
    render_timer(&(scene->timer));
    render_timer(&(scene->high_score));
    if(scene->is_manual_visible) show_manual(scene);
}

void draw_terrain(Scene *scene){
    // a placcot darabokban rajzoljuk ki, hogy latvanyosan verje vissza a fenyt
    int i, j;
    float x_coord=-20.9675f, y_coord=-8.405f;
    float step_x=25.935/50, step_y=22.55/50;
    glEnable(GL_COLOR_MATERIAL);
    glBindTexture(GL_TEXTURE_2D, scene->ground_texture_id);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glNormal3f(0,0,1);
    for(i=0; i<50; i++){
        for(j=0;j<50; j++){
            glTexCoord2f(0,12);
            glVertex3f(x_coord+step_x, y_coord, -0.451667);
            glTexCoord2f(12,12);
            glVertex3f(x_coord+step_x, y_coord+step_y, -0.451667);
            glTexCoord2f(12,0);
            glVertex3f(x_coord, y_coord+step_y, -0.451667);
            glTexCoord2f(0,0);
            glVertex3f(x_coord, y_coord, -0.451667);
            y_coord+=step_y;
        }
        x_coord+=step_x;
        y_coord=-8.405f;
    }
    glEnd();
    //a tavoli fuves resz kirajzolasa
    glBindTexture(GL_TEXTURE_2D, scene->grass_texture_id);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2f(100,0);
    glVertex3f(1000, -1000, -0.5);
    glTexCoord2f(100,100);
    glVertex3f(1000, 1000, -0.5);
    glTexCoord2f(0,100);
    glVertex3f(-1000, 1000, -0.5);
    glTexCoord2f(0,0);
    glVertex3f(-1000, -1000, -0.5);
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
