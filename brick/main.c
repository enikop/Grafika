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

int main(int argc, char* argv[])
{
    Brick brick;
    double volume;
	
    set_brick_data(&brick, 5, 10, 8);
	volume = calc_brick_volume(&brick);
	
	
	printf("Brick volume: %lf\n", volume);
	
	return 0;
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