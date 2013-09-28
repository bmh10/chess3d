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

// Diff is that allow difference between the colours.
bool Colour::Equals(Colour c, GLfloat diff)
{
	bool equal = true;
	equal &= fabs(r*a - c.r*c.a) < diff;
	equal &= fabs(g*a - c.g*c.a) < diff;
	equal &= fabs(b*a - c.b*c.a) < diff;
	return equal;
}

// Switches current colour to this.
void Colour::Set()
{
  glColor4f(r, g, b, a);
}
