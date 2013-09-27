#ifndef _MODEL_MANAGER_H
#define _MODEL_MANAGER_H

#include "headers.h"
#include "model.h"
#include "lodepng.h"

class ModelManager
{
  private:
    // TODO: change to array of models later.
    vector<Model*> models;
    GLuint pieces2d[6][2];
    //Model* pawnModel;

  public:
    ModelManager();
    ~ModelManager();

    void LoadAllTextures();
    void LoadAllModels();
    
    void LoadTextures();
    void LoadModel(string id, string path);
    Model* GetModel(string id);
    GLuint GetPiece2d(PieceType type, PieceColour colour);
};

#endif
