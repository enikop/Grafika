#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "timer.h"
#include "texture.h"

void init_timer(Timer *timer, float scale, float pos[2]){
    timer->texture=load_texture("assets/textures/numbers.jpg");
    timer->value=0;
    timer->precise_value=0.0;
    set_digits(timer);
    timer->is_stopped = false;
    timer->scale = scale;
    timer->position[0]=pos[0];
    timer->position[1]=pos[1];

}
void read_high_score(Timer *timer){
    FILE *fp = fopen("hs.txt", "rt");
    if(fp==NULL){
        timer->value=9999;
        set_digits(timer);
    } else {
        fscanf(fp, "%d", &(timer->value));
        timer->value = timer->value ^ 22222;
        fclose(fp);
        if(timer->value > 9999 || timer->value < 0){
            timer->value=9999.0f;
        }
        set_digits(timer);
    }
} 
void write_high_score(Timer *timer){
    FILE *fp = fopen("hs.txt", "wt");
    if(fp==NULL){
        return;
    } else {
        fprintf(fp, "%d\n", timer->value ^ 22222);
        fclose(fp);
    }
} 
void check_high_score(Timer *timer, int score){
    if(score<timer->value){
        timer->value = score;
        set_digits(timer);
        write_high_score(timer);
    }
}

void reset_timer(Timer *timer){
    timer->value=0;
    timer->precise_value=0.0;
    set_digits(timer);
    timer->is_stopped = false;
}

void update_timer(Timer *timer, double time){
    if(time<0 || time>1000 || timer->is_stopped) return;
    timer->precise_value+=time;
    timer->value = floor(timer->precise_value);
    if(timer->value>9999){
        timer->value=9999;
        timer->precise_value=9999;
    }
    set_digits(timer);
}
void set_digits(Timer *timer){
    int temp;
    timer->digits[0]=timer->value%10;
    temp = timer->value/10;
    timer->digits[1]=temp%10;
    temp /= 10;
    timer->digits[2]=temp%10;
    temp /= 10;
    timer->digits[3]=temp%10;
}
void stop_timer(Timer *timer){
    timer->is_stopped = true;
}
void start_timer(Timer *timer){
    timer->is_stopped = false;
}
void render_timer(Timer *timer){
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_COLOR_MATERIAL);
    glBindTexture(GL_TEXTURE_2D,  timer->texture);
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBegin(GL_QUADS);
    glTexCoord2f(0.1*timer->digits[0], 1);
    glVertex3f(-0.12f*timer->scale+timer->position[0], -0.16f*timer->scale+timer->position[1], -3);
    glTexCoord2f(0.1*(timer->digits[0]+1), 1);
    glVertex3f(0.12f*timer->scale+timer->position[0], -0.16f*timer->scale+timer->position[1], -3);
    glTexCoord2f(0.1*(timer->digits[0]+1), 0);
    glVertex3f(0.12f*timer->scale+timer->position[0], 0.16f*timer->scale+timer->position[1], -3);
    glTexCoord2f(0.1*timer->digits[0], 0);
    glVertex3f(-0.12f*timer->scale+timer->position[0], 0.16f*timer->scale+timer->position[1], -3);
    glEnd();
    glBegin(GL_QUADS);
    glTexCoord2f(0.1*(timer->digits[1]), 1);
    glVertex3f((-0.12f-0.24f)*timer->scale+timer->position[0], -0.16f*timer->scale+timer->position[1], -3);
    glTexCoord2f(0.1*(timer->digits[1]+1), 1);
    glVertex3f((0.12f-0.24f)*timer->scale+timer->position[0], -0.16f*timer->scale+timer->position[1], -3);
    glTexCoord2f(0.1*(timer->digits[1]+1), 0);
    glVertex3f((0.12f-0.24f)*timer->scale+timer->position[0], 0.16f*timer->scale+timer->position[1], -3);
    glTexCoord2f(0.1*(timer->digits[1]), 0);
    glVertex3f((-0.12f-0.24f)*timer->scale+timer->position[0], 0.16f*timer->scale+timer->position[1], -3);
    glEnd();
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glTexCoord2f(0.1*(timer->digits[2]), 1);
    glVertex3f((-0.12f-0.48f)*timer->scale+timer->position[0], -0.16f*timer->scale+timer->position[1], -3);
    glTexCoord2f(0.1*(timer->digits[2]+1), 1);
    glVertex3f((0.12f-0.48f)*timer->scale+timer->position[0], -0.16f*timer->scale+timer->position[1], -3);
    glTexCoord2f(0.1*(timer->digits[2]+1), 0);
    glVertex3f((0.12f-0.48f)*timer->scale+timer->position[0], 0.16f*timer->scale+timer->position[1], -3);
    glTexCoord2f(0.1*(timer->digits[2]), 0);
    glVertex3f((-0.12f-0.48f)*timer->scale+timer->position[0], 0.16f*timer->scale+timer->position[1], -3);
    glEnd();
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glTexCoord2f(0.1*(timer->digits[3]), 1);
    glVertex3f((-0.12f-0.72f)*timer->scale+timer->position[0], -0.16f*timer->scale+timer->position[1], -3);
    glTexCoord2f(0.1*(timer->digits[3]+1), 1);
    glVertex3f((0.12f-0.72f)*timer->scale+timer->position[0], -0.16f*timer->scale+timer->position[1], -3);
    glTexCoord2f(0.1*(timer->digits[3]+1), 0);
    glVertex3f((0.12f-0.72f)*timer->scale+timer->position[0], 0.16f*timer->scale+timer->position[1], -3);
    glTexCoord2f(0.1*(timer->digits[3]), 0);
    glVertex3f((-0.12f-0.72f)*timer->scale+timer->position[0], 0.16f*timer->scale+timer->position[1], -3);
    glEnd();

    glEnable(GL_CULL_FACE);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}