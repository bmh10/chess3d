#ifndef _MENU_MANAGER_H
#define _MENU_MANAGER_H

#include "headers.h"

#define NUM_OPTIONS 4

class MenuManager
{
  private:
    char text[4][20];
    int selectedOption;
    bool gameStarted;

    void Init();
    void DrawOption(int n, GLfloat* pos, GLfloat* col);
    void OptionClicked();

  public:
    MenuManager();
    ~MenuManager();

    bool GameStarted();
    void Update();
    void Draw();
    void KeyboardPress(unsigned char key);
    void MousePress(int button, int state, int x, int y);
    

};

#endif
