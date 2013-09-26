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
    //vector<unsigned char> texture;
    //Model* pawnModel;

  public:
    ModelManager();
    ~ModelManager();

    void LoadAllTextures();
    void LoadAllModels();
    
    GLuint* LoadTexture();
    void LoadModel(string id, string path);
    Model* GetModel(string id);
};

#endif
