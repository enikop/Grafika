#include <math.h>
#include "brick.h"

int has_square_sides(Brick* brick){
    int ret = 0;
    if(brick->a==brick->b ||brick->b==brick->c || brick->a==brick->c){
        ret = 1;
    }
    return ret;
}
int isValid(Brick* brick){
    if(brick->a!=brick->a ||brick->b!=brick->b|| brick->c!=brick->c){
        return 0;
    }
    return 1;
}
void set_brick_data(Brick* brick, double a, double b, double c)
{
    if(a>0){
        brick->a=a;
    }
    else{
        brick->a=NAN;
    }
    if(b>0){
        brick->b=b;
    }
    else{
        brick->b=NAN;
    }
    if(c>0){
        brick->c=c;
    }
    else{
        brick->c=NAN;
    }
}

double calc_brick_volume(const Brick* brick)
{
	double volume = brick->a*brick->b*brick->c;
	return volume;
}
double calc_brick_surface(const Brick* brick){
    double surface = 2*(brick->a*brick->b+brick->a*brick->c+brick->c*brick->b);
    return surface;
}