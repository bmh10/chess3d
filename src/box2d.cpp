#include "box2d.h"

Box2d::Box2d(GLfloat* origin, GLfloat width, GLfloat height, GLfloat* colour)
{
  memcpy(this->origin, origin, 3*sizeof(GLfloat));
  memcpy(this->colour, colour, 4*sizeof(GLfloat));
  this->width = width;
  this->height = height;
  this->texName = -1;
}

Box2d::Box2d(GLfloat* origin, GLfloat width, GLfloat height, GLfloat* colour, char* text)
{
  memcpy(this->origin, origin, 3*sizeof(GLfloat));
  memcpy(this->colour, colour, 4*sizeof(GLfloat));
  this->width = width;
  this->height = height;
  strcpy(this->text, text);
  showText = true;
  this->texName = -1;
}

Box2d::Box2d(GLfloat* origin, GLfloat width, GLfloat height, GLfloat* colour, GLuint texName)
{
  this->origin = origin;
  //memcpy(this->origin, origin, 3*sizeof(GLfloat));
  memcpy(this->colour, colour, 4*sizeof(GLfloat));
  this->width = width;
  this->height = height;
  this->texName = texName;
  //showTexture = true;
}

Box2d::~Box2d()
{
}

GLfloat* Box2d::GetOrigin()
{
  return origin;
}

void Box2d::SetColour(GLfloat* colour)
{
  memcpy(this->colour, colour, 4*sizeof(GLfloat));
}

bool Box2d::IsPointInBox(int i, int j)
{
  return (i > origin[0] && i < origin[0]+width
         && j > origin[1] && j < origin[1]+height);
}

void Box2d::Draw()
{
  COL_WHITE(1.0f)

  if (showTexture)
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
    if (showText)
    {
      glPushMatrix();
        glColor4fv(white);
        glTranslatef(origin[0], origin[1], origin[2]);
        glScalef(0.25f, 0.25f, 0.5f);
        DrawText();
      glPopMatrix();
    }

    glBegin(GL_QUADS);
      glColor4fv(colour);
      glVertex3f(origin[0],       origin[1],        origin[2]);
      glVertex3f(origin[0]+width, origin[1],        origin[2]);
      glVertex3f(origin[0]+width, origin[1]+height, origin[2]);
      glVertex3f(origin[0]      , origin[1]+height, origin[2]);
    glEnd();
  }
}

void Box2d::DrawText()
{
  for (int i=0; i < (int)strlen(text); i++)
  {
    glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
  }
}
