#include "model.h"

Model::Model(string id, int numVerticies, int numFaces)
{
  this->id = id;
  this->numVerticies = numVerticies;
  this->numFaces = numFaces;

  this->vertexData = new Vertex[numVerticies];
  this->faceData = new Face[numFaces];
}

Model::~Model()
{
}

void Model::PrintData()
{
  int i, j;
  cout << "Vertex data" << endl;
  for (i=0; i < numVerticies; i++)
  {
    for (j=0; j < 3; j++)
    {
      cout << vertexData[i].coord[j] << ", ";
    }
    for (j=0; j < 3; j++)
    {
      cout << vertexData[i].normal[j] << ", ";
    }
    cout << endl;
  }

  cout << "Face data" << endl;
  for (i=0; i < numFaces; i++)
  {
    for (j=0; j < faceData[i].numIndicies; j++)
    {
      cout << faceData[i].vIdxs[j] << ", ";
    }

    cout << endl;
  }
}

