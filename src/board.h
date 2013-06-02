#ifndef _BOARD_H

#define _BOARD_H

class Board
{
  private:
    Piece[32] pieces;

  public:
    Board();
    ~Board();

    void Init();
    //void Update();
    void Draw();
};

#endif
