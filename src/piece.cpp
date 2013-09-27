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
  LoadModelAnd2dTexture(modelManager);
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

bool Piece::CheckIfClicked(int x, int y, GLfloat* rgba)
{
  bool selected = true;
  GLfloat sa = selectedColour[3];
  GLfloat a = rgba[3];

  // 2D selection (takes priority when 2D board is active.)
  GLfloat* origin = box->GetOrigin();
  // cout << x << ", " << y << " | " << origin[0] << "< " << origin[1] << endl;
  if (box->IsPointInBox(x, y))
  {
    return true;
  }

  //cout << rgba[0] << ", " << rgba[1] << ", " << rgba[2] << ", " << rgba[3] << endl;
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
  COL_YELLOW(1.0f)
  COL_CYAN(1.0f)
  GLfloat navy[] = {0.0, 0.0, 0.2, 1.0};
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
       col = ((i+j)%2 == 0) ? white : navy;
    }
  }

  GLfloat origin[] = { 50.0f + i*50.0f, WINDOW_HEIGHT - 500.0f + j*50.0f, 1.0f };
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
