#ifndef _PIECE_H
#define _PIECE_H

#include "headers.h"
#include "model.h"
#include "modelManager.h"

#define PIECE_SCALE 0.005f

enum PieceType { EMPTY, PAWN, KNIGHT, BISHOP, CASTLE, QUEEN, KING };

enum PieceColour { WHITE, BLACK };

class Piece
{
  private:
    PieceType type;
    PieceColour colour;
    Model* model;

    bool selectionMode;
    GLfloat selectedColour[4];
    bool selected;

    void LoadModel(ModelManager* modelManager);
    bool Match(GLfloat a, GLfloat b);

  public:
    Piece(PieceType type);
    Piece(PieceType type, PieceColour colour, ModelManager* modelManager);
    ~Piece();
    
    void EnableSelectionMode(bool enable, int i, int j);
    bool CheckIfSelected(GLfloat* rgba);
    void Draw(int i, int j);
    

};

#endif
