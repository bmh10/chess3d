#ifndef _PIECE_H
#define _PIECE_H

#include "headers.h"
#include "model.h"
#include "modelManager.h"
#include "box2d.h"

#define PIECE_SCALE 0.005f

enum PieceState { NORMAL, HIGHLIGHTED, SELECTED };

class Piece
{
  private:
    PieceType type;
    PieceColour colour;
    PieceState state;
    Model* model;

    GLuint tex2dName;
    Box2d* box;

    bool selectionMode;
    Colour selectedColour;
    bool hasMoved;

    void LoadModelAnd2dTexture(ModelManager* modelManager);
    bool Match(GLfloat a, GLfloat b);

  public:
    Piece(PieceType type);
    Piece(PieceType type, PieceColour colour, ModelManager* modelManager);
    ~Piece();

    PieceType GetType();
    PieceColour GetColour();
    PieceState GetState();
    
    void SetHasMoved();
    bool HasMoved();

    void SetSelected(bool selected);
    void SetHighlighted(bool highlight);
    void EnableSelectionMode(bool enable, int i, int j);
    bool CheckIfClicked(int x, int y, Colour clickedColour, bool in2D);
    void Draw(int i, int j);
    void Draw2D(int i, int j);
};

#endif
