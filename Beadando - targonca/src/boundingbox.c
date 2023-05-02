#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <obj/load.h>
#include <obj/draw.h>
#include <GL/gl.h>
#include "boundingbox.h"

void init_bounding_box(Bounding_box *box, float* dimensions, float* center){
    box->dimensions[0] = dimensions[0];
    box->dimensions[1] = dimensions[1];
    box->dimensions[2] = dimensions[2];
    box->center[0] = center[0];
    box->center[1] = center[1];
    box->center[2] = center[2];
    box->diagonal_angle = atan(dimensions[0]/dimensions[1]);
    box->diagonal = pow(dimensions[0]/2*dimensions[0]/2+dimensions[1]/2*dimensions[1]/2, 0.5);
    init_vector(&(box->fl));
    init_vector(&(box->fr));
    init_vector(&(box->bl));
    init_vector(&(box->br));
}
void update_bounding_box(Bounding_box *box, float* cur_position, float angle){ //jelenlegi pozicio es szog radianban
    float a1, b1, a2, b2, shift_x, shift_y;
    a1 = box->diagonal*sin(angle-box->diagonal_angle);
    b1 = box->diagonal*cos(angle-box->diagonal_angle);
    a2 = box->diagonal*cos(M_PI/2-angle-box->diagonal_angle);
    b2 = box->diagonal*sin(M_PI/2-angle-box->diagonal_angle);
    shift_x=box->center[1]*sin(angle);
    shift_y=box->center[1]*cos(angle);
    box->fl.x = a1+cur_position[0]+shift_x;
    box->fl.y = b1+cur_position[1]+shift_y;
    box->fl.z = box->center[2];
    box->br.x = -a1+cur_position[0]+shift_x;
    box->br.y = -b1+cur_position[1]+shift_y;
    box->br.z = box->center[2];
    box->fr.x = a2+cur_position[0]+shift_x;
    box->fr.y = b2+cur_position[1]+shift_y;
    box->fr.z = box->center[2];
    box->bl.x = -a2+cur_position[0]+shift_x;
    box->bl.y = -b2+cur_position[1]+shift_y;
    box->bl.z = box->center[2];
}
void draw_bounding_box(const Bounding_box *box){
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_CULL_FACE);
    glPushMatrix();
        glBegin(GL_QUADS);
            glColor3f(0,1,1);
            glVertex3f(box->fl.x, box->fl.y, box->fl.z);
            glVertex3f(box->fr.x, box->fr.y, box->fr.z);
            glVertex3f(box->br.x, box->br.y, box->br.z);
            glVertex3f(box->bl.x, box->bl.y, box->bl.z);
            glColor3f(1,1,1);
        glEnd();
    glPopMatrix();
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_COLOR_MATERIAL);
}
float max_coordinate(const Bounding_box box1, int index){
    float max;
    if(index==0){
        max = fmax(fmax(fmax(box1.bl.x, box1.br.x), box1.fr.x), box1.fl.x);
    } else if(index==1){
        max = fmax(fmax(fmax(box1.bl.y, box1.br.y), box1.fr.y), box1.fl.y);
    }
    else if(index==2){
        max = fmax(fmax(fmax(box1.bl.z, box1.br.z), box1.fr.z), box1.fl.z);
    }
    return max;
}
float min_coordinate(const Bounding_box box1, int index){
    float max;
    if(index==0){
        max = fmin(fmin(fmin(box1.bl.x, box1.br.x), box1.fr.x), box1.fl.x);
    } else if(index==1){
        max = fmin(fmin(fmin(box1.bl.y, box1.br.y), box1.fr.y), box1.fl.y);
    }else if(index==2){
        max = fmin(fmin(fmin(box1.bl.z, box1.br.z), box1.fr.z), box1.fl.z);
    }
    return max;
}

void construct_projections(vec3 line, Bounding_box box, Bounding_box *projected){
    project_point_to_line(box.bl, line, &(projected->bl));
    project_point_to_line(box.br, line, &(projected->br));
    project_point_to_line(box.fr, line, &(projected->fr));
    project_point_to_line(box.fl, line, &(projected->fl));
}


