#define _USE_MATH_DEFINES
#include "camera.h"
#include "forklift.h"
#include "forklift.h"
#include <GL/gl.h>

#include <math.h>
#include <stdlib.h>

void init_camera(Camera* camera)
{
    camera->position.x = 0.0;
    camera->position.y = 0.0;
    camera->position.z = 1.0;
    camera->rotation.x = 0.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 0.0;
    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;
    camera->is_on_forklift = false;
}

void update_camera(Camera* camera, Forklift* forklift, double time)
{
    double angle;
    double side_angle;

    angle = degree_to_radian(camera->rotation.z);
    side_angle = degree_to_radian(camera->rotation.z + 90.0);
    if(camera->is_on_forklift){
        //ilyen bumpy kanyart csinal az x szinuszos resze ha nem 1.4
        camera->position.x = forklift->x - 1.3*sin(forklift->body_turn_angle);
        camera->position.y = forklift->y -1.4*cos(forklift->body_turn_angle);
        camera->position.z = forklift->z+2.25;
        camera->rotation.z = 90-forklift->body_turn_angle/M_PI*180;
    } else {
        camera->position.x += cos(angle) * camera->speed.y * time;
        camera->position.y += sin(angle) * camera->speed.y * time;
        camera->position.x += cos(side_angle) * camera->speed.x * time;
        camera->position.y += sin(side_angle) * camera->speed.x * time;
        camera->position.z += camera->speed.z * time;
    }
}
void change_camera_mode(Camera* camera){
 if(camera->is_on_forklift){
    camera->is_on_forklift = false;
    reset_camera(camera);
 } else camera->is_on_forklift = true;
}
void reset_camera(Camera* camera){
    camera->position.x = 0.0;
    camera->position.y = 0.0;
    camera->position.z = 3.0;
    camera->rotation.x = 0.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 0.0;
    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;
}

void set_view(const Camera* camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0);
    glRotatef(-(camera->rotation.z - 90), 0, 0, 1.0);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(Camera* camera, double horizontal, double vertical)
{
    camera->rotation.z += horizontal;
    camera->rotation.x += vertical;

    if (camera->rotation.z < 0) {
        camera->rotation.z += 360.0;
    }

    if (camera->rotation.z > 360.0) {
        camera->rotation.z -= 360.0;
    }

    if (camera->rotation.x < 0) {
        camera->rotation.x += 360.0;
    }

    if (camera->rotation.x > 360.0) {
        camera->rotation.x -= 360.0;
    }
}

void set_camera_speed(Camera* camera, double speed)
{
    camera->speed.y = speed;
}

void set_camera_side_speed(Camera* camera, double speed)
{
    camera->speed.x = speed;
}
void set_camera_lift_speed(Camera* camera, double speed)
{
    camera->speed.z = speed;
}

