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
}

void Game::Init()
{
  Logger::Info("Initializing game.");

  centreBoard[0] = SQUARE_SIZE*4.0f;
  centreBoard[1] = SQUARE_SIZE*4.0f;
  centreBoard[2] = 0.0f;

  // Set initial camera position relative to centre of board
  for (int i=0; i < 3; i++)
    cameraPos[i] = centreBoard[i];

  cameraPos[0] += 0.0f;
  cameraPos[1] -= 0.12f;
  cameraPos[2] += 0.08f;
  rotationAngle = 0.0f;

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
  board = new Board();
  hud = new Hud();
  demoMode = true;
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

  if (demoMode)
  {
    rotationAngle += 0.2f;
  }
  else if (board->GetRotateCam())
  {
    // TODO: make it rotate shortest distance rather than same way all the time.
    rotationAngle += 5.0f;
  }

  if (rotationAngle > 360.0f)
  {
    rotationAngle = 0.0f;  
  }

  if ((board->IsWhiteToMove() && rotationAngle == 0.0f)
      || (!board->IsWhiteToMove() && rotationAngle == 180.0f))
  {
    board->SetRotateCam(false);
  }


  glTranslatef(centreBoard[0], centreBoard[1], centreBoard[2]);
  glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
  glTranslatef(-centreBoard[0], -centreBoard[1], -centreBoard[2]);
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
  // Left/right to rotate camera.
  if (key == 'a') rotationAngle += 2.0f;
  else if (key == 'd') rotationAngle -= 2.0f;

  // Up/down to zoom in or out.
  if (key == 'w') Zoom(true);
  else if (key == 's') Zoom(false);

/*
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
*/
}

void Game::MousePress(int button, int state, int x, int y)
{
  // Use scroll wheel to zoom in or out.
  if (button == 3) Zoom(true);
  else if (button == 4) Zoom(false);


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

void Game::Zoom(bool zoomIn)
{
  if (zoomIn && cameraPos[1] < ZOOM_MAX)
  {
    cameraPos[1] += 0.01f;
  }
  else if (!zoomIn && cameraPos[1] > ZOOM_MIN)
  {
    cameraPos[1] -= 0.01f; 
  }
}
