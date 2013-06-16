#include "menuManager.h"

MenuManager::MenuManager()
{
  Init();
}

MenuManager::~MenuManager()
{
}

void MenuManager::Init()
{
  // Load text
  strcpy(text[0], "Single Player");
  strcpy(text[1], "Multiplayer");
  strcpy(text[2], "Options");
  strcpy(text[3], "Quit");
}

void MenuManager::Update()
{
}

void MenuManager::Draw()
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
  
  // Disable face culling and depth buffering for 2D drawing.
  // TODO: not sure if necessary
  glDisable(GL_CULL_FACE);
  glClear(GL_DEPTH_BUFFER_BIT);

  // Draw menu background
  glBegin(GL_QUADS);
    GLfloat w = WINDOW_WIDTH/3;
    GLfloat h = WINDOW_HEIGHT;
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(w, 0.0f);
    glVertex2f(w, h);
    glVertex2f(0.0, h);
  glEnd();

  // Draw options
  int optWidth;
  GLfloat col[3] = { 1.0f, 1.0f, 1.0f };
  
  //GLfloat translate[3] = { 0.0f, -150.0f, 0.0f };
  //glTranslatef(pos[0], startPos[1], pos[2]);
  
  for (int i=0; i < 4; i++)
  {
    glPushMatrix();
      optWidth = (int)strlen(text[i])*15;
      GLfloat pos[3] = { WINDOW_WIDTH/6 - optWidth/2, WINDOW_HEIGHT*2/3 - 50.0f*i, 1.0f };
      DrawOption(i, pos, col);
    glPopMatrix();
  }

  // Restore saved matricies ready for 3D rendering.
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
}

void MenuManager::DrawOption(int n, GLfloat* pos, GLfloat* col)
{
  // Draw box around option
  glBegin(GL_QUADS);
    GLfloat w = WINDOW_WIDTH/3;
    GLfloat h = 50.f;
    GLfloat y = pos[1]-10.0f;
    glColor3f(0.0f, 0.2f, 0.0f);
    glVertex3f(0.0f, y, 0.5f);
    glVertex3f(w, y, 0.5f);
    glVertex3f(w, y + h, 0.5f);
    glVertex3f(0.0, y + h, 0.5f);
  glEnd();

  glColor3fv(col);
  glTranslatef(pos[0], pos[1], pos[2]);
  glScalef(0.25f, 0.25f, 0.5f);

  for (int i=0; i < (int)strlen(text[n]); i++)
  {
    glutStrokeCharacter(GLUT_STROKE_ROMAN, text[n][i]);
  }

}

void MenuManager::KeyboardPress(unsigned char key)
{
}

void MenuManager::MousePress(int button, int state, int x, int y)
{
}
