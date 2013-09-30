#ifndef _BOARD_H
#define _BOARD_H

#include "headers.h"
#include "piece.h"
#include "camera.h"
#include "modelManager.h"
#include "coord2d.h"

enum BoardState { STANDARD, CHECK, STALEMATE, CHECKMATE_WHITE, CHECKMATE_BLACK };

class Board
{
  private:
    Piece* pieces[8][8];
    ModelManager* modelManager;
    Camera* camera;
    Piece* selectedPiece;
    Coord2D selCoord;
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

    // TODO: Move these functions to chess AI class.
    vector<Coord2D> GetPossibleMoves(Coord2D p, int l);
    bool SafeAddMove(Coord2D p, Coord2D m, PieceColour ownColour, vector<Coord2D>* moves, int l);
    void SafeAddMoves(Coord2D p, int (*fx)(int, int), int (*fy)(int, int), PieceColour ownColour, vector<Coord2D>* moves, int l);
    bool SafeAddMovePawn(Coord2D p, Coord2D m, vector<Coord2D>* moves, int l);
    bool SafeAddMovePawnTake(Coord2D p, Coord2D m, PieceColour col, vector<Coord2D>* moves, int l);

    // Board analysis functions.
    bool WillMoveCauseCheck(Coord2D s, Coord2D e, int l);
    bool IsInCheck(PieceColour colourToCheck, int ls);
    bool IsLegalMove(PieceColour colour);

    // Piece* CreateBoardClone();

  public:
    Board();
    Board(Camera* camera);
    ~Board();

    void Draw();
    void SelectSquareAt(int x, int y);
    
    bool IsWhiteToMove();
    BoardState GetBoardState();
    void Toggle2dMode();
};

#endif
