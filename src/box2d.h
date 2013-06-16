#ifndef _BOX2D_H
#define _BOX2D_H

#include "headers.h"

class Box2d
{
  private:
    GLfloat origin[3];
    GLfloat colour[3];
    GLfloat width;
    GLfloat height;

  public:
    Box2d(GLfloat* origin, GLfloat width, GLfloat height, GLfloat* colour);
    ~Box2d();

    GLfloat* GetOrigin();
    bool IsPointInBox(int i, int j);    
    void Draw();
};

#endif
