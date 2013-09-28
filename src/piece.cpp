#include "piece.h"

Piece::Piece(PieceType type)
{
  this->type = type;
  selectionMode = false;
  hasMoved = false;
  state = NORMAL;
}

Piece::Piece(PieceType type, PieceColour colour, ModelManager* modelManager)
{
  this->type = type;
  this->colour = colour;
  LoadModelAnd2dTexture(modelManager);
  selectionMode = false;
  hasMoved = false;
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

void Piece::SetHasMoved()
{
  hasMoved = true;
}

bool Piece::HasMoved()
{
  return hasMoved;
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

bool Piece::CheckIfClicked(int x, int y, GLfloat* rgba, bool in2D)
{
  bool selected = true;
  GLfloat sa = selectedColour[3];
  GLfloat a = rgba[3];

  // 2D selection - simple box check.
  if (in2D)
  {
    return box->IsPointInBox(x, y);
  }
  // 3D selection - check colours match.
  else
  {
    for (int i=0; i < 3; i++)
    {
      selected &= Match(selectedColour[i]*sa, rgba[i]*a);
    }
  
    return selected;
  }
}

bool Piece::Match(GLfloat a, GLfloat b)
{
  GLfloat diff = a-b;
  return (diff < 0.005 && diff > -0.005);
}

void Piece::Draw(int i, int j)
{
  Colour red             = COL_RED   (1.0f);
  Colour blue            = COL_BLUE  (1.0f);
  Colour yellow          = COL_YELLOW(1.0f);
  Colour cyan            = COL_CYAN  (1.0f);
  Colour selectedCol     = Colour(1.0, 1.0, 0.0, 0.8);
  Colour highlightedCol  = Colour(0.0, 1.0, 1.0, 0.8);
  Colour highlightedCol2 = Colour(0.0, 0.5, 1.0, 0.8);
  
  Colour* col;

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
  col->Set();
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

// Assumes already in ortho drawing mode.
void Piece::Draw2D(int i, int j)
{
  Colour white           = COL_WHITE (1.0f);
  Colour black           = COL_BLACK (1.0f);
  Colour yellow          = COL_YELLOW(1.0f);
  Colour cyan            = COL_CYAN  (1.0f);
  Colour navy            = Colour(0.0, 0.0, 0.2, 1.0);
  Colour selectedCol     = Colour(1.0, 1.0, 0.0, 0.8);
  Colour highlightedCol  = Colour(0.0, 1.0, 1.0, 0.8);
  Colour highlightedCol2 = Colour(0.0, 0.5, 1.0, 0.8);

  Colour col;
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
       col = ((i+j)%2 == 0) ? white : navy;
    }
  }

  Coord origin = Coord(WINDOW_WIDTH/2 - 4*50.0f + i*50.0f, WINDOW_HEIGHT - 500.0f + j*50.0f, 1.0f);
  if (type == EMPTY)
    box = new Box2d(origin, 50.0f, 50.0f, col);
  else
    box = new Box2d(origin, 50.0f, 50.0f, col, tex2dName);

  box->Draw();
}

void Piece::LoadModelAnd2dTexture(ModelManager* modelManager)
{
  assert(modelManager != NULL);
  tex2dName = modelManager->GetPiece2d(type, colour);

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
