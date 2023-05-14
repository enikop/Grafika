#ifndef APP_H
#define APP_H

#include "camera.h"
#include "scene.h"
#include "forklift.h"

#include <SDL2/SDL.h>

#include <stdbool.h>

#define VIEWPORT_RATIO (5.0 / 3.0)
#define VIEWPORT_ASPECT 50.0

typedef struct App
{
    SDL_Window* window;
    SDL_GLContext gl_context;
    bool is_running;
    double uptime;
    Camera camera;
    Scene scene;
} App;

//app inicializalasa
void init_app(App* app, int width, int height);

//OpenGL kontextus inicializalas
void init_opengl();

//ablak meretezese
void reshape(GLsizei width, GLsizei height);

//esemenykezeles
void handle_app_events(App* app);

//ertekfrissites
void update_app(App* app);

//applikacio komponensek renderelese
void render_app(App* app);

//kilepes
void destroy_app(App* app);

#endif /* APP_H */
