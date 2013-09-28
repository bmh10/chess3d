#ifndef _COLOUR_H
#define _COLOUR_H

#include "headers.h"

class Colour
{
  public:
  	Colour();
  	Colour(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    ~Colour();

  	GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;

    bool Equals(Colour c, GLfloat diff);
    void Set();
};

#endif