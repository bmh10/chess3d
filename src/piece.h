#ifndef _PIECE_H
#define _PIECE_H

#include "headers.h"
#include "model.h"
#include "modelManager.h"

#define PIECE_SCALE 0.005f

enum PieceType { EMPTY, PAWN, KNIGHT, BISHOP, CASTLE, QUEEN, KING };

enum PieceColour { WHITE, BLACK };

enum PieceState { NORMAL, HIGHLIGHTED, SELECTED };

class Piece
{
  private:
    PieceType type;
    PieceColour colour;
    PieceState state;
    Model* model;

    bool selectionMode;
    GLfloat selectedColour[4];

    void LoadModel(ModelManager* modelManager);
    bool Match(GLfloat a, GLfloat b);

  public:
    Piece(PieceType type);
    Piece(PieceType type, PieceColour colour, ModelManager* modelManager);
    ~Piece();

    PieceType GetType();
    PieceColour GetColour();
    PieceState GetState();
    
    void SetSelected(bool selected);
    void SetHighlighted(bool highlight);
    void EnableSelectionMode(bool enable, int i, int j);
    bool CheckIfClicked(GLfloat* rgba);
    void Draw(int i, int j);
    

};

#endif
