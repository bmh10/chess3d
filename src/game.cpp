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
  
  //glEnable(GL_COLOR_MATERIAL);
  //glColorMaterial(GL_FRONT,GL_DIFFUSE);
  
  // Enable Z-buffering
  glEnable(GL_DEPTH_TEST);
  
  // Cull back faces of polygons
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  
  // Set initial camera position relative to centre point of model
  for (int i=0; i < 3; i++)
    cameraPos[i] = avgVertex[i];
  cameraPos[0] += 0.025;
  cameraPos[2] -= 0.1;

  // Initialise game components
  board = new Board();
}

void Game::Update()
{
  // Move light depending on current coords
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

  // Move camera depending on current coords
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2],
    avgVertex[0], avgVertex[1], avgVertex[2], 0.0f, 1.0f,  0.0f);
  Draw();

}

void Game::KeyboardPress()
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