#include <math.h>

#include <stdio.h>

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

int main(int argc, char* argv[])
{
    Brick brick;
    double volume, surface;
	
    set_brick_data(&brick, 5, 5, 8);
	volume = calc_brick_volume(&brick);
    surface = calc_brick_surface(&brick);
	
	
	printf("Brick volume: %lf\n", volume);
    printf("Brick surface: %lf\n", surface);
    if(has_square_sides(&brick)){
        printf("Has square sides.");
    } else printf("Has no square sides.");
	
	return 0;
}
int has_square_sides(Brick* brick){
    int ret = 0;
    if(brick->a==brick->b ||brick->b==brick->c || brick->a==brick->c){
        ret = 1;
    }
    return ret;
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
        brick->a=NAN;
    }
    if(c>0){
        brick->c=c;
    }
    else{
        brick->a=NAN;
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