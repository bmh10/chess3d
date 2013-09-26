#include "hud.h"

Hud::Hud()
{
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
}

void Hud::Draw(bool whiteToMove)
{
  OpenGLUtil::StartOrtho();

  // Draw HUD  
  glBegin(GL_QUADS);
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
    glVertex2f(0.0, WINDOW_HEIGHT);
    glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT);
    glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT-50.0);
    glVertex2f(0.0, WINDOW_HEIGHT-50);
  glEnd();
  
  glColor3f(1.0f, 1.0f, 1.0);
  glTranslatef(50.0f, WINDOW_HEIGHT-40.0f, 1.0f);
  glScalef(0.25f, 0.25f, 0.5f);
  int n = (whiteToMove) ? 0 : 1;
  DrawText(n);

  glTranslatef(2300.0f, 0.0f, 0.0f);
  DrawText(2);

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
