#ifndef _HUD_H
#define _HUD_H

#include "headers.h"

class Hud
{
  private:
    char text[2][20];

    void DrawText(int n);

  public:
    Hud();
    ~Hud();

    void Init();
    void Draw(bool whiteToMove);
};

#endif
