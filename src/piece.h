#ifndef _PIECE_H
#define _PIECE_H

#include "headers.h"

enum PieceType { PAWN, KNIGHT, BISHOP, CASTLE, QUEE, KING };

class Piece
{
  private:
    
    PieceType type;

    void Init();

  public:
    Piece(PieceType type);
    ~Piece();
    
    void Draw();
    

};

#endif
