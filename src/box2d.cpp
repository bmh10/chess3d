#include "box2d.h"

Box2d::Box2d()
{
  this->origin = Coord3D(0.0f, 0.0f, 0.0f);
  this->width = 0.0f;
  this->height = 0.0f;
  this->colour = Colour(0.0f, 0.0f, 0.0f, 0.0f);
  showText = false;
  showTexture = false;
}

Box2d::Box2d(Coord3D origin, GLfloat width, GLfloat height, Colour colour)
{
  this->origin = origin;
  this->width = width;
  this->height = height;
  this->colour = colour;

  showText = false;

  this->texName = -1;
  showTexture = false;
}

Box2d::Box2d(Coord3D origin, GLfloat width, GLfloat height, Colour colour, char* text)
{
  this->origin = origin;
  this->width = width;
  this->height = height;
  this->colour = colour;

  strcpy(this->text, text);
  showText = true;

  this->texName = -1;
  showTexture = false;
}

Box2d::Box2d(Coord3D origin, GLfloat width, GLfloat height, Colour colour, GLuint texName)
{
  this->origin = origin;
  this->width = width;
  this->height = height;
  this->colour = colour;

  showText = false;

  this->texName = texName;
  showTexture = true;
}

Box2d::~Box2d()
{
}

Coord3D Box2d::GetOrigin()
{
  return origin;
}

void Box2d::SetColour(Colour colour)
{
  this->colour = colour;
}

bool Box2d::IsPointInBox(int i, int j)
{
  return (i > origin.x && i < origin.x+width
         && j > origin.y && j < origin.y+height);
}

// Assumes already in ortho drawing mode.
void Box2d::Draw()
{
  Colour white = COL_WHITE(1.0f);

  if (showTexture)
  {
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texName);
    glBegin(GL_QUADS);
      colour.Set();
      glTexCoord2f(0.0, 1.0); glVertex3f(origin.x,       origin.y,        origin.z);
      glTexCoord2f(0.0, 0.0); glVertex3f(origin.x      , origin.y+height, origin.z);
      glTexCoord2f(1.0, 0.0); glVertex3f(origin.x+width, origin.y+height, origin.z);
      glTexCoord2f(1.0, 1.0); glVertex3f(origin.x+width, origin.y,        origin.z);
    glEnd();
    glDisable(GL_TEXTURE_2D);
  }
  else
  {
    if (showText)
    {
      glPushMatrix();
        white.Set();
        glTranslatef(origin.x, origin.y, origin.z);
        glScalef(0.25f, 0.25f, 0.5f);
        DrawText();
      glPopMatrix();
    }

    glBegin(GL_QUADS);
      colour.Set();
      glVertex3f(origin.x,       origin.y,        origin.z);
      glVertex3f(origin.x+width, origin.y,        origin.z);
      glVertex3f(origin.x+width, origin.y+height, origin.z);
      glVertex3f(origin.x      , origin.y+height, origin.z);
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
