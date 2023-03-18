#include <SDL2/SDL.h>
#include <math.h>

#include "circle.h"

void set_color(Color *color, int r, int g, int b)
{
    color->r = r;
    color->g = g;
    color->b = b;
}

void set_circle(Circle* circle, double x, double y, double radius)
{
	circle->x = x;
	circle->y = y;
	if (radius > 0.0) {
		circle->radius = radius;
	} else {
		circle->radius = NAN;
	}
}

void draw_circle_angle(SDL_Renderer *renderer, Circle *circle, double step_angle){
    double angle_rad = step_angle / 180 * (atan(1)*4);
    double y0 = circle->radius;
    double x0 = 0;
    double current_angle = angle_rad;
    while(current_angle < 2*(atan(1)*4)){
        double x0t = x0;
        double y0t = y0;
        x0=circle->radius*sin(current_angle);
        y0=circle->radius*cos(current_angle);
        SDL_RenderDrawLine(renderer, x0t+circle->x, y0t+circle->y, x0+circle->x, y0+circle->y );
        current_angle+=angle_rad;
    }
    SDL_RenderDrawLine(renderer, x0+circle->x, y0+circle->y, circle->x, circle->radius+circle->y);
    SDL_RenderPresent(renderer);
}
void draw_circle_steps(SDL_Renderer *renderer, Circle *circle, int steps){
    double step_angle = 360.0/steps;
    draw_circle_angle(renderer, circle, step_angle);
}
void draw_circle_length(SDL_Renderer *renderer, Circle *circle, double length){
    double angle = asin(length/2/circle->radius)*2/(atan(1)*4)*180;
    draw_circle_angle(renderer, circle, angle);
}