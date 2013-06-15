#ifndef _BOARD_H
#define _BOARD_H

#include "headers.h"
#include "piece.h"
#include "modelManager.h"
#include <functional>

class Board
{
  private:
    Piece* pieces[8][8];
    ModelManager* modelManager;
    Piece* selectedPiece;
    int selCoord[2];

    void Init();
    void EnableSelectionMode(bool enable);
    void SetSelectedPiece(int i, int j);
    bool SafeHighlightPiece(int i, int j);
    //template<class Fx, class Fy> int SafeHighlightPieces(int i, int j, Fx fx, Fx fy);
    //void SafeHighlightPieces(int i, int j, std::binary_function<int, int, int> fx,
                                           //std::binary_function<int, int, int> fy);
    int Apply(int i, int j, std::binary_function<int, int, int> f);
    void UnhighlightPieces();

    template<class Fx, class Fy> int SafeHighlightPieces(int i, int j, Fx fx, Fx fy)
	{
	  int n = 0;
	  for (n=0; n < 8; n++)
	  {
		if (!SafeHighlightPiece(fx(i, n), fy(j, n)))
          break;
	  }

	}

  public:
    Board();
    ~Board();

    //void Update();
    void Draw();
    void SelectSquareAt(int x, int y);
    void DisplayPossibleMoves();
   
};

#endif
