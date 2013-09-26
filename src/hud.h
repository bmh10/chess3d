#ifndef _HUD_H
#define _HUD_H

#include "headers.h"
#include "box2d.h"
#include "board.h"
#include "piece.h"

class Hud
{
  private:
  	Board* board;
    char text[2][20];

    void DrawText(int n);

  public:
    Hud(Board* board);
    ~Hud();

    void Init();
    void Draw(bool whiteToMove);
};

#endif
