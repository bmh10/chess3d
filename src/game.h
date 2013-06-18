#ifndef _GAME_H
#define _GAME_H

#include "headers.h"
#include "board.h"
#include "hud.h"

#define ZOOM_MAX 0.07f
#define ZOOM_MIN -0.07f

class Game
{
  private:
    GLfloat cameraPos[3];
    GLfloat lightPos[3];
    GLfloat centreBoard[3];
    GLfloat rotationAngle;
    Board *board;
    Hud *hud;
    bool demoMode;

    void Init();
    void Zoom(bool zoomIn);

  public:
    Game();
    ~Game();

    void SetDemoMode(bool enable);
    void Update();
    void Draw();
    void KeyboardPress(unsigned char key);
    void MousePress(int button, int state, int x, int y);
};

#endif