bool is_colliding(const Bounding_box box1, const Bounding_box box2){
    vec3 line1a, line1b, line2a, line2b;
    Bounding_box projected1a, projected1b, projected2a, projected2b;
    float maxx1, minx1, maxy1, miny1, maxx2, minx2, maxy2, miny2;
    bool cond1, cond2, cond3, cond4;
    construct_2d_line(box1.fl, box1.fr, &line1a);
    construct_2d_line(box1.fl, box1.bl, &line1b);
    construct_2d_line(box2.fl, box2.fr, &line2a);
    construct_2d_line(box2.fl, box2.bl, &line2b);
    construct_projections(line1a, box2, &projected2a);
    construct_projections(line1b, box2, &projected2b);
    construct_projections(line2a, box1, &projected1a);
    construct_projections(line2b, box1, &projected1b);

    maxx1= max_coordinate(projected1a, 0);
    maxx2= fmax(box2.fl.x, box2.fr.x);
    minx1= min_coordinate(projected1a, 0);
    minx2= fmin(box2.fl.x, box2.fr.x);
    maxy1= max_coordinate(projected1a, 1);
    maxy2= fmax(box2.fl.y, box2.fr.y);
    miny1= min_coordinate(projected1a, 1);
    miny2= fmin(box2.fl.y, box2.fr.y);
    cond1=(maxx1 >= minx2 && maxx2 >= minx1) && (maxy1 >= miny2 && maxy2 >= miny1);

    maxx1= max_coordinate(projected1b, 0);
    maxx2= fmax(box2.fl.x, box2.bl.x);
    minx1= min_coordinate(projected1b, 0);
    minx2= fmin(box2.fl.x, box2.bl.x);
    maxy1= max_coordinate(projected1b, 1);
    maxy2= fmax(box2.fl.y, box2.bl.y);
    miny1= min_coordinate(projected1b, 1);
    miny2= fmin(box2.fl.y, box2.bl.y);
    cond2=(maxx1 >= minx2 && maxx2 >= minx1) && (maxy1 >= miny2 && maxy2 >= miny1);

    maxx1= max_coordinate(projected2a, 0);
    maxx2= fmax(box1.fl.x, box1.fr.x);
    minx1= min_coordinate(projected2a, 0);
    minx2= fmin(box1.fl.x, box1.fr.x);
    maxy1= max_coordinate(projected2a, 1);
    maxy2= fmax(box1.fl.y, box1.fr.y);
    miny1= min_coordinate(projected2a, 1);
    miny2= fmin(box1.fl.y, box1.fr.y);
    cond3=(maxx1 >= minx2 && maxx2 >= minx1) && (maxy1 >= miny2 && maxy2 >= miny1);

    maxx1= max_coordinate(projected2b, 0);
    maxx2= fmax(box1.fl.x, box1.bl.x);
    minx1= min_coordinate(projected2b, 0);
    minx2= fmin(box1.fl.x, box1.bl.x);
    maxy1= max_coordinate(projected2b, 1);
    maxy2= fmax(box1.fl.y, box1.bl.y);
    miny1= min_coordinate(projected2b, 1);
    miny2= fmin(box1.fl.y, box1.bl.y);
    cond4=(maxx1 >= minx2 && maxx2 >= minx1) && (maxy1 >= miny2 && maxy2 >= miny1);
   
    return (cond1 && cond2 && cond3 && cond4);
}

bool is_inside(const Bounding_box box1, const Bounding_box box2){
    float box1_max_x=max_coordinate(box1, 0);
    float box1_min_x=min_coordinate(box1, 0);
    float box1_max_y=max_coordinate(box1, 1);
    float box1_min_y=min_coordinate(box1, 1);
    float box2_max_x=max_coordinate(box2, 0);
    float box2_min_x=min_coordinate(box2, 0);
    float box2_max_y=max_coordinate(box2, 1);
    float box2_min_y=min_coordinate(box2, 1);

    return ((box1_max_x >= box2_max_x && box2_min_x >= box1_min_x) && (box1_max_y >= box2_max_y && box2_min_y >= box1_min_y));
}
