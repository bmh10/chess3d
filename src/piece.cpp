#include "piece.h"

Piece::Piece(PieceType type)
{
  this->type = type;
}

Piece::Piece(PieceType type, PieceColour colour, ModelManager* modelManager)
{
  this->type = type;
  this->colour = colour;
  LoadModel(modelManager);
}

Piece::~Piece()
{
}

void Piece::Draw(int i, int j)
{
  assert(model != NULL);
  GLfloat white[] = {1.0, 1.0, 0.0}; // Make static?
  GLfloat black[] = {0.0, 1.0, 1.0};

  if (type != EMPTY)
  {
    GLfloat* col = (colour == WHITE) ? white : black;
    model->DrawAt(
      i*SQUARE_SIZE + SQUARE_SIZE/2, 
      j*SQUARE_SIZE + SQUARE_SIZE/2,
      SQUARE_SIZE/4,
      PIECE_SCALE,
      col);
  }
}

void Piece::LoadModel(ModelManager* modelManager)
{
  assert(modelManager != NULL);
  // TODO: make simpler by somehow mapping enum to string.
  switch(type)
  {
    case PAWN:
      model = modelManager->GetModel("pawn");
      break;
    case KNIGHT:
      model = modelManager->GetModel("knight");
      break;
    case BISHOP:
      model = modelManager->GetModel("bishop");
      break;
    case CASTLE:
      model = modelManager->GetModel("castle");
      break;
   case KING:
      model = modelManager->GetModel("king");
      break;
   case QUEEN:
      model = modelManager->GetModel("queen");
      break;  
  }
}
