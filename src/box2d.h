#ifndef _BOX2D_H
#define _BOX2D_H

#include "headers.h"
#include "coord.h"
#include "colour.h"

class Box2d
{
  private:
    Coord origin;
    Colour colour;
    GLfloat width;
    GLfloat height;
    GLuint texName;
    char text[20];
    bool showText;
    bool showTexture;

  public:
    Box2d(Coord origin, GLfloat width, GLfloat height, Colour colour);
    Box2d(Coord origin, GLfloat width, GLfloat height, Colour colour, char* text);
    Box2d(Coord origin, GLfloat width, GLfloat height, Colour colour, GLuint texName);
    ~Box2d();

    Coord GetOrigin();
    void SetColour(Colour colour);
    bool IsPointInBox(int i, int j);    
    void Draw();
    void DrawText();
};

#endif
