#include "box2d.h"

Box2d::Box2d(GLfloat* origin, GLfloat width, GLfloat height, GLfloat* colour)
{
  memcpy(this->origin, origin, 3*sizeof(GLfloat));
  memcpy(this->colour, colour, 3*sizeof(GLfloat));
  this->width = width;
  this->height = height;
}

Box2d::~Box2d()
{
}

GLfloat* Box2d::GetOrigin()
{
  return origin;
}

bool Box2d::IsPointInBox(int i, int j)
{
  return (i > origin[0] && i < origin[0]+width
         && j > origin[1] && j < origin[1]+height);
}

void Box2d::Draw()
{
  glBegin(GL_QUADS);
    glColor3fv(colour);
    glVertex3f(origin[0],       origin[1],        origin[2]);
    glVertex3f(origin[0]+width, origin[1],        origin[2]);
    glVertex3f(origin[0]+width, origin[1]+height, origin[2]);
    glVertex3f(origin[0]      , origin[1]+height, origin[2]);
  glEnd();
}
