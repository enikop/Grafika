#include "line.h"
void set_line(Line *line, int x0, int y0, int x1, int y1)
{
    line->x1 = x1;
    line->y1 = y1;
    line->x0 = x0;
    line->y0 = y0;
}
void set_color(Color *color, int r, int g, int b)
{
    color->r = r;
    color->g = g;
    color->b = b;
}
