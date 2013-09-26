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
  COL_RED(1.0f)
  COL_BLUE(1.0f)
  COL_YELLOW(1.0f)
  COL_CYAN(1.0f)
  GLfloat selectedCol[] = {1.0, 1.0, 0.0, 0.8};
  GLfloat highlightedCol[] = {0.0, 1.0, 1.0, 0.8};
  GLfloat highlightedCol2[] = {0.0, 0.5, 1.0, 0.8};
  
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
        col = selectedCol;
        break;
     case HIGHLIGHTED:
        col = ((i+j)%2 == 0) ? highlightedCol : highlightedCol2;
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
    col = (colour == WHITE) ? yellow : cyan;
    model->DrawAt(
      i*SQUARE_SIZE + SQUARE_SIZE/2, 
      j*SQUARE_SIZE + SQUARE_SIZE/2,
      0,
      PIECE_SCALE,
      col);
  }
}

void Piece::Draw2D(int i, int j)
{
  COL_WHITE(1.0f)
  COL_BLACK(1.0f)
  COL_RED(1.0f)
  GLfloat origin[] = { 50.0f + i*25.0f, WINDOW_HEIGHT - 270.0f + j*25.0f, 1.0f };
  GLfloat* col = ((i+j)%2 == 0) ? white : black;
  if (type == PAWN)
    col = red;
  Box2d box = Box2d(origin, 25.0f, 25.0f, col);
  box.Draw();
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
