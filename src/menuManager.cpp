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

  GLfloat boxCol[3] = { 0.0f, 0.0f, 0.0f };
  for (int i=0; i<4; i++)
  {
    GLfloat origin[3] = { 0.0f, WINDOW_HEIGHT*2/3 - 50.0f*i - 10.0f, 0.5f };
    boxes[i] = new Box2d(origin, WINDOW_WIDTH/3, 50.0f, boxCol);
  }

  GLfloat origin[3] = { 0.0f, 0.0f, 0.0f };
  backBox = new Box2d(origin, WINDOW_WIDTH/3, WINDOW_HEIGHT, boxCol);
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
 
  backBox->Draw();
/*
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
*/
  for (int i=0; i < 4; i++)
  {
    DrawOption(i);
  }

  // Restore saved matricies ready for 3D rendering.
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
}

// Should only really draw when things change not all the time.
void MenuManager::DrawOption(int n)
{
  glPushMatrix();

  // Draw box around option
  boxes[n]->Draw();

  GLfloat normCol[3] = { 1.0f, 1.0f, 1.0f };
  GLfloat selCol[3] = { 0.0f, 0.0f, 1.0f };
  GLfloat* col = (n == selectedOption) ? selCol : normCol;
  glColor3fv(col);

  int optWidth = (int)strlen(text[state][n])*15;
  GLfloat pos[3] = { WINDOW_WIDTH/6 - optWidth/2, boxes[n]->GetOrigin()[1]+10, 1.0f };
  glTranslatef(pos[0], pos[1], pos[2]);
  glScalef(0.25f, 0.25f, 0.5f);

  for (int i=0; i < (int)strlen(text[state][n]); i++)
  {
    glutStrokeCharacter(GLUT_STROKE_ROMAN, text[state][n][i]);
  }
  
  glPopMatrix();
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
  switch(button)
  {
    case GLUT_LEFT_BUTTON:
      if (state == GLUT_UP)
      {
        OptionClicked();
      }
    break;
  }
}

void MenuManager::MouseMotion(int x, int y)
{
  for (int i=0; i < 4; i++)
  {
    if (boxes[i]->IsPointInBox(x, y))
    {
      selectedOption = i;
      return;
    }
  }
}



