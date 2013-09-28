#ifndef _COORD_2D_H
#define _COORD_2D_H

#include "headers.h"

class Coord2D
{
  public:
  	Coord2D();
  	Coord2D(int x, int y);
    ~Coord2D();

    int x;
    int y;

    bool Equals(Coord2D c);
    bool OutOfRange();
};

#endif
