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
  // Draw squares
  glBegin(GL_POLYGON);
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(SQUARE_SIZE, 0.0, 0.0);
  glVertex3f(SQUARE_SIZE, SQUARE_SIZE, 0.0);
  glVertex3f(0.0, SQUARE_SIZE, 0.0);
  glEnd();

  // Draw pieces

}
