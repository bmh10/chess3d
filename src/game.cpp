#include "game.h"

Game::Game()
{
  Init();
}

Game::~Game()
{
}

void Game::Init()
{
  Logger::Info("Initializing game.");

  centreBoard[0] = 0.02f*4.0f;
  centreBoard[1] = 0.0f;
  centreBoard[2] = 0.0f;

  // Set initial camera position relative to centre of board
  for (int i=0; i < 3; i++)
    cameraPos[i] = centreBoard[i];

  cameraPos[0] += 0.0f;
  cameraPos[1] -= 0.05f;
  cameraPos[2] += 0.05f;

  // Put light in same place as camera
  for (int i=0; i < 3; i++)
    lightPos[i] = cameraPos[i];

  glShadeModel (GL_SMOOTH);
  GLfloat LightAmbient[] = {0.0, 0.0, 0.0, 1.0};
  GLfloat LightDiffuse[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat LightSpecular[] = {1.0, 1.0, 1.0, 0.1};
  GLfloat MaterialSpecular[] = {0.1, 0.1, 0.1, 1.0};
  GLfloat MaterialShininess[] = {128};
  
  // Enable lighting
  //glEnable (GL_LIGHTING);
  //glEnable (GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
  glLightfv(GL_LIGHT0, GL_AMBIENT,  LightAmbient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE,  LightDiffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
  
  // Set material parameters
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  MaterialSpecular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, MaterialShininess);
  
  glEnable(GL_COLOR_MATERIAL);
  //glColorMaterial(GL_FRONT,GL_DIFFUSE);
  
  // Enable Z-buffering
  glEnable(GL_DEPTH_TEST);
  
  // Cull back faces of polygons
  //glEnable(GL_CULL_FACE);
  //glCullFace(GL_BACK);
  
  // Initialise game components
  board = new Board();
  hud = new Hud();
}

void Game::Update()
{
  // Move light depending on current coords
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

  // Move camera depending on current coords
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2],
    centreBoard[0], centreBoard[1], centreBoard[2], 0.0f, 0.0f, 1.0f);
}

void Game::Draw()
{

/*
  if (DEBUG)
  {
    // Draw triangle at light source
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(lightPos[0], lightPos[1], lightPos[2]);
    glVertex3f(lightPos[0], lightPos[1]+0.1, lightPos[2]);
    glVertex3f(lightPos[0], lightPos[1]+0.1, lightPos[2]+0.1);
    glEnd();
  }
*/
  
/*
  if (textureOn)
    glEnable(GL_TEXTURE_2D);
  else
    glDisable(GL_TEXTURE_2D);
*/

    // Draw axis

    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0); glVertex3f(100.0, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0); glVertex3f(0.0, 100.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0); glVertex3f(0.0, 0.0, 100.0);
    
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0); glVertex3f(-100.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0); glVertex3f(0, -100.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0); glVertex3f(0, 0.0, -100.0);
    glEnd();

    board->Draw();
    hud->Draw(board->IsWhiteToMove());
}

void Game::KeyboardPress(unsigned char key)
{
  if (key == 'q') cameraPos[0] += 0.01;
  else if (key == 'a') cameraPos[0] -= 0.01;
  else if (key == 'w') cameraPos[1] += 0.01;
  else if (key == 's') cameraPos[1] -= 0.01;
  else if (key == 'e') cameraPos[2] += 0.01;
  else if (key == 'd') cameraPos[2] -= 0.01;
  
  else if (key == 'u') lightPos[0] += 0.01;
  else if (key == 'j') lightPos[0] -= 0.01;
  else if (key == 'i') lightPos[1] += 0.01;
  else if (key == 'k') lightPos[1] -= 0.01;
  else if (key == 'o') lightPos[2] += 0.01;
  else if (key == 'l') lightPos[2] -= 0.01;
}

void Game::MousePress(int button, int state, int x, int y)
{
  switch(button)
  {
    case GLUT_LEFT_BUTTON:
      if (state == GLUT_UP)
      {
        board->SelectSquareAt(x, y);
      }
    break;
  }
}
