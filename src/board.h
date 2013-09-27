#ifndef _BOARD_H
#define _BOARD_H

#include "headers.h"
#include "piece.h"
#include "camera.h"
#include "modelManager.h"
#include "coord.h"

enum BoardState { STANDARD, CHECK_WHITE, CHECK_BLACK, STALEMATE, CHECKMATE };

class Board
{
  private:
    Piece* pieces[8][8];
    ModelManager* modelManager;
    Camera* camera;
    Piece* selectedPiece;
    int selCoord[2];
    // Put these in struct so HUD can have easy access.
    bool whiteToMove;
    bool show2dBoard;
    BoardState boardState;
    //

    void Init();
    void EnableSelectionMode(bool enable);
    void SetSelectedPiece(int i, int j);
    void MoveSelectedPiece(int i, int j);
    int Apply(int i, int j, std::binary_function<int, int, int> f);
    void UnhighlightPieces();

    void HighlightPossibleMoves();
    vector<Coord> GetPossibleMoves(Coord p);
    bool SafeAddMove(Coord m, PieceColour ownColour, vector<Coord>* moves);
    void SafeAddMoves(Coord start, int (*fx)(int, int), int (*fy)(int, int), PieceColour ownColour, vector<Coord>* moves);
    bool SafeAddMovePawn(Coord m, vector<Coord>* moves);
    bool SafeAddMovePawnTake(Coord m, PieceColour col, vector<Coord>* moves);

  public:
    Board(Camera* camera);
    ~Board();

    void Draw();
    void SelectSquareAt(int x, int y);
    
    bool IsWhiteToMove();
    BoardState GetBoardState();
    void Toggle2dMode();
};

#endif
