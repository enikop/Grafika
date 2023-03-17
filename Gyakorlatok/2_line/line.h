#ifndef LINE_H
#define LINE_H
typedef struct Color
{
    int r;
    int g;
    int b;
} Color;
typedef struct Line
{
    int x0;
    int y0;
    int x1;
    int y1;
} Line;
void set_line(Line *line, int x0, int y0, int x1, int y1);
void set_color(Color *color, int r, int g, int b);

#endif