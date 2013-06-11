#include "piece.h"

Piece::Piece(PieceType type, Model* model)
{
  this->type = type;
  this->model = model;
}

Piece::~Piece()
{
}

void Piece::Init()
{
}

void Piece::Draw(int i, int j)
{
  if (type != EMPTY)
  {
    model->DrawAt(i*SQUARE_SIZE + SQUARE_SIZE/2, j*SQUARE_SIZE + SQUARE_SIZE/2, SQUARE_SIZE/4, 0.005f);
  }
}
