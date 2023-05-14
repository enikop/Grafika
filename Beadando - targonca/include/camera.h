#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"
#include "forklift.h"

#include <stdbool.h>


typedef struct Camera
{
    vec3 position; //kamera helye
    vec3 rotation; //kamera elfordulasa
    vec3 speed; //kamera sebessege
    bool is_on_forklift; //rajta van-e a targoncan a kamera
} Camera;

//kamera inicializalasa a kezdohelyzetere
void init_camera(Camera* camera);

//kamera helyenek frissitese, ha rajta van a targoncan, akkor targonca parameterek alapjan
void update_camera(Camera* camera, Forklift* forklift,  double time);

//kamera feltevese a targoncara es levevese onnen
void change_camera_mode(Camera* camera);

//kamera visszaallitasa kezdohelyzetbe
void reset_camera(Camera* camera);

//a nezopont beallitasa, hogy a kamera megfelelo helyen legyen
void set_view(const Camera* camera);

//kamera forgatasa fel-le es oldalra
void rotate_camera(Camera* camera, double horizontal, double vertical);

//elore sebesseg beallitasa
void set_camera_speed(Camera* camera, double speed);

//oldaliranyu sebesseg beallitasa
void set_camera_side_speed(Camera* camera, double speed);

//felfele iranyulo sebesseg beallitasa
void set_camera_lift_speed(Camera* camera, double speed);

#endif /* CAMERA_H */
