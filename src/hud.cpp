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
  // Save projection matrix on stack then set it up for ortho drawing.
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0.0, WINDOW_HEIGHT, 0.0, WINDOW_WIDTH, -1.0, 10.0);

  // Save model view matrix then reset it.
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  
  // Disable face culling, depth buffering and lighting for 2D drawing.
  // TODO: not sure if necessary
  glDisable(GL_CULL_FACE);
  glDisable(GL_LIGHTING);
  glClear(GL_DEPTH_BUFFER_BIT);

  // Draw HUD  
  glBegin(GL_QUADS);
    glColor4f(0.0f, 0.3f, 0.5f, 0.5f);
    glVertex2f(0.0, 0.0);
    glVertex2f(WINDOW_WIDTH, 0.0);
    glVertex2f(WINDOW_WIDTH, 50.0);
    glVertex2f(0.0, 50.0);
  glEnd();
  
  glColor3f(1.0f, 1.0f, 1.0);
  glScalef(0.25f, 0.25f, 0.5f);
  glTranslatef(50.0f, 50.0f, 1.0f);
  int n = (whiteToMove) ? 0 : 1;
  DrawText(n);

  glTranslatef(2500.f, 0.0f, 1.0f);
  DrawText(2);

  // Restore saved matricies ready for 3D rendering.
  glEnable(GL_LIGHTING);
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
}

// ## Private Methods ## //

void Hud::DrawText(int n)
{
  for (int i=0; i < (int)strlen(text[n]); i++)
  {
    glutStrokeCharacter(GLUT_STROKE_ROMAN, text[n][i]);
  }
}
