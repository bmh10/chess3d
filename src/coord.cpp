#include "coord.h"

Coord::Coord(int x, int y)
{
  this->x = x;
  this->y = y;
}

Coord::~Coord()
{
}

bool Coord::Equals(Coord c)
{
	return x == c.x && y == c.y;
}

bool Coord::OutOfRange()
{
	return (x < 0 || x > 7 || y < 0 || y > 7);
}
