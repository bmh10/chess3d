#ifndef _MENU_MANAGER_H
#define _MENU_MANAGER_H

#include "headers.h"
#include "box2d.h"

#define NUM_OPTIONS 4

enum MenuState { MAIN, OPTIONS, AREYOUSURE };

class MenuManager
{
  private:
    MenuState state;
    Box2d* boxes[4];
    char text[3][4][25];
    int selectedOption;
    bool gameStarted;
    Box2d* backBox;

    void Init();
    void DrawOption(int n);
    void OptionClicked();

  public:
    MenuManager();
    ~MenuManager();

    bool GameStarted();
    void Update();
    void Draw();
    void KeyboardPress(unsigned char key);
    void MousePress(int button, int state, int x, int y);
    void MouseMotion(int x, int y);

};

#endif
