#include "coord3d.h"

Coord3D::Coord3D()
{
}

Coord3D::Coord3D(GLfloat x, GLfloat y, GLfloat z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

Coord3D::~Coord3D()
{
}

bool Coord3D::Equals(Coord3D c)
{
	return x == c.x && y == c.y && z == c.z;
}
