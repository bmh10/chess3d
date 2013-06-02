#ifndef _GAME_H

#define _GAME_H

class Game
{
  private:
    GLfloat cameraPos[3];
    GLfloat lightPos[3] = {0.36, -0.1448, -0.010616};
    Board board;

  public:
    Game();
    ~Game();

    void Init();
    void Update();
    void Draw();
    void KeyboardPress(unsigned char key);



};

#endif
