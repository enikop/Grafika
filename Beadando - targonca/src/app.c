#include "app.h"
#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL_image.h>

void init_app(App* app, int width, int height)
{
    int error_code;
    int inited_loaders;

    app->is_running = false;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0) {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return;
    }

    app->window = SDL_CreateWindow(
        "Forklift",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL);
    if (app->window == NULL) {
        printf("[ERROR] Unable to create the application window!\n");
        return;
    }

    inited_loaders = IMG_Init(IMG_INIT_PNG);
    if (inited_loaders == 0) {
        printf("[ERROR] IMG initialization error: %s\n", IMG_GetError());
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL) {
        printf("[ERROR] Unable to create the OpenGL context!\n");
        return;
    }

    init_opengl();
    reshape(width, height);

    init_camera(&(app->camera));
    init_scene(&(app->scene));
    app->is_running = true;
}

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.1, 0.1, 0.1, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(
        -.1, .1,
        -.06, .06,
        .1166, 700
    );
}

void handle_app_events(App* app)
{
    SDL_Event event;
    static bool is_mouse_down = false;
    static int mouse_x = 0;
    static int mouse_y = 0;
    int x;
    int y;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                app->is_running = false;
                break;
            case SDL_SCANCODE_W:
                set_camera_speed(&(app->camera), 3);
                break;
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), -3);
                break;
            case SDL_SCANCODE_A:
                set_camera_side_speed(&(app->camera), 3);
                break;
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), -3);
                break;
            case SDL_SCANCODE_E:
                set_camera_lift_speed(&(app->camera), 3);
                break;
            case SDL_SCANCODE_Q:
                set_camera_lift_speed(&(app->camera), -3);
                break;
            case SDL_SCANCODE_T:
                set_forklift_acceleration(&(app->scene.forklift), 1);
                break;
            case SDL_SCANCODE_G:
                set_forklift_acceleration(&(app->scene.forklift), -1);
                break;
            case SDL_SCANCODE_F:
                set_turn_speed(&(app->scene.forklift.wheels), 30);
                break;
            case SDL_SCANCODE_H:
                set_turn_speed(&(app->scene.forklift.wheels), -30);
                break;
            case SDL_SCANCODE_R:
                if(app->scene.forklift.fork_lift_height>=2){
                    set_fork_speed(&(app->scene.forklift), -3);
                } else if(app->scene.forklift.fork_lift_height<=0){
                    set_fork_speed(&(app->scene.forklift), 3);
                }
                break;
            case SDL_SCANCODE_V: 
                switch_spotlight(&(app->scene.forklift));
                break;
            case SDL_SCANCODE_1:
                decrease_light(&(app->scene));
                break;
             case SDL_SCANCODE_2:
                increase_light(&(app->scene));
                break;
            case SDL_SCANCODE_C:
                change_camera_mode(&(app->camera));
                break;
            case SDL_SCANCODE_I:
                if(app->scene.is_manual_visible)
                    app->scene.is_manual_visible = false;
                else app->scene.is_manual_visible = true;
                break;
            case SDL_SCANCODE_L:
               up_down_pallet(&(app->scene.pallet), app->scene.forklift.fork_lift_height < 0.001 ? true : false );
               break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), 0);
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), 0);
                break;
            case SDL_SCANCODE_E:
            case SDL_SCANCODE_Q:
                set_camera_lift_speed(&(app->camera), 0);
                break;
            case SDL_SCANCODE_T:
                set_forklift_acceleration(&(app->scene.forklift), -300);
                break;
            case SDL_SCANCODE_G:
                set_forklift_acceleration(&(app->scene.forklift), 300);
                break;
            case SDL_SCANCODE_F:
            case SDL_SCANCODE_H:
                set_turn_speed(&(app->scene.forklift.wheels), 0);
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            is_mouse_down = true;
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&x, &y);
            if (is_mouse_down) {
                rotate_camera(&(app->camera), mouse_x - x, mouse_y - y);
            }
            mouse_x = x;
            mouse_y = y;
            break;
        case SDL_MOUSEBUTTONUP:
            is_mouse_down = false;
            break;
        case SDL_QUIT:
            app->is_running = false;
            break;
        default:
            break;
        }
    }
}

void update_app(App* app)
{
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - app->uptime;
    app->uptime = current_time;

    update_scene(&(app->scene),  elapsed_time);
    update_camera(&(app->camera), &(app->scene.forklift), elapsed_time);
    update_skybox_position(&(app->scene), app->camera.position);
}

void render_app(App* app)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&(app->camera));
    render_scene(&(app->scene));
    glPopMatrix();

    SDL_GL_SwapWindow(app->window);
}


void destroy_app(App* app)
{
    if (app->gl_context != NULL) {
        SDL_GL_DeleteContext(app->gl_context);
    }

    if (app->window != NULL) {
        SDL_DestroyWindow(app->window);
    }

    SDL_Quit();
}
