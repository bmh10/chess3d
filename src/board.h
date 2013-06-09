#ifndef _BOARD_H
#define _BOARD_H

#define SQUARE_SIZE 0.02

#include "headers.h"
#include "board.h"
#include "piece.h"

class Board
{
  private:
    Piece pieces[32];

  public:
    Board();
    ~Board();

    void Init();
    //void Update();
    void Draw();
};

#endif
