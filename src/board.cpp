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
  int x, y;
  // Pawns and empty squares.
  for (x = 0; x < 8; x++)
  {
    pieces[x][1] = new Piece(PAWN, WHITE, modelManager);
    pieces[x][6] = new Piece(PAWN, BLACK, modelManager);
    for (y = 2; y < 6; y++)
    {
      pieces[x][y] = new Piece(EMPTY);
    }
  }
  
  // Back rows.
  for (x = 0; x < 8; x++)
  {
    if (x == 0 || x == 7)
    {
      pieces[x][0] = new Piece(CASTLE, WHITE, modelManager);
      pieces[x][7] = new Piece(CASTLE, BLACK, modelManager);
    }
    else if (x == 1 || x == 6)
    {
      pieces[x][0] = new Piece(KNIGHT, WHITE, modelManager);
      pieces[x][7] = new Piece(KNIGHT, BLACK, modelManager);
    }
    else if (x == 2 || x == 5)
    {
      pieces[x][0] = new Piece(BISHOP, WHITE, modelManager);
      pieces[x][7] = new Piece(BISHOP, BLACK, modelManager);
    }
  }

  pieces[3][0] = new Piece(KING, WHITE, modelManager);
  pieces[3][7] = new Piece(KING, BLACK, modelManager);
  pieces[4][0] = new Piece(QUEEN, WHITE, modelManager);
  pieces[4][7] = new Piece(QUEEN, BLACK, modelManager);

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
