#include "chess.h"

/*
 * Chess3D main entry point
 */

#define DEBUG 0

float avgVertex[3];
GLfloat cameraPos[3];
GLfloat lightPos[3] = {0.36, -0.1448, -0.010616};

enum State { Menu, Game };
State state;

MenuManager menuManager;
Game game;


void init() 
{
  glClearColor (0.0, 0.0, 0.0, 0.0);
  Logger.WriteInfo("Initialising...");
  
  menuManager = new MenuManager();
  game = new Game();
  
  // TODO: change to menu when start writing menu
  state = State.Game; 
}

void display(void)
{
  // Clear colour and depth buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  switch (state)
  {
    case Menu:
      menuManager.Draw();
      break;
    case Game:
      game.Draw();
      break;
  }  
  
  glutSwapBuffers();
}

void reshape (int w, int h)
{
  cout << "reshape" << endl;
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  
  // Setup perspective
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  gluPerspective (90, (GLfloat)w / (GLfloat)h, 0.01, 10.0);
}

void update()
{
  // Move light depending on current coords
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

  // Move camera depending on current coords
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2],
    avgVertex[0], avgVertex[1], avgVertex[2], 0.0f, 1.0f,  0.0f);
  display();
}

/*
 * Allows user to move camera and light positions using keyboard
 */
void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 27: // ESC
    exit(0);
    break;
  }

  switch (state)
  {
    case Menu:
      menu.KeyboardPress(key);
    break;

    case Game:
      game.KeyboardPress(key);
    break;
  }
}

int main(int argc, char** argv)
{
  // Initialize graphics window
  glutInit(&argc, argv);
  // Use double buffering and depth testing
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 

  glutInitWindowSize (512, 512); 
  glutInitWindowPosition (0, 0);
  glutCreateWindow ("Chess3D");

  // Initialize OpenGL
  init();

  // Initialize callback functions
  glutDisplayFunc(display);
  glutIdleFunc(update); 
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);

  // Start rendering 
  glutMainLoop();
}