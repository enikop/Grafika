#ifndef CIRCLE_H
#define CIRCLE_H

/**
 * Data of a circle object in Descartes coordinate system
 */
typedef struct Circle
{
	double x;
	double y;
	double radius;
} Circle;
typedef struct Color
{
    int r;
    int g;
    int b;
} Color;

/**
 * Set the data of the circle
 */
void set_circle(Circle* circle, double x, double y, double radius);
void set_color(Color *color, int r, int g, int b);
void draw_circle_angle(SDL_Renderer *renderer, Circle *circle, double step_angle);
void draw_circle_steps(SDL_Renderer *renderer, Circle *circle, int steps);
void draw_circle_length(SDL_Renderer *renderer, Circle *circle, double length);

#endif // CIRCLE_H
