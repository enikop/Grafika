#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "line.h"

void set_rectangle(SDL_Rect *rectangle, int x, int y, int w, int h)
{
    rectangle->x = x;
    rectangle->y = y;
    rectangle->w = w;
    rectangle->h = h;
}

void set_draw_color(Color *color, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, SDL_ALPHA_OPAQUE);
}

void init_window(SDL_Renderer *renderer, SDL_Rect *rectangles, Color *color_back, Color *palette)
{
    SDL_Event event;
    int db = 0;
    int x0 = -1, y0 = -1, x1 = -1, y1 = -1;
    bool need_run;

    set_draw_color(color_back, renderer);
    SDL_RenderClear(renderer);
    set_draw_color(&palette[0], renderer);
    SDL_RenderFillRect(renderer, &rectangles[0]);
    set_draw_color(&palette[1], renderer);
    SDL_RenderFillRect(renderer, &rectangles[1]);
    set_draw_color(&palette[2], renderer);
    SDL_RenderFillRect(renderer, &rectangles[2]);
    set_draw_color(&palette[3], renderer);
    SDL_RenderFillRect(renderer, &rectangles[3]);
    SDL_RenderPresent(renderer);
}
void choose_palette(SDL_Renderer *renderer, Color *palette, int y)
{
    if (y < 150)
        set_draw_color(&palette[0], renderer);
    else if (y < 300)
        set_draw_color(&palette[1], renderer);
    else if (y < 450)
        set_draw_color(&palette[2], renderer);
    else
        set_draw_color(&palette[3], renderer);
}
void handle_events(SDL_Renderer *renderer, SDL_Rect rectangles[4], Color *color_back, Color *palette, const int MAX_LINE_COUNT)
{
    SDL_Event event;
    SDL_Cursor *cursor_pointer = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    SDL_Cursor *cursor_hand = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    int db = 0;
    Line line;
    bool need_run, hand;
    set_line(&line, -1, -1, -1, -1);
    need_run = true;
    hand = false;
    while (need_run)
    {
        if (db > MAX_LINE_COUNT)
        {
            init_window(renderer, rectangles, color_back, palette);
            handle_events(renderer, rectangles, color_back, palette, MAX_LINE_COUNT);
            SDL_SetCursor(cursor_pointer);
            need_run = false;
        }
        SDL_GetMouseState(&line.x1, &line.y1);
        if (line.x1 < 150 || hand)
        {
            SDL_SetCursor(cursor_hand);
        }
        else
        {
            SDL_SetCursor(cursor_pointer);
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
                if (line.x0 == -1)
                {
                    SDL_GetMouseState(&line.x0, &line.y0);
                    if (line.x0 < 150)
                    {
                        choose_palette(renderer, palette, line.y0);
                        line.x0 = -1;
                    }
                    else
                        hand = true;
                }
                else
                {
                    hand = false;
                    SDL_GetMouseState(&line.x1, &line.y1);
                    if (line.x1 < 150)
                    {
                        choose_palette(renderer, palette, line.y1);
                    }
                    else
                    {
                        SDL_RenderDrawLine(renderer, line.x0, line.y0, line.x1, line.y1);
                        SDL_RenderPresent(renderer);
                        db++;
                    }
                    line.x0 = -1;
                }
                break;
            }
        }
    }
}
int main(int argc, char *argv[])
{
    const int MAX_LINE_COUNT = 8;
    int error_code;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Rect rectangles[4];
    Color color_back;
    Color palette[4];
    set_color(&color_back, 230, 230, 255);
    set_color(&palette[0], 255, 223, 140);
    set_color(&palette[1], 204, 181, 143);
    set_color(&palette[2], 176, 143, 204);
    set_color(&palette[3], 111, 61, 153);
    set_rectangle(&rectangles[0], 0, 0, 150, 150);
    set_rectangle(&rectangles[1], 0, 150, 150, 150);
    set_rectangle(&rectangles[2], 0, 300, 150, 150);
    set_rectangle(&rectangles[3], 0, 450, 150, 150);

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0)
    {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return error_code;
    }

    window = SDL_CreateWindow(
        "Line Drawer",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1000, 600, 0);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    init_window(renderer, rectangles, &color_back, palette);
    handle_events(renderer, rectangles, &color_back, palette, MAX_LINE_COUNT);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}