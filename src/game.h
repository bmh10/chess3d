#ifndef _GAME_H
#define _GAME_H

#include "headers.h"
#include "board.h"

class Game
{
  private:
    GLfloat cameraPos[3];
    GLfloat lightPos[3];
    GLfloat centreBoard[3];
    Board *board;

    void Init();

  public:
    Game();
    ~Game();

    
    void Update();
    void Draw();
    void KeyboardPress(unsigned char key);
    void MousePress(int button, int state, int x, int y);
};

#endif
