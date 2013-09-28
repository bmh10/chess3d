#include "colour.h"

Colour::Colour()
{
}

Colour::Colour(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = a;
}

Colour::~Colour()
{
}

bool Colour::Equals(Colour c)
{
	return r == c.r && g == c.g && b == c.b && a == c.a;
}

// Switches current colour to this.
void Colour::Set()
{
  glColor4f(r, g, b, a);
}
