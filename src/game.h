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

  public:
    Game();
    ~Game();

    void Init();
    void Update();
    void Draw();
    void KeyboardPress(unsigned char key);

};

#endif
