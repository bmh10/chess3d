#include "headers.h"
#include "game.h"
#include "menuManager.h"


/*
 * Chess3D main entry point
 */

enum State { MenuState, GameState };
State state;

MenuManager *menuManager;
Game *game;

void Init() 
{
  glClearColor (0.0, 0.0, 0.0, 0.0);
  Logger::Info("Initialising...");
  
  menuManager = new MenuManager();
  game = new Game();
  
  // TODO: change to menu when start writing menu
  state = GameState; 
}

void Display()
{
  // Clear colour and depth buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  switch (state)
  {
    case MenuState:
      menuManager->Draw();
      break;
    case GameState:
      game->Draw();
      break;
  }  
  
  glutSwapBuffers();
}

void Reshape (int w, int h)
{
  Logger::Info("Reshape...");
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  
  // Setup perspective
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  gluPerspective (90, (GLfloat)w / (GLfloat)h, 0.01, 10.0);
}

void Update()
{
  switch (state)
  {
    case MenuState:
      menuManager->Update();
      break;
    case GameState:
      game->Update();
      break;
  }

  Display();
}

/*
 * Allows user to move camera and light positions using keyboard
 */
void Keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 27: // ESC
    exit(0);
    break;
  }

  switch (state)
  {
    case MenuState:
      menuManager->KeyboardPress(key);
    break;
    case GameState:
      game->KeyboardPress(key);
    break;
  }

}

int main(int argc, char** argv)
{
  // Initialize graphics window
  glutInit(&argc, argv);
  // Use double buffering and depth testing
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 

  glutInitWindowSize (1024, 1024); 
  glutInitWindowPosition (0, 0);
  glutCreateWindow ("Chess3D");

  // Initialize OpenGL
  Init();

  // Initialize callback functions
  glutDisplayFunc(Display);
  glutIdleFunc(Update); 
  glutReshapeFunc(Reshape);
  glutKeyboardFunc(Keyboard);

  // Start rendering 
  glutMainLoop();
}
