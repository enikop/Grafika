#include "counter.h"

#include <GL/gl.h>

#include <math.h>
#include <stdio.h>

void init_counter(Counter *counter, float x, float y)
{
    counter->x = x;
    counter->y = y;
    counter->left = 0;
    counter->right = 0;
    counter->width = 400;
    counter->height = 20;
}

void update_counter(Counter *counter, int left, int right)
{
    counter->left = left;
    counter->right = right;
}

void render_counter(Counter *counter)
{
    float x1, x2, y1, y2;
    int i;
    float step = 10;
    if(counter->left + counter->right !=0){
        float unit = counter->width / ((counter->left + counter->right )* 2);
        if(unit<step){
            step=unit;
        }
    }
    
    y1 = counter->y;
    y2 = y1 + counter->height;
    x1 = counter->x;
    for (i = 0; i < counter->left; i++)
    {
        x2 = x1 + step;
        glBegin(GL_QUADS);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(x1, y1);
        glColor3f(0.8, 0.2, 0.0);
        glVertex2f(x2, y1);
        glColor3f(1.0, 0.4, 0.0);
        glVertex2f(x2, y2);
        glColor3f(0.9, 0.3, 0.0);
        glVertex2f(x1, y2);
        glEnd();
        x1 += 2 * step;
    }
    x2=counter->x+counter->width;
    for (i = 0; i < counter->right; i++)
    {
        x1 = x2 - step;
        glBegin(GL_QUADS);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(x1, y1);
        glColor3f(0.0, 0.8, 0.2);
        glVertex2f(x2, y1);
        glColor3f(0.0, 1.0, 0.4);
        glVertex2f(x2, y2);
        glColor3f(0.0, 0.9, 0.2);
        glVertex2f(x1, y2);
        glEnd();
        x2 -= 2 * step;
    }
}
