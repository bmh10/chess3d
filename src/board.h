#ifndef _BOARD_H
#define _BOARD_H

#include "headers.h"
#include "piece.h"
#include "modelManager.h"

class Board
{
  private:
    Piece* pieces[8][8];
    ModelManager* modelManager;

    void Init();

  public:
    Board();
    ~Board();

    //void Update();
    void Draw();
};

#endif
