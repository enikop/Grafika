#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "circle.h"

void set_draw_color(Color *color, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, SDL_ALPHA_OPAQUE);
}


void init_window(SDL_Renderer *renderer, Color *color_back, Color *color_front, Circle *circle)
{

    set_draw_color(color_back, renderer);
    SDL_RenderClear(renderer);
    set_draw_color(color_front, renderer);
    draw_circle_angle(renderer, circle, 15);
    SDL_RenderPresent(renderer);
    /*set_circle(&circle, 200, 200, 50);
    draw_circle_steps(renderer, &circle, 25);
    set_circle(&circle, 100, 300, 50);
    draw_circle_length(renderer, &circle, 10);*/
}

void handle_events(SDL_Renderer *renderer, Color *color_back, Color *color_front, Circle *circle)
{
    SDL_Event event;
    SDL_Cursor *cursor_pointer = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    SDL_Cursor *cursor_hand = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    int x1, y1;
    bool dragging = false;
    bool hand = false;
    bool need_run = true;
    bool cross = false;
    while (need_run)
    {
        SDL_GetMouseState(&x1, &y1);
        if(circle->radius>abs(circle->x-x1) && circle->radius>abs(circle->y-y1) && !cross){
            SDL_RenderDrawLine(renderer, circle->x - 20, circle->y, circle->x + 20, circle->y);
            SDL_RenderDrawLine(renderer, circle->x, circle->y-20, circle->x, circle->y+20);
            SDL_RenderPresent(renderer);
            cross = true;
        } else if (circle->radius<abs(circle->x-x1) || circle->radius<abs(circle->y-y1)){
            init_window(renderer, color_back, color_front, circle);
            cross = false;
        }
        if(dragging){
            set_circle(circle, x1, y1, circle->radius);
            init_window(renderer, color_back, color_front, circle);
            //need_run = false;
        }
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_SCANCODE_Q:
                need_run = false;
                break;
            case SDL_QUIT:
                need_run = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&x1, &y1);
                if(circle->radius>abs(circle->x-x1) && circle->radius>abs(circle->y-y1)){
                    dragging = true;
                    SDL_SetCursor(cursor_hand);
                }
                break;
            case SDL_MOUSEBUTTONUP:
                dragging = false;
                SDL_SetCursor(cursor_pointer);
                break;
            }
        }
    }
}
int main(int argc, char *argv[])
{
    int error_code;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Color color_back;
    Color color_front;
    Circle circle;
    set_circle(&circle, 200, 200, 100);
    set_color(&color_back, 230, 230, 255);
    set_color(&color_front, 111, 61, 153);

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0)
    {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return error_code;
    }

    window = SDL_CreateWindow(
        "Circle Drawer",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1000, 600, 0);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    init_window(renderer, &color_back, &color_front, &circle);
    handle_events(renderer, &color_back, &color_front, &circle);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}