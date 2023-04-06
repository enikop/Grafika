#include "cube.h"
#include <stdio.h>
#include <obj/load.h>
#include <obj/draw.h>

void init_cube(Cube *cube){
    load_model(&(cube->cube_model), "assets/models/cube.obj");
    cube->texture_id = load_texture("assets/textures/cube.png");
    glBindTexture(GL_TEXTURE_2D, cube->texture_id);
    cube->x=0;
    cube->y=0;
    cube->z=0;
    cube->angle=0;
    cube->rotation_speed=1;
}
void update_cube(Cube *cube, double time){
    cube->angle+=cube->rotation_speed/10;
    //printf("%.3f - %.3f\n", cube->angle, time);
    if(cube->angle > 360) cube->angle=0;
}
void render_cube(const Cube *cube){
	glEnable(GL_TEXTURE_2D);
	glScalef(0.2,0.2,0.2);
    glRotatef(cube->angle, 0, 0, 1);
    glTranslatef(cube->x, cube->y, cube->z);
    draw_model(&(cube->cube_model));
    glTranslatef(-cube->x, -cube->y, -cube->z);
    glRotatef(-cube->angle, 0, 0, 1);
    glScalef(5,5,5);
	glDisable(GL_TEXTURE_2D);
}