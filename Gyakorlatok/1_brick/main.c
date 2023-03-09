#include <stdio.h>
#include "brick.h"
void examineBrick(Brick* brick);
int main(int argc, char *argv[])
{
    Brick brick;
    printf("Brick number 1:\n");
    set_brick_data(&brick, 5, -1, 8);
    examineBrick(&brick);
    printf("\nBrick number 2:\n");
    set_brick_data(&brick, 5, 5, 8);
    examineBrick(&brick);
    printf("\nBrick number 3:\n");
    set_brick_data(&brick, 5, 100, 8);
    examineBrick(&brick);

    return 0;
}
void examineBrick(Brick* brick){
    if (!isValid(brick)) {
        printf("One or more sides of the brick are given incorrectly.\n");
    } else {
        double volume = calc_brick_volume(brick);
        double surface = calc_brick_surface(brick);

        printf("Brick volume: %lf\n", volume);
        printf("Brick surface: %lf\n", surface);
        if (has_square_sides(brick))
        {
            printf("Has square sides.\n");
        }
        else
            printf("Has no square sides.\n");
    }
}