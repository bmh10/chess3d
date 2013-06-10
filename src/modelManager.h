#ifndef _MODEL_MANAGER_H
#define _MODEL_MANAGER_H

#include "headers.h"
#include "model.h"

class ModelManager
{
  private:
    // TODO: change to array of models later.
    Model* pawnModel;

  public:
    ModelManager();
    ~ModelManager();

    void LoadAllModels();
    Model* GetModel(string id);
};

#endif
