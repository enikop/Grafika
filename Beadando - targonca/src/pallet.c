#define _USE_MATH_DEFINES
#include "pallet.h"
#include "texture.h"
#include "timer.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <obj/load.h>
#include <obj/draw.h>

void init_pallet(Pallet *pallet, GLuint road_texture_id){
    float dimensions[] = {1.2f, 0.795f, 0.144f};
    load_model(&(pallet->model), "assets/models/pallet.obj");
    pallet->texture_id= load_texture("assets/textures/pallet_planks.jpg");
    pallet->texture_id= load_texture("assets/textures/pallet_planks.jpg");
    pallet->angle=0;
    pallet->position[0]=0.0f;
    pallet->position[1]=0.0f;
    pallet->position[2]=-0.3f;
    pallet->lifted_position[0]=0.0f;
    pallet->lifted_position[1]=1.04656f;
    pallet->lifted_position[2]=-0.181025f;
    pallet->dimensions[0]=dimensions[0];
    pallet->dimensions[1]=dimensions[1];
    pallet->dimensions[2]=dimensions[2];
    pallet->is_lifted=false;
    pallet->is_green=true;
    pallet->is_visible=true;
    pallet->road_texture_id=road_texture_id;

    init_bounding_box(&(pallet->box), dimensions, pallet->position);
    //nem hiba, origoba kell inicializalni, utana tolom
    pallet->position[1]=2.0f;
}
void update_pallet(Pallet *pallet, float* pos, float angle){
    if(pallet->is_lifted){
        //position[0] 0, nem kell atfogot szamolni
        pallet->position[0]=pallet->lifted_position[1]*sin(angle)+pos[0];
        pallet->position[1]=pallet->lifted_position[1]*cos(angle)+pos[1];
        pallet->position[2]=pallet->lifted_position[2]+pos[2];
        pallet->angle = angle;
    }
    update_bounding_box(&(pallet->box), pallet->position, pallet->angle);
}
void up_down_pallet(Pallet *pallet, Bounding_box *arena,  bool is_fork_down, Timer *timer, Timer *hs){
    if(pallet->is_green && is_fork_down) pallet->is_lifted = true;
    else if(is_fork_down && pallet->is_lifted){
        pallet->position[0]+=sin(pallet->angle)*1.2;
        pallet->position[1]+=cos(pallet->angle)*1.2;
        if(is_inside(*arena, pallet->box)){
            pallet->is_lifted=false;
            pallet->position[2]=-0.3f;
        }
        else{
            pallet->position[0]-=sin(pallet->angle)*1.2;
            pallet->position[1]-=cos(pallet->angle)*1.2;
        }
    } else if(!is_fork_down && pallet->is_green){
        stop_timer(timer);
        check_high_score(hs, timer->value);
        pallet->is_visible = false;
    }
}
void render_pallet(Pallet *pallet){
    if(!pallet->is_visible) return;
    glBindTexture(GL_TEXTURE_2D, pallet->texture_id);
    glEnable(GL_TEXTURE_2D);
    if(pallet->is_green) glColor3f(0.5f, 1.0f, 0.5f);
    glPushMatrix();
        glTranslatef(pallet->position[0], pallet->position[1], pallet->position[2]);
        glRotatef(-pallet->angle/M_PI*180, 0, 0, 1);
        draw_model(&(pallet->model));
        glColor3f(1.0f, 1.0f, 1.0f);
        if(pallet->is_lifted && !pallet->is_green){
            glBindTexture(GL_TEXTURE_2D, pallet->road_texture_id);
            glEnable(GL_TEXTURE_2D);
            glDisable(GL_CULL_FACE);
            glPushMatrix();
                glTranslatef(0.0f, 1.2f, -pallet->position[2]-0.45f);
                glBegin(GL_QUADS);
                    glNormal3f(0,0,1);
                    glTexCoord2f(0,0);
                    glVertex3f(pallet->dimensions[0]/2,pallet->dimensions[1]/2, 0.0f);
                    glTexCoord2f(0,1);
                    glVertex3f(pallet->dimensions[0]/2,-pallet->dimensions[1]/2, 0.0f);
                    glTexCoord2f(1,1);
                    glVertex3f(-pallet->dimensions[0]/2,-pallet->dimensions[1]/2, 0.0f);
                    glTexCoord2f(1,0);
                    glVertex3f(-pallet->dimensions[0]/2,pallet->dimensions[1]/2, 0.0f);                    
                glEnd();
            glPopMatrix();
            glEnable(GL_CULL_FACE);
        }
    glPopMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
}

void reset_pallet(Pallet *pallet){
    pallet->angle=0;
    pallet->position[0]=0.0f;
    pallet->position[1]=2.0f;
    pallet->position[2]=-0.3f;
    pallet->is_lifted=false;
    pallet->is_green=true;
    pallet->is_visible=true;
    update_bounding_box(&(pallet->box), pallet->position, pallet->angle);
}