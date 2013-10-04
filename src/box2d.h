#ifndef _BOX2D_H
#define _BOX2D_H

#include "headers.h"
#include "coord3d.h"
#include "colour.h"

class Box2d
{
  private:
    Coord3D origin;
    Colour colour;
    GLfloat width;
    GLfloat height;
    GLuint texName;
    char text[20];
    bool showText;
    bool showTexture;

  public:
    Box2d();
    Box2d(Coord3D origin, GLfloat width, GLfloat height, Colour colour);
    Box2d(Coord3D origin, GLfloat width, GLfloat height, Colour colour, char* text);
    Box2d(Coord3D origin, GLfloat width, GLfloat height, Colour colour, GLuint texName);
    ~Box2d();

    Coord3D GetOrigin();
    void SetColour(Colour colour);
    bool IsPointInBox(int i, int j);    
    void Draw();
    void DrawText();
    void SetTexture(GLuint texName);
    void UnsetTexture();
};

#endif
