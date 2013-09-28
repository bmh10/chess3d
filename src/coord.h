#ifndef _COORD_H
#define _COORD_H

#include "headers.h"

class Coord
{
  public:
  	Coord();
  	Coord(int x, int y);
  	Coord(int x, int y, int z);
    ~Coord();

  	int x;
    int y;
    int z;

    bool Equals(Coord c);
    bool OutOfRange();
};

#endif