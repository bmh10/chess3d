#ifndef _PIECE_H
#define _PIECE_H

#include "headers.h"
#include "model.h"

enum PieceType { EMPTY, PAWN, KNIGHT, BISHOP, CASTLE, QUEE, KING };

class Piece
{
  private:
    PieceType type;
    Model* model;

    void Init();

  public:
    Piece(PieceType type, Model* model);
    ~Piece();
    
    void Draw(int i, int j);
    

};

#endif
