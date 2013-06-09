#ifndef _MENU_MANAGER_H
#define _MENU_MANAGER_H

#include "headers.h"

class MenuManager
{
  private:

  public:
    MenuManager();
    ~MenuManager();

    void Init();
    void Update();
    void Draw();
    void KeyboardPress(unsigned char key);
    

};

#endif
