#ifndef TIMER_H
#define TIMER_H
#include <obj/model.h>
#include <GL/gl.h>
#include <stdbool.h>

//Stopper es high score kijelzo
typedef struct Timer {
    int value; //kijelzett egesz idoertek
    double precise_value; //pontos idoertek
    GLuint texture; //szamok texturan
    int digits[4]; //4 megjelenitett szamjegy
    bool is_stopped; //meg van-e allitva
    float scale; //megjelenitett szamjegyek merete 0.24*0.32 hoz kepest
    float position[2]; //jobb felso sarok x es y koordinataja
} Timer;

//stopper incializalas
void init_timer(Timer *timer, float scale, float pos[2]);
//stopper megallitasa es elinditasa (stopper)
void stop_timer(Timer *timer);
void start_timer(Timer *timer);
//stopper frissitese eltelt idovel (stopper)
void update_timer(Timer *timer, double time);
//stopper renderelese 
void render_timer(Timer *timer);
//hs.txt filebol value kiolvasasa, ha nincs ilyen value = 9999 (high score)
void read_high_score(Timer *timer);
//hs.txt fileba value kiirasa (high score)
void write_high_score(Timer *timer);
//adott pontertek osszehasonlitasa a high score value-val, ha kisebb nala, kiirasa a hs.txt fileba (high score)
void check_high_score(Timer *timer, int score);
//szamjegyek beallitasa value erteke alapjan
void set_digits(Timer *timer);
//stopper reset (stopper)
void reset_timer(Timer *timer);
#endif