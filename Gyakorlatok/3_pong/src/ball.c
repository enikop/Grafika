#include "ball.h"

#include <GL/gl.h>

#include <math.h>

void init_ball(Ball* ball, float x, float y)
{
    ball->x = x;
    ball->y = y;
    ball->angle = 0;
    ball->radius = 50;
    ball->speed_x = 200;
    ball->speed_y = 200;
    ball->speed_rot = 1;
}

void update_ball(Ball* ball, double time)
{
    ball->x += ball->speed_x * time;
    ball->y += ball->speed_y * time;
    ball->angle += ball -> speed_rot * time;
    if(ball->angle > 2*atan(1)*4){
        ball->angle = 0;
    }
    if(ball->angle <0){
        ball->angle = 2*atan(1)*4;
    }
}

void render_ball(Ball* ball)
{
    double angle = 0;
    double x;
    double y;
    int i=0;

    glPushMatrix();
    glTranslatef(ball->x, ball->y, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0, 255, 255);
    glVertex2f(0, 0);
    
    while (angle < 2.0 * (atan(1)*4) + 1) {
        x = cos(angle + ball->angle) * ball->radius;
        y = sin(angle + ball->angle) * ball->radius;
        glColor3ub(0, i, i); 
        i+=255*0.2/(2.0 * (atan(1)*4) + 1);
        glVertex2f(x, y);
        angle += 0.2;
    }
    glEnd();
    glPopMatrix();
}
