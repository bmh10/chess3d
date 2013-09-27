#ifndef _BOARD_H
#define _BOARD_H

#include "headers.h"
#include "piece.h"
#include "camera.h"
#include "modelManager.h"
#include "coord.h"

enum BoardState { STANDARD, CHECK, STALEMATE, CHECKMATE_WHITE, CHECKMATE_BLACK };

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
    vector<Coord> GetPossibleMoves(Coord p, int l);
    bool SafeAddMove(Coord p, Coord m, PieceColour ownColour, vector<Coord>* moves, int l);
    void SafeAddMoves(Coord p, int (*fx)(int, int), int (*fy)(int, int), PieceColour ownColour, vector<Coord>* moves, int l);
    bool SafeAddMovePawn(Coord p, Coord m, vector<Coord>* moves, int l);
    bool SafeAddMovePawnTake(Coord p, Coord m, PieceColour col, vector<Coord>* moves, int l);

    // Board analysis functions.
    bool WillMoveCauseCheck(Coord s, Coord e, int l);
    bool IsInCheck(PieceColour colourToCheck, int ls);
    bool IsLegalMove(PieceColour colour);

    // Piece* CreateBoardClone();

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
