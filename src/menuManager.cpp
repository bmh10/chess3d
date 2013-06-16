#include "menuManager.h"

MenuManager::MenuManager()
{
  Init();
}

MenuManager::~MenuManager()
{
}

bool MenuManager::GameStarted()
{
  return gameStarted;
}

void MenuManager::Init()
{
  // Load text
  strcpy(text[MAIN][0], "Single Player");
  strcpy(text[MAIN][1], "Multiplayer");
  strcpy(text[MAIN][2], "Options");
  strcpy(text[MAIN][3], "Quit");

  strcpy(text[OPTIONS][0], "Sound");
  strcpy(text[OPTIONS][1], "Language");
  strcpy(text[OPTIONS][2], "Ingame Options");
  strcpy(text[OPTIONS][3], "Back");

  selectedOption = 0;
  gameStarted = false;
  state = MAIN;
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
  GLfloat normCol[3] = { 1.0f, 1.0f, 1.0f };
  GLfloat selCol[3] = { 0.0f, 0.0f, 1.0f };
  GLfloat* col;
  
  for (int i=0; i < 4; i++)
  {
    glPushMatrix();
      optWidth = (int)strlen(text[state][i])*15;
      GLfloat pos[3] = { WINDOW_WIDTH/6 - optWidth/2, WINDOW_HEIGHT*2/3 - 50.0f*i, 1.0f };
      col = (i == selectedOption) ? selCol : normCol;
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

  for (int i=0; i < (int)strlen(text[state][n]); i++)
  {
    glutStrokeCharacter(GLUT_STROKE_ROMAN, text[state][n][i]);
  }

}

void MenuManager::OptionClicked()
{
  switch (state)
  {
    case MAIN:
	  switch(selectedOption)
	  {
		// TODO: add different game started modes after implemented.
		case 0:
		  gameStarted = true;
		  break;
		case 1:
		  gameStarted = true;
		  break;
		case 2:
		  state = OPTIONS;
		  break;
		case 3:
		  exit(0);
		  break;
	  }
    break;
    case OPTIONS:
      // TODO: save preferences to file after setting. 
      // TODO: add restore to default settings option.
      switch(selectedOption)
	  {
		case 0:
		  // TODO: sound options
		  break;
		case 1:
		  // TODO: Language options
		  break;
		case 2:
		  // TODO: In-game options
		  break;
		case 3:
		  state = MAIN;
		  break;
	  }
    break;
  }

  selectedOption = 0;
}

void MenuManager::KeyboardPress(unsigned char key)
{
  key = tolower(key);
  if (key == 'w') 
  {
    if (selectedOption < 1) selectedOption = NUM_OPTIONS-1;
    else selectedOption = (selectedOption-1)%NUM_OPTIONS;
  }
  else if (key == 's') 
  {
    selectedOption = (selectedOption+1)%NUM_OPTIONS;
  }
  else if (key == 13) // 'Enter' key
  {
    OptionClicked();
  }
}

void MenuManager::MousePress(int button, int state, int x, int y)
{
}
