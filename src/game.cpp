#include "game.h"

Game::Game()
{
  Init();
}

Game::~Game()
{
}

void Game::SetDemoMode(bool enable)
{
  demoMode = enable;
  camera->RotateToWhite(true);
}

void Game::Init()
{
  Logger::Info("Initializing game.");

  GLfloat* centerBoard = new GLfloat[3];
  centerBoard[0] = SQUARE_SIZE*4.0f;
  centerBoard[1] = SQUARE_SIZE*4.0f;
  centerBoard[2] = 0.0f;

  // Set initial camera position relative to centre of board
  GLfloat* cameraPos = new GLfloat[3];
  for (int i=0; i < 3; i++)
    cameraPos[i] = centerBoard[i];

  cameraPos[0] += 0.0f;
  cameraPos[1] -= 0.12f;
  cameraPos[2] += 0.08f;

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
  glEnable (GL_LIGHTING);
  glEnable (GL_LIGHT0);
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

  // Enable blending for transparent objects
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  // Initialise game components
  camera = new Camera(cameraPos, 0.0f, centerBoard, CONTINOUS_ROTATE);
  board = new Board(camera);
  hud = new Hud();
  demoMode = true;
}

void Game::Update()
{
  // Move light depending on current coords
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
  // Move camera depending on current coords
  camera->Update();
}

void Game::Draw()
{
/*
  if (textureOn)
    glEnable(GL_TEXTURE_2D);
  else
    glDisable(GL_TEXTURE_2D);
*/

    // Draw axis
    if (DEBUG)
    {
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

      // Draw light source
      /*glBegin(GL_POLYGON);
      glVertex3f(lightPos[0], lightPos[1], lightPos[2]);
      glVertex3f(lightPos[0], lightPos[1] + 0.1f, lightPos[2]);
      glVertex3f(lightPos[0], lightPos[1] + 0.1f, lightPos[2] + 0.1f);
      glEnd();*/
    }

    // Ground plane
    GLfloat n = 100.0;
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-n, -n, -0.011);
    glVertex3f(n, -n, -0.011);
    glVertex3f(n, n, -0.011);
    glVertex3f(-n, n, -0.011);
    glEnd();

    board->Draw();
    if (!demoMode)
    {
      hud->Draw(board->IsWhiteToMove());
    }
}

void Game::KeyboardPress(unsigned char key)
{
  camera->KeyboardPress(key);
}

void Game::MousePress(int button, int state, int x, int y)
{
  camera->MousePress(button, state, x, y);
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
