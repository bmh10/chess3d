#include "modelManager.h"

ModelManager::ModelManager()
{
  this->models = vector<Model*>();
}

ModelManager::~ModelManager()
{
}

void ModelManager::LoadAllModels()
{
  Logger::Info("Loading models.");
  string path = "../res/";
  LoadModel("PAWN", path + "pawn.ply");
  LoadModel("CASTLE", path + "castle.ply");
}

void ModelManager::LoadModel(string id, string path)
{  
  std::ifstream in;
  int numVerticies;
  int numFaces;
  string f;
  int i, j;
  int numIndicies;
  //int size;
  GLfloat c[3];
  Model* model;
  bool done;
  //Vertex v;
  Logger::Info("Loading model: " + path);
  in.open(path.c_str());

  if (in.fail())
  {
    Logger::Warn("Failed to open file: " + path);
    exit(0);
  }

  while (in >> f)
  {
    if (f == "element") {
      in >> f;
      if (f == "vertex")
      {
        in >> numVerticies;
        //Logger::Info("Number of verticies is: " + numVerticies);
      }
      else if (f == "face")
      {
        in >> numFaces;
        //Logger::Info("Number of faces is: " + numFaces);
      }
    }
    else if (f == "end_header")
    {
      model = new Model(id, numVerticies, numFaces);
      
      // Store vertex and normal data
      for (i=0; i < numVerticies; i++)
      {        
        in >> c[0] >> c[1] >> c[2];
        memcpy(model->vertexData[i].coord, c, 3*sizeof(GLfloat));
        in >> c[0] >> c[1] >> c[2];
        memcpy(model->vertexData[i].normal, c, 3*sizeof(GLfloat)); 
      }

      // Store face data
      for (i=0; i < numFaces; i++)
      {
        in >> numIndicies;
        model->faceData[i].numIndicies = numIndicies;
        model->faceData[i].vIdxs = new int[numIndicies];
        
        for (j=0; j < numIndicies; j++)
        {
          in >> model->faceData[i].vIdxs[j];
        }
      }

      models.push_back(model);
    }
  }

  in.close();
  //model->PrintData();
}

Model* ModelManager::GetModel(string id)
{
  for (int i = 0; i < models.size(); ++i)
  {
    if (models.at(i)->GetId() == id)
    {
      return models.at(i);
    }
  }
  // TODO: for now if model not found - return first model in list - later throw exception.
  return models.front();
}

