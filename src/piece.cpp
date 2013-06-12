#include "piece.h"

Piece::Piece(PieceType type)
{
  this->type = type;
  selectionMode = false;
  selected = false;
}

Piece::Piece(PieceType type, PieceColour colour, ModelManager* modelManager)
{
  this->type = type;
  this->colour = colour;
  LoadModel(modelManager);
  selectionMode = false;
  selected = false;
}

Piece::~Piece()
{
}

void Piece::EnableSelectionMode(bool enable, int i, int j)
{
  selectionMode = enable;
  selectedColour[0] = (GLfloat)i/8.0;
  selectedColour[1] = (GLfloat)j/8.0;
  selectedColour[2] = 0.5;
for (int i=0; i < 3; i++)
  {
  cout << "SELCOL: " << selectedColour[i] << endl;
}
}

bool Piece::CheckIfSelected(GLfloat* rgba)
{
  bool selected = true;
  cout << "CHECK" << endl;
  for (int i=0; i < 3; i++)
  {
    cout << selectedColour[i] << " == " << rgba[i] << endl;
    selected &= (selectedColour[i] == rgba[i]);
  }
  cout << endl;

  if (selected)
  {
    this->selected = true;
  }

  return selected;
}

void Piece::Draw(int i, int j)
{
  assert(model != NULL);
  GLfloat red[] = {1.0, 0.0, 0.0}; // Make static?
  GLfloat blue[] = {0.0, 0.0, 1.0};
  GLfloat white[] = {1.0, 1.0, 0.0}; // Make static?
  GLfloat black[] = {0.0, 1.0, 1.0};
  
  GLfloat* col = NULL;

  if (selectionMode)
  {
    col = selectedColour;
  }
  
  if (selected)
  {
    col = white;
  }

  // Draw square under this piece
  glBegin(GL_POLYGON);
    if (!selectionMode && !selected) col = ((i+j)%2 == 0) ? red : blue;
    glColor3fv(col);
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
