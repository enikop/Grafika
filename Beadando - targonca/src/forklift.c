
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <obj/load.h>
#include <obj/draw.h>
#include "forklift.h"
#include "wheels.h"
#include "light.h"
#include "boundingbox.h"
#include "scene.h"

void init_forklift(Forklift *forklift){
    //modellek betoltese
    load_model(&(forklift->model), "assets/models/forkliftpos.obj");
    load_model(&(forklift->fork_model), "assets/models/forkpos.obj");
    load_model(&(forklift->steer_model), "assets/models/steeringpos.obj");
    //texturak betoltese
    forklift->texture_id = load_texture("assets/textures/violet.jpg");
    forklift->fork_texture_id = load_texture("assets/textures/fork.jpg");
    //forklift inicializalas
    forklift->x = 0;
    forklift->y = 0;
    forklift->z = 0;
    forklift->speed = 0;
    forklift->speed_z = 0;
    forklift->acceleration = 0;
    forklift->body_turn_angle = 0;
    forklift->body_turn_speed = 0;
    forklift->r=0;
    forklift->steer_angle = 0;
    forklift->fork_speed=0;
    forklift->fork_lift_height = 0;
    forklift->is_light_on=false;

    
    float dimensions[] = {1.5f,3.28f, 3.2f};
    float center[] = {0.0f, -1.07f,1.16f};
    init_bounding_box(&(forklift->box), dimensions, center);
    float fork_dimensions[]={0.7758f, 1.1125f, 0.055f};
    float fork_center[]={0.0f, 1.12f, -0.2f};
    init_bounding_box(&(forklift->fork_box), fork_dimensions, fork_center);
    init_wheels(&(forklift->wheels));
    init_light(&(forklift->spotlight));
    forklift->material_steel.ambient.red = 0.19225;
    forklift->material_steel.ambient.green = 0.19225;
    forklift->material_steel.ambient.blue = 0.19225;

    forklift->material_steel.diffuse.red = 0.50754;
    forklift->material_steel.diffuse.green =0.50754;
    forklift->material_steel.diffuse.blue = 0.50754;

    forklift->material_steel.specular.red = 0.508273;
    forklift->material_steel.specular.green = 0.508273;
    forklift->material_steel.specular.blue = 0.508273;

    forklift->material_steel.shininess = 100;

    forklift->material_rubber.ambient.red = 0.02;
    forklift->material_rubber.ambient.green = 0.02;
    forklift->material_rubber.ambient.blue = 0.02;

    forklift->material_rubber.diffuse.red = 0.01;
    forklift->material_rubber.diffuse.green =0.01;
    forklift->material_rubber.diffuse.blue = 0.01;

    forklift->material_rubber.specular.red =0.4;
    forklift->material_rubber.specular.green = 0.4;
    forklift->material_rubber.specular.blue = 0.4;

    forklift->material_rubber.shininess = 5;
}
void update_forklift(Forklift *forklift, double time, Pallet *pallet){
    float speed_x, speed_y;
    //villa mozgatasa z=0 és z=2 kozottt
    if((forklift->fork_lift_height >= 2 && forklift->fork_speed>0) || (forklift->fork_lift_height <= 0 && forklift->fork_speed<0)){
         forklift->fork_speed = 0;
    }
    //sebesseg novelese 9 vegsebessegig a gyorsulas alapjan
    if(!(forklift->speed>=9 && forklift->acceleration>0) && !(forklift->speed<=-9 && forklift->acceleration<0)){
         forklift->speed+=forklift->acceleration*time;
    }
    //fekezesi gyorsulas 1 vagy -1, ekkor 0 sebessegnel meg kell allni, ne induljunk el visszafele
    if((forklift->acceleration==300 && forklift->speed>0) ||(forklift->acceleration==-300 && forklift->speed<0)){
            forklift->speed=0;
            forklift->acceleration=0;
    }
    //ha pont egyenesen akarnank menni, vegtelen lenne a tangens, legyen r egy kelloen nagy valos szam
    if(forklift->wheels.turn_angle==0){
        forklift->r=1000;
    }else if(!forklift->speed==0){
       //r=l/tan(delta)
        forklift->r=-2.13102/tan(forklift->wheels.turn_angle/180*M_PI);
    }
    //omega = v/r
    forklift->body_turn_speed = forklift->speed/forklift->r;
    //ha speed 0, azaz a targonca nem mozog, akkor ne is kanyarodjon
    if(forklift->speed!=0){
        forklift->body_turn_angle+=forklift->body_turn_speed*time;
    }
    //body turn angle -2pi és 2pi között maradjon a biztonsag kedveert
    if(forklift->body_turn_angle>M_PI*2){
        forklift->body_turn_angle = 0;
    }
    if(forklift->body_turn_angle<-M_PI*2){
        forklift->body_turn_angle = 0;
    }
    speed_x=forklift->speed*sin(forklift->body_turn_angle);
    speed_y=forklift->speed*cos(forklift->body_turn_angle);
    //forklift->x += speed_x*time;
    //forklift->y += speed_y*time;
    forklift->z += forklift->speed_z*time;
    forklift->fork_lift_height+=forklift->fork_speed*time;
    float pos[3]={0,0,forklift->z};
    //if(is_colliding(forklift->box, pallet->box)) printf("utkozes\n");
    //todo ha x iranybol utkozik, nem erzekeli
    if(pallet->is_lifted){
        forklift->x += speed_x*time;
        forklift->y += speed_y*time;
        pos[0]=forklift->x;
        pos[1]=forklift->y;
    } else {
        forklift->x += speed_x*time;
        forklift->y += speed_y*time;
        pos[0]=forklift->x;
        pos[1]=forklift->y;
        update_bounding_box(&(forklift->box), pos, forklift->body_turn_angle);
        if(is_colliding(forklift->box, pallet->box)){
            forklift->x -= speed_x*time;
            forklift->y -= speed_y*time;
            forklift->body_turn_angle-=forklift->body_turn_speed*time;
        }
    }
    update_bounding_box(&(forklift->box), pos, forklift->body_turn_angle);
    update_bounding_box(&(forklift->fork_box), pos, forklift->body_turn_angle);
    //hatso kerek forgasi sebessege = targonca sebesseg/kerek kerulet
    forklift->wheels.rot_speed=forklift->speed/2.8379*360;
    //kormany forgasszoge 12-szerese a kerekenek (360 fok mindket iranyba)
    forklift->steer_angle = forklift->wheels.turn_angle*12;

    update_wheels(&(forklift->wheels), time);
    float hypotenuse = pow(0.38*0.38+0.7*0.7, 0.5);
    float phi = atan(0.38/0.7);
    float pos1[]={forklift->x-hypotenuse*sin(forklift->body_turn_angle+2*phi), forklift->y-hypotenuse*cos(forklift->body_turn_angle+2*phi), forklift->z+2.4, 1.0f};
    float pos2[]={forklift->x-hypotenuse*sin(forklift->body_turn_angle-2*phi), forklift->y-hypotenuse*cos(forklift->body_turn_angle-2*phi), forklift->z+2.4, 1.0f};
    float dir[]={sin(forklift->body_turn_angle), cos(forklift->body_turn_angle), -0.6};
    update_light(&(forklift->spotlight), pos1, pos2, dir);
}
void set_forklift_acceleration(Forklift *forklift, double acc){
    forklift->acceleration = acc;
}
void stop_colliding_forklift(Forklift *forklift, double time){
    float speed_x=forklift->speed*sin(forklift->body_turn_angle);
    float speed_y=forklift->speed*cos(forklift->body_turn_angle);
    float pos[3]={forklift->x,forklift->y,forklift->z};
    forklift->x -= speed_x*time;
    forklift->y -= speed_y*time;
    forklift->body_turn_angle-=forklift->body_turn_speed*time;
    pos[1]=forklift->y;
    pos[0]=forklift->x;
    update_bounding_box(&(forklift->box), pos, forklift->body_turn_angle);
}
void set_fork_speed(Forklift *forklift, double speed){
    forklift->fork_speed = speed;
}
void switch_spotlight(Forklift *forklift){
    if(forklift->is_light_on) forklift->is_light_on=false;
    else forklift->is_light_on = true;
}
void render_forklift(Forklift *forklift){
    //draw_bounding_box(&(forklift->fork_box));
    set_light(&(forklift->spotlight), forklift->is_light_on);
    set_material(&(forklift->material_steel));
    glPushMatrix();
        glEnable(GL_CULL_FACE);
        glBindTexture(GL_TEXTURE_2D, forklift->texture_id);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_COLOR_MATERIAL);
        glTranslatef(forklift->x, forklift->y, forklift->z);
        glRotatef(-forklift->body_turn_angle*180/M_PI, 0, 0, 1);
        //targonca rajzol
        draw_model(&(forklift->model));
        glBindTexture(GL_TEXTURE_2D, forklift->fork_texture_id);
        glEnable(GL_TEXTURE_2D);
        set_material(&(forklift->material_rubber));
        render_wheels(&(forklift->wheels));
        //villa rajzol
        set_material(&(forklift->material_steel));
        glPushMatrix();
            glTranslatef(0,0,forklift->fork_lift_height);
            draw_model(&(forklift->fork_model));
        glPopMatrix();
        //kormany rajzol
        glPushMatrix();
            set_material(&(forklift->material_rubber));
            glTranslated(-0.01, -0.83125, 1.563192);
            glRotatef(forklift->steer_angle, 0, -0.5878, 0.809);
            draw_model(&(forklift->steer_model));
        glPopMatrix();
    glPopMatrix();
}