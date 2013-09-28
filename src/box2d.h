#ifndef _BOX2D_H
#define _BOX2D_H

#include "headers.h"

class Box2d
{
  private:
    GLfloat origin[3];
    GLfloat* colour[4];
    GLfloat width;
    GLfloat height;
    GLuint texName;
    char text[20];
    bool showText;
    bool showTexture;

  public:
    Box2d(GLfloat* origin, GLfloat width, GLfloat height, GLfloat* colour);
    Box2d(GLfloat* origin, GLfloat width, GLfloat height, GLfloat* colour, char* text);
    Box2d(GLfloat* origin, GLfloat width, GLfloat height, GLfloat* colour, GLuint texName);
    ~Box2d();

    GLfloat* GetOrigin();
    void SetColour(GLfloat* colour);
    bool IsPointInBox(int i, int j);    
    void Draw();
    void DrawText();
};

#endif
