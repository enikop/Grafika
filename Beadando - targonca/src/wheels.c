#include "wheels.h"
#include <stdio.h>
#include <obj/load.h>
#include <obj/draw.h>

void init_wheels(Set_of_wheels *wheels){
    load_model(&(wheels->front_wheels), "assets/models/frontpos.obj");
    wheels->texture_id = load_texture("assets/textures/fork.jpg");
    load_model(&(wheels->back_right), "assets/models/backpos.obj");
    wheels->rot_angle = 0;
    wheels->rot_speed = 0;
    wheels->turn_speed = 0;
    wheels->turn_angle = 0;

    wheels->radius_ratio = 0.825;
}
void update_wheels(Set_of_wheels *wheels, double time){
    wheels->rot_angle += wheels -> rot_speed*time;
    if(wheels->rot_angle >= 360){
        wheels->rot_angle = 0;
    }
    if(wheels->rot_angle <= -360){
        wheels->rot_angle = 0;
    }
    if(wheels->turn_angle >= 30 && wheels->turn_speed>0){
        wheels->turn_speed = 0;
        wheels->turn_angle = 30;
    }else if(wheels->turn_angle <= -30 && wheels->turn_speed<0){
         wheels->turn_speed = 0;
         wheels->turn_angle = -30;
    } else  wheels->turn_angle += wheels -> turn_speed*time;
}
void set_turn_speed(Set_of_wheels *wheels, double speed){
    wheels->turn_speed=speed;
}
void render_wheels(const Set_of_wheels *wheels){
    glBindTexture(GL_TEXTURE_2D, wheels->texture_id);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glRotatef(-wheels->rot_angle*wheels->radius_ratio, 1 ,0, 0);
    draw_model(&(wheels->front_wheels));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.611, -2.148, -0.085);
    glRotatef(-wheels->turn_angle, 0,0,1);
    glRotatef(-wheels->rot_angle, 1 ,0, 0);
    draw_model(&(wheels->back_right));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.61052, -2.148, -0.085);
    glRotatef(-wheels->turn_angle, 0,0,1);
    glRotatef(-wheels->rot_angle, 1 ,0, 0);
    glRotatef(-180, 0, 1, 0);
    draw_model(&(wheels->back_right));
    glPopMatrix();
    
}