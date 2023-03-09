#ifndef BRICK_H
#define BRICK_H
typedef struct Brick
{
	double a;
	double b;
	double c;
} Brick;
void set_brick_data(Brick* brick, double a, double b, double c);
double calc_brick_volume(const Brick* brick);
double calc_brick_surface(const Brick* brick);
int has_square_sides(Brick* brick);
int isValid(Brick* brick);

#endif