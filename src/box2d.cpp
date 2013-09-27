#include "box2d.h"

Box2d::Box2d(GLfloat* origin, GLfloat width, GLfloat height, GLfloat* colour)
{
  memcpy(this->origin, origin, 3*sizeof(GLfloat));
  memcpy(this->colour, colour, 4*sizeof(GLfloat));
  this->width = width;
  this->height = height;
  this->texName = NULL;
}

Box2d::Box2d(GLfloat* origin, GLfloat width, GLfloat height, GLfloat* colour, GLuint texName)
{
  memcpy(this->origin, origin, 3*sizeof(GLfloat));
  memcpy(this->colour, colour, 4*sizeof(GLfloat));
  this->width = width;
  this->height = height;
  this->texName = texName;
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
  if (texName)
  {
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texName);
    glBegin(GL_QUADS);
      glColor4fv(colour);
      glTexCoord2f(0.0, 1.0); glVertex3f(origin[0],       origin[1],        origin[2]);
      glTexCoord2f(0.0, 0.0); glVertex3f(origin[0]      , origin[1]+height, origin[2]);
      glTexCoord2f(1.0, 0.0); glVertex3f(origin[0]+width, origin[1]+height, origin[2]);
      glTexCoord2f(1.0, 1.0); glVertex3f(origin[0]+width, origin[1],        origin[2]);
    glEnd();
    glDisable(GL_TEXTURE_2D);
  }
  else
  {
    glBegin(GL_QUADS);
      glColor4fv(colour);
      glVertex3f(origin[0],       origin[1],        origin[2]);
      glVertex3f(origin[0]+width, origin[1],        origin[2]);
      glVertex3f(origin[0]+width, origin[1]+height, origin[2]);
      glVertex3f(origin[0]      , origin[1]+height, origin[2]);
    glEnd();
  }
}
