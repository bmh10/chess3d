#include "board.h"

Board::Board()
{
  Init();
}

Board::~Board()
{
}

void Board::Init()
{
  modelManager = new ModelManager();
  modelManager->LoadAllModels();
  
  // Initialize pieces
  //TODO
  int i, j;
  for (i = 0; i < 8; i++)
  {
    for (j = 0; j < 8; j++)
    {
      pieces[i][j] = new Piece(EMPTY, NULL);
    }
  }
  pieces[4][4] = new Piece(PAWN, modelManager->GetModel("pawn"));
}

void Board::Draw()
{

  GLfloat red[] = {1.0, 0.0, 0.0}; // Make static?
  GLfloat blue[] = {0.0, 0.0, 1.0};
  GLfloat *col = red;
  int i, j;

  // Draw board base
  glBegin(GL_POLYGON);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(0.0, 0.0, -0.01);
    glVertex3f(8*SQUARE_SIZE, 0.0, -0.01);
    glVertex3f(8*SQUARE_SIZE, 8*SQUARE_SIZE, -0.01);
    glVertex3f(0.0, 8*SQUARE_SIZE, -0.01);
  glEnd();

  // Draw squares
  for (i = 0; i < 8; i++)
  {
    for (j = 0; j < 8; j++)
    {
      glBegin(GL_POLYGON);
        col = ((i+j)%2 == 0) ? red : blue;
        glColor3fv(col);
        glVertex3f(i*SQUARE_SIZE, j*SQUARE_SIZE, 0.0);
        glVertex3f((i+1)*SQUARE_SIZE, j*SQUARE_SIZE, 0.0);
        glVertex3f((i+1)*SQUARE_SIZE, (j+1)*SQUARE_SIZE, 0.0);
        glVertex3f(i*SQUARE_SIZE, (j+1)*SQUARE_SIZE, 0.0);
      glEnd();
    }
  }

  // Draw pieces
  for (i = 0; i < 8; i++)
  {
    for (j = 0; j < 8; j++)
    {
      pieces[i][j]->Draw(i, j);
    }
  }

}
