#include "coord2d.h"

Coord2D::Coord2D()
{
}

Coord2D::Coord2D(int x, int y)
{
  this->x = x;
  this->y = y;
}

Coord2D::~Coord2D()
{
}

bool Coord2D::Equals(Coord2D c)
{
	return x == c.x && y == c.y;
}

bool Coord2D::OutOfRange()
{
	return (x < 0 || x > 7 || y < 0 || y > 7);
}
