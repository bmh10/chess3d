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
  // Initialize pieces
  
}

void Board::Draw()
{
  GLfloat red[] = {1.0, 0.0, 0.0}; // Make static?
  GLfloat blue[] = {0.0, 0.0, 1.0};
  GLfloat *col = red;
  
  // Draw board base
  glBegin(GL_POLYGON);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(0.0, 0.0, -0.01);
    glVertex3f(8*SQUARE_SIZE, 0.0, -0.01);
    glVertex3f(8*SQUARE_SIZE, 8*SQUARE_SIZE, -0.01);
    glVertex3f(0.0, 8*SQUARE_SIZE, -0.01);
  glEnd();

  // Draw squares
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
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

}
