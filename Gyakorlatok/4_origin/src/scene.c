#include "scene.h"

#include <GL/gl.h>
#include <stdlib.h>
#include <math.h>

void init_scene(Scene* scene)
{
    scene->sphere_angle=0;
    scene->sphere_rotspeed=0.1;
}

void update_scene(Scene* scene)
{
    scene->sphere_angle+=scene->sphere_rotspeed;
    if(scene->sphere_angle>360){
        scene->sphere_angle=0;
    }
}

void render_scene(const Scene* scene)
{
    draw_origin();
    //draw_triangle();
    draw_chess();
    draw_cylinder();
    draw_sphere(scene);
    draw_cone();
}

void draw_origin()
{
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

    glEnd();

}
void draw_triangle(){
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0, 0.5, 0.5);
    glVertex3f(0.5, 0.5, 0);
    glColor3f(0.5, 0.5, 0); 
    glVertex3f(0.5, 0, 0.5);
    glColor3f(0.5, 0, 0.5); 
    glVertex3f(0.5, 0.5, 0.5);
    glEnd();
}

void draw_chess(){
    double i, j;
    int feher=1;
    for(i=0; i<1; i+=0.1){
        for(j=0; j<1; j+=0.1){
            glBegin(GL_QUADS);
            if(feher) {
                glColor3f(0,0,0);
                feher=0;
            }else{
                glColor3f(1,1,1);
                feher=1;
            }
            glVertex3f(i,j,0);
            glVertex3f(i,j+0.1,0);
            glVertex3f(i+0.1,j+0.1,0);
            glVertex3f(i+0.1,j,0);
            glEnd();
        }
    }
}
void draw_sphere(Scene *scene){
    double r = 0.1;
    int fi = 0;
    double angle = scene->sphere_angle;
    double x= 0.2*cos(degree_to_radian(angle));
    double y = 0.2*sin(degree_to_radian(angle));
    int theta = 0;
    for(theta=-90; theta<=90; theta+=5){
        glBegin(GL_QUAD_STRIP);
        glColor3f(0,abs(theta%2),1);
        for(fi=0; fi<=360; fi+=5){
            glVertex3f(r*cos(degree_to_radian(fi))*cos(degree_to_radian(theta))+x, r*sin(degree_to_radian(fi))*cos(degree_to_radian(theta))+y,r*sin(degree_to_radian(theta))+0.5);
            glVertex3f(r*cos(degree_to_radian(fi))*cos(degree_to_radian(theta+5))+x, r*sin(degree_to_radian(fi))*cos(degree_to_radian(theta+5))+y,r*sin(degree_to_radian(theta+5))+0.5);
        }
        glEnd();
    }
}
void draw_cylinder(){
    int i=0;
    double height = 0.2;
    double r =0.1;
    double x = 0.7;
    double angle=0;
    glBegin(GL_QUAD_STRIP);
    glColor3f(1,0,0);
     for(i=0; i<=360; i+=10){
        glVertex3f(r*cos(degree_to_radian(i))+x,r*sin(degree_to_radian(i))+x,0.3);
        glVertex3f(r*cos(degree_to_radian(i))+x,r*sin(degree_to_radian(i))+x,0.3+height);
     }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1, 0, 1);
    glVertex3f(x, x, 0.3);
    
    while (angle < 2.0 * (atan(1)*4) + 1) {
        glVertex3f(r*cos(angle)+x, r*sin(angle)+x, 0.3);
        angle += 0.1;
    }
    angle=0;
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1, 0, 1);
    glVertex3f(x, x, 0.3+height);
    
    while (angle < 2.0 * (atan(1)*4) + 1) {
        glVertex3f(r*cos(angle)+x, r*sin(angle)+x, 0.3+height);
        angle += 0.1;
    }
    glEnd();
}
void draw_cone(){
    int i=0;
    double height = 0.3;
    double r =0.1;
    double x = 0.5;
    double angle=0;
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0.5, 0.5, 0); 
     for(i=0; i<=360; i+=10){
        glVertex3f(x,x,0.5+height);
        glVertex3f(r*cos(degree_to_radian(i+10))+x,r*sin(degree_to_radian(i+10))+x,0.6);
        glVertex3f(r*cos(degree_to_radian(i))+x,r*sin(degree_to_radian(i))+x,0.6);
     }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.5, 0.4, 0); 
    glVertex3f(x, x, 0.6);
    
    while (angle < 2.0 * (atan(1)*4) + 1) {
        glVertex3f(r*cos(angle)+x, r*sin(angle)+x, 0.6);
        angle += 0.1;
    }
    glEnd();
    
}
