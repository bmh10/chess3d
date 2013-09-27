#include "hud.h"

Hud::Hud(Board* board)
{
  this->board = board;
  Init();
}

Hud::~Hud()
{
}

void Hud::Init()
{
  // Load text
  strcpy(text[0], "White to move");
  strcpy(text[1], "Black to move");
  strcpy(text[2], "Menu");
  strcpy(text[3], "X");
}

void Hud::Draw(bool whiteToMove, BoardState boardState)
{
  OpenGLUtil::StartOrtho();
  
  // Setup HUD box
  // TODO: Move into init - causes weird bug to 'Menu' text??
  GLfloat origin[] = { 0.0f, WINDOW_HEIGHT-50.0f, 0.0f };
  GLfloat col[] = { 0.0f, 0.0f, 0.0f, 0.7f };
  Box2d* hudBox = new Box2d(origin, WINDOW_WIDTH, 50.0f, col);

  // Draw HUD  
  hudBox->Draw();

  glColor3f(1.0f, 1.0f, 1.0);
  glPushMatrix();
    glTranslatef(50.0f, WINDOW_HEIGHT-40.0f, 1.0f);
    glScalef(0.25f, 0.25f, 0.5f);
    int n = (whiteToMove) ? 0 : 1;
    DrawText(n);
    if (boardState == CHECK)
    {
      glTranslatef(100.0f, 0.0f, 0.0f);
      DrawText(3);
    }
  glPopMatrix();

  glPushMatrix();
    glTranslatef(WINDOW_WIDTH - 100.0f, WINDOW_HEIGHT-40.0f, 1.0f);
    glScalef(0.25f, 0.25f, 0.5f);
    DrawText(2);
  glPopMatrix();

  // // Draw 2D board -- testing
  // GLfloat black[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  // GLfloat white[] = { 0.0f, 0.0f, 0.0f, 1.0f };
  // GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
  // Box2d* boxes[8][8];
  // //Piece* pieces = board->GetPieces();
  // for (int i = 0; i < 8; i++)
  // {
  //   for (int j = 0; j < 8; j++)
  //   {
      
  //     GLfloat origin[] = { 50.0f + i*25.0f, WINDOW_HEIGHT - 270.0f + j*25.0f, 1.0f };
  //     GLfloat* col = ((i+j)%2 == 0) ? white : black;
  //     boxes[i][j] = new Box2d(origin, 25.0f, 25.0f, col);
  //     boxes[i][j]->Draw();
  //     if (pieces[i][j]->GetType() == PAWN)
  //     {
  //       GLfloat origin[] = { 50.0f + i*25.0f + 5.0, WINDOW_HEIGHT - 270.0f + j*25.0f + 5.0, 1.0f };
  //       Box2d* pbox = new Box2d(origin, 15.0f, 15.0f, red);
  //       pbox->Draw();
  //     }
  //   }
  // }

  OpenGLUtil::EndOrtho();
}

// ## Private Methods ## //

void Hud::DrawText(int n)
{
  for (int i=0; i < (int)strlen(text[n]); i++)
  {
    glutStrokeCharacter(GLUT_STROKE_ROMAN, text[n][i]);
  }
}
