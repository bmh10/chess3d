#include "piece.h"

Piece::Piece(PieceType type)
{
  this->type = type;
  selectionMode = false;
  state = NORMAL;
}

Piece::Piece(PieceType type, PieceColour colour, ModelManager* modelManager)
{
  this->type = type;
  this->colour = colour;
  LoadModel(modelManager);
  selectionMode = false;
  state = NORMAL;
}

Piece::~Piece()
{
}

PieceType Piece::GetType()
{
  return type;
}

PieceColour Piece::GetColour()
{
  return colour;
}

PieceState Piece::GetState()
{
  return state;
}

void Piece::SetSelected(bool selected)
{
  this->state = (selected) ? SELECTED : NORMAL;
}

void Piece::SetHighlighted(bool highlight)
{
  this->state = (highlight) ? HIGHLIGHTED : NORMAL;
}

void Piece::EnableSelectionMode(bool enable, int i, int j)
{
  selectionMode = enable;
  selectedColour[0] = (GLfloat)i/8.0;
  selectedColour[1] = (GLfloat)j/8.0;
  selectedColour[2] = 0.5;
  selectedColour[3] = 1.0;
  Draw(i, j);
}

bool Piece::CheckIfClicked(GLfloat* rgba)
{
  bool selected = true;
  GLfloat sa = selectedColour[3];
  GLfloat a = rgba[3];

  for (int i=0; i < 3; i++)
  {
    selected &= Match(selectedColour[i]*sa, rgba[i]*a);
  }
/*
  if (selected)
  {
    this->state = SELECTED;
  }
*/

  return selected;
}

bool Piece::Match(GLfloat a, GLfloat b)
{
  GLfloat diff = a-b;
  return (diff < 0.005 && diff > -0.005);
}

void Piece::Draw(int i, int j)
{
  GLfloat red[] = {1.0, 0.0, 0.0, 1.0}; // Make static?
  GLfloat blue[] = {0.0, 0.0, 1.0, 1.0};
  GLfloat white[] = {1.0, 1.0, 0.0, 1.0}; // Make static?
  GLfloat black[] = {0.0, 1.0, 1.0, 1.0};
  
  GLfloat* col = NULL;

  if (selectionMode)
  {
    col = selectedColour;
  }
  else
  {
    switch (state)
    {
      case SELECTED:
        col = white;
        break;
     case HIGHLIGHTED:
        col = black;
        break;
     default:
       col = ((i+j)%2 == 0) ? red : blue;
    }
  }
  
  // Draw square under this piece
  glColor4fv(col);
  glBegin(GL_POLYGON);  
    glVertex3f(i*SQUARE_SIZE, j*SQUARE_SIZE, 0.0);
    glVertex3f((i+1)*SQUARE_SIZE, j*SQUARE_SIZE, 0.0);
    glVertex3f((i+1)*SQUARE_SIZE, (j+1)*SQUARE_SIZE, 0.0);
    glVertex3f(i*SQUARE_SIZE, (j+1)*SQUARE_SIZE, 0.0);
  glEnd();

  if (type != EMPTY)
  {
    col = (colour == WHITE) ? white : black;
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
      model = modelManager->GetModel("PAWN");
      break;
    case KNIGHT:
      model = modelManager->GetModel("KNIGHT");
      break;
    case BISHOP:
      model = modelManager->GetModel("BISHOP");
      break;
    case CASTLE:
      model = modelManager->GetModel("CASTLE");
      break;
   case KING:
      model = modelManager->GetModel("KING");
      break;
   case QUEEN:
      model = modelManager->GetModel("QUEEN");
      break;  
  }
}
