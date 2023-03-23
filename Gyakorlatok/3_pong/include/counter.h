#ifndef COUNTER_H
#define COUNTER_H

typedef struct Counter
{
    int left;
    int right;
    float x;
    float y;
    float width;
    float height;
} Counter;

void init_counter(Counter *counter, float x, float y);

void update_counter(Counter *counter, int left, int right);
void render_counter(Counter *counter);



#endif 