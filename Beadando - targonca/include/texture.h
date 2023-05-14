#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/gl.h>

typedef GLubyte Pixel[3];

//textura betoltese fajlbol, azonosito visszaadasa
GLuint load_texture(char* filename);

#endif /* TEXTURE_H */
