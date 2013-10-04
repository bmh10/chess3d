#ifndef _GAME_H
#define _GAME_H

#include "headers.h"
#include "camera.h"
#include "board.h"
#include "hud.h"

class Game
{
  private:
    Coord3D lightPos;

    Camera camera;
    Board board;
    Hud hud;
    bool demoMode;

    void Init();

  public:
    Game();
    ~Game();

    bool QuitGame();
    void SetDemoMode(bool enable);
    void Update();
    void Draw();
    void KeyboardPress(unsigned char key);
    void MousePress(int button, int state, int x, int y);
    void MouseMotion(int x, int y);
};

#endif
