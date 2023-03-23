#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "pong.h"

void init_pong(Pong* pong, int width, int height)
{
    pong->width = width;
    pong->height = height;
    init_pad(&(pong->left_pad), 0, height, RED_THEME);
    init_pad(&(pong->right_pad), width - 50, height, GREEN_THEME);
    init_ball(&(pong->ball), width / 2, height / 2);
    init_counter(&(pong->counter), width/2-200, 20);
}

void update_pong(Pong* pong, double time)
{
    update_pad(&(pong->left_pad), time);
    update_pad(&(pong->right_pad), time);
    update_ball(&(pong->ball), time);
    bounce_ball(pong);
}

void render_pong(Pong* pong)
{
    render_pad(&(pong->left_pad));
    render_pad(&(pong->right_pad));
    render_ball(&(pong->ball));
    render_counter(&(pong->counter));
}

void set_left_pad_position(Pong* pong, float position)
{
    set_pad_position(&(pong->left_pad), position);
}

void set_left_pad_speed(Pong* pong, float speed)
{
    set_pad_speed(&(pong->left_pad), speed);
}

void set_right_pad_position(Pong* pong, float position)
{
    set_pad_position(&(pong->right_pad), position);
}

void set_right_pad_speed(Pong* pong, float speed)
{
    set_pad_speed(&(pong->right_pad), speed);
}
int is_touching_pad(Pong *pong, int left){
    int padcenter = pong->right_pad.y + pong -> right_pad.height/2;
    int padheight = pong -> right_pad.height/2;
    if(left){
        padcenter = pong->left_pad.y + pong -> left_pad.height/2;
        padheight = pong -> left_pad.height/2;
    }
    if(abs(pong->ball.y-padcenter)<padheight/2+pong->ball.radius/2){
        return 1;
    }
    return 0;
}
void bounce_ball(Pong* pong)
{
    if (pong->ball.x - pong->ball.radius < 50 ) {
        if(is_touching_pad(pong, 1)){
            pong->ball.x = pong->ball.radius + 50;
            pong->ball.speed_x *= -1;
            pong->ball.speed_rot *= -1.25;
        } else{
            init_ball(&(pong->ball), pong->width / 2, pong->height / 2);
            pong -> counter.right+=1;
            };
    }
    if (pong->ball.x + pong->ball.radius > pong->width - 50) {
        if(is_touching_pad(pong, 0)){
            pong->ball.x = pong->width - pong->ball.radius - 50;
            pong->ball.speed_x *= -1;
            pong->ball.speed_rot *= -1.25;
        } else{
            init_ball(&(pong->ball), pong->width / 2, pong->height / 2);
            pong -> counter.left +=1;
        }
    }
    if (pong->ball.y - pong->ball.radius < 0) {
        pong->ball.y = pong->ball.radius;
        pong->ball.speed_y *= -1;
        pong->ball.speed_rot *= 0.8;
    }
    if (pong->ball.y + pong->ball.radius > pong->height) {
        pong->ball.y = pong->height - pong->ball.radius;
        pong->ball.speed_y *= -1;
        pong->ball.speed_rot *= 0.8;
    }
}
