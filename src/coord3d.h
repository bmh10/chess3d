#ifndef _COORD_3D_H
#define _COORD_3D_H

#include "headers.h"

class Coord3D
{
  public:
  	Coord3D();
  	Coord3D(GLfloat x, GLfloat y, GLfloat z);
    ~Coord3D();

  	GLfloat x;
    GLfloat y;
    GLfloat z;

    bool Equals(Coord3D c);
    GLfloat* ToPtr();
};

#endif