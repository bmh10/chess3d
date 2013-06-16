#ifndef _MENU_MANAGER_H
#define _MENU_MANAGER_H

#include "headers.h"

class MenuManager
{
  private:
    char text[2][20];

    void Init();
    void DrawOption(int n, GLfloat* pos, GLfloat* col);

  public:
    MenuManager();
    ~MenuManager();

    void Update();
    void Draw();
    void KeyboardPress(unsigned char key);
    void MousePress(int button, int state, int x, int y);
    

};

#endif
