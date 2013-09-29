#ifndef _HUD_H
#define _HUD_H

#include "headers.h"
#include "box2d.h"
#include "board.h"
#include "piece.h"

#define NUM_OPTIONS 4

class Hud
{
  private:
  	//Board board;
    char text[10][30];
    
    bool menuIsOpen;
    int selectedOption;
    Box2d* hudBox;
    Box2d* optionBoxes[NUM_OPTIONS];

    void DrawText(int n);

  public:
    Hud();
    ~Hud();

    void Init();
    void Draw(bool whiteToMove, BoardState boardState);
    void OptionClicked();
    void MouseMotion(int x, int y);
    void MousePress(int button, int state, int x, int y);
};

#endif
