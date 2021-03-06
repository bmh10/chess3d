#include "hud.h"

Hud::Hud() {}

Hud::Hud(Board &board)
{
  this->board = &board;
  Init();
}

Hud::~Hud()
{
}

void Hud::Init()
{
  // Load text
  strcpy(text[0], "White to move");
  strcpy(text[1], "Black to move");
  strcpy(text[2], "Check");
  strcpy(text[3], "Stalemate");
  strcpy(text[4], "Checkmate - White Wins!");
  strcpy(text[5], "Checkmate - Black Wins!");
  strcpy(text[6], "Menu");
  strcpy(text[7], "2D Board");
  strcpy(text[8], "Opt2");
  strcpy(text[9], "Quit");

  // Init HUD components.
  menuIsOpen = false;
  selectedOption = -1;
  quitGame = false;

  // Main HUD box.
  Coord3D origin = Coord3D(0.0f, WINDOW_HEIGHT-50.0f, 0.0f);
  hudBox = new Box2d(origin, WINDOW_WIDTH, 50.0f, COL_BLACK(0.7f));

  // Menu option boxes.
  for (int i = 0; i < NUM_OPTIONS; i++)
  {
    Coord3D origin2 = Coord3D(WINDOW_WIDTH - 200.0f, WINDOW_HEIGHT-(i+1)*50.0f, 1.0f);
    optionBoxes[i] = new Box2d(origin2, 200.0f, 50.0f, COL_GREEN(0.9f), text[6+i]);
  }
}

bool Hud::QuitGame()
{
  bool b = quitGame;
  if (b) quitGame = false;
  return b;
}

void Hud::Draw()
{
  Colour white = COL_WHITE(1.0f);
  OpenGLUtil::StartOrtho();
  
  // Draw HUD.
  hudBox->Draw();

  // HUD text.
  glPushMatrix();
    white.Set();
    glTranslatef(50.0f, WINDOW_HEIGHT-40.0f, 1.0f);
    glScalef(0.25f, 0.25f, 0.5f);
    int n = (board->IsWhiteToMove()) ? 0 : 1;
    DrawText(n);
    glTranslatef(100.0f, 0.0f, 0.0f);
    switch (board->GetBoardState())
    {
      case STANDARD:                     break;
      case CHECK:           DrawText(2); break;
      case STALEMATE:       DrawText(3); break;
      case CHECKMATE_WHITE: DrawText(4); break;
      case CHECKMATE_BLACK: DrawText(5); break;
    }

  glPopMatrix();

  // HUD menu.
  for (int i = 0; i < NUM_OPTIONS; i++)
  {
    optionBoxes[i]->SetColour(selectedOption == i ? COL_GREEN(0.7f) : COL_RED(0.7f));

    // Always show top item, but only show rest of menu if menu is open.
    if (i == 0 || menuIsOpen) optionBoxes[i]->Draw();
  }

  OpenGLUtil::EndOrtho();
}

void Hud::OptionClicked()
{
  switch (selectedOption)
  {
    case -1: return;
    case 0: menuIsOpen = !menuIsOpen; break;
    // Toggle 2D board - TODO: seg fault on first try.
    case 1: board->Toggle2dMode(); menuIsOpen = false; break;
    case 2: menuIsOpen = false; break;
    // Quit to menu.
    case 3: quitGame = true; menuIsOpen = false; break;
  }
}

void Hud::MousePress(int button, int state, int x, int y)
{
  switch(button)
  {
    case GLUT_LEFT_BUTTON:
      if (state == GLUT_UP)
      {
        OptionClicked();
      }
    break;
  }
}

void Hud::MouseMotion(int x, int y)
{
  for (int i=0; i < NUM_OPTIONS; i++)
  {
    if (optionBoxes[i]->IsPointInBox(x, y))
    {
      selectedOption = i;
      return;
    }
  }

  selectedOption = -1;
}

// ## Private Methods ## //

void Hud::DrawText(int n)
{
  for (int i=0; i < (int)strlen(text[n]); i++)
  {
    glutStrokeCharacter(GLUT_STROKE_ROMAN, text[n][i]);
  }
}
