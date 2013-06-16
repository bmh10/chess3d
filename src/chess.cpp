#include "headers.h"
#include "game.h"
#include "menuManager.h"


/*
 * Chess3D main entry point
 */
enum State { MENU, GAME };
State state;

MenuManager *menuManager;
Game *game;

void Init() 
{
  glClearColor (0.0, 0.5, 1.0, 0.0);
  Logger::Info("Initialising.");
  
  menuManager = new MenuManager();
  game = new Game();
  
  // TODO: change to menu when start writing menu
  state = MENU; 
}

void Display()
{
  // Clear colour and depth buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  switch (state)
  {
    case MENU:
      menuManager->Draw();
      break;
    case GAME:
      game->Draw();
      break;
  }  
  
  glutSwapBuffers();
}

void Reshape (int w, int h)
{
  Logger::Info("Reshape.");
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
    case MENU:
      menuManager->Update();
      if (menuManager->GameStarted()) state = GAME;
      break;
    case GAME:
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
    case MENU:
      menuManager->KeyboardPress(key);
    break;
    case GAME:
      game->KeyboardPress(key);
    break;
  }
}

// Maps special keys to normals key presses for simplicity.
void Special(int key, int x, int y)
{
  switch (key)
  {
    case GLUT_KEY_UP:
      Keyboard('w', x, y);
      break;
    case GLUT_KEY_DOWN:
      Keyboard('s', x, y);
      break;
  }
}

void Mouse(int button, int state, int x, int y)
{
  switch (state)
  {
    case MENU:
      menuManager->MousePress(button, state, x, WINDOW_HEIGHT-y);
    break;
    case GAME:
      game->MousePress(button, state, x, WINDOW_HEIGHT-y);
    break;
  }
}

int main(int argc, char** argv)
{
  // Initialize graphics window
  glutInit(&argc, argv);
  // Use double buffering and depth testing
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 

  glutInitWindowSize (WINDOW_WIDTH, WINDOW_HEIGHT);
  glutInitWindowPosition (0, 0);
  glutCreateWindow ("Chess3D");

  // Initialize OpenGL
  Init();

  // Initialize callback functions
  glutDisplayFunc(Display);
  glutIdleFunc(Update); 
  glutReshapeFunc(Reshape);
  glutKeyboardFunc(Keyboard);
  glutSpecialFunc(Special);
  glutMouseFunc(Mouse);

  // Start rendering 
  glutMainLoop();
}
