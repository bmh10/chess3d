#ifndef _COORD_H
#define _COORD_H

#include "headers.h"

class Coord
{
  public:
  	Coord(int x, int y);
    ~Coord();

  	int x;
    int y;

    bool Equals(Coord c);
};

#endif