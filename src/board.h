#ifndef _BOARD_H
#define _BOARD_H

#include "headers.h"
#include "piece.h"
#include "modelManager.h"

class Board
{
  private:
    Piece* pieces[8][8];
    ModelManager* modelManager;
    Piece* selectedPiece;
    int selCoord[2];
    bool whiteToMove;

    void Init();
    void EnableSelectionMode(bool enable);
    void SetSelectedPiece(int i, int j);
    void MoveSelectedPiece(int i, int j);
    bool SafeHighlightPiece(int i, int j);
    void SafeHighlightPieces(int i, int j, int (*fx)(int, int), int (*fy)(int, int));
    bool SafeHighlightPiecePawn(int i, int j);
    bool SafeHighlightPiecePawnTake(int i, int j, PieceColour col);
    int Apply(int i, int j, std::binary_function<int, int, int> f);
    void UnhighlightPieces();

  public:
    Board();
    ~Board();

    //void Update();
    void Draw();
    void SelectSquareAt(int x, int y);
    void DisplayPossibleMoves();

    bool IsWhiteToMove();
   
};

#endif
