#include "light.h"
#include "utils.h"
#include <GL/gl.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void init_light(Light* light){
    light->position1[0]=0;
    light->position1[1]=1;
    light->position1[2]=0.3;
    light->position1[3]=1;
    light->position2[0]=0;
    light->position2[1]=0;
    light->position2[2]=0;
    light->position2[3]=1;
    light->direction[0]=0;
    light->direction[1]=1;
    light->direction[2]=0;
    light->ambient[0]=0.0f;
    light->ambient[1]=0.0f;
    light->ambient[2]=0.0f;
    light->ambient[3]=1.0f;
    light->diffuse[0]=0.8f;
    light->diffuse[1]=0.8f;
    light->diffuse[2]=0.8f;
    light->diffuse[3]=1.0f;
    light->specular[0]=1.0f;
    light->specular[1]=1.0f;
    light->specular[2]=1.0f;
    light->specular[3]=1.0f;
    light->cutoff = 40;
}
void update_light(Light* light, float pos1[4], float pos2[4], float dir[3]){
    light->position1[0] = pos1[0];
    light->position1[1] = pos1[1];
    light->position1[2] = pos1[2];
    light->position1[3] = pos1[3];
    light->position2[0] = pos2[0];
    light->position2[1] = pos2[1];
    light->position2[2] = pos2[2];
    light->position2[3] = pos2[3];
    light->direction[0] = dir[0];
    light->direction[1] = dir[1];
    light->direction[2] = dir[2];
}
void set_light(Light *light, bool is_on){
    if(!is_on){
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT2);
        return;
    }
    glLightfv(GL_LIGHT1, GL_AMBIENT, light->ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light->diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light->specular);
    glPushMatrix();
        glLightfv(GL_LIGHT1, GL_POSITION, light->position1);
        glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, light->cutoff);
        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light->direction);
        glLightf (GL_LIGHT1, GL_SPOT_EXPONENT, 20.0);
        glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
        glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.045);
        glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0075);
    glPopMatrix();
    glLightfv(GL_LIGHT2, GL_AMBIENT, light->ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light->diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light->specular);
    glPushMatrix();
        glLightfv(GL_LIGHT2, GL_POSITION, light->position2);
        glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, light->cutoff);
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light->direction);
        glLightf (GL_LIGHT2, GL_SPOT_EXPONENT, 20.0);
        glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0);
        glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.045);
        glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.0075);
    glPopMatrix();
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
}
