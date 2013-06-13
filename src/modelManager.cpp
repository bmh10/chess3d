#include "modelManager.h"

ModelManager::ModelManager()
{
}

ModelManager::~ModelManager()
{
}

void ModelManager::LoadAllModels()
{
  // TODO: For now just loads dummy pawn model.
  Logger::Info("Loading models.");
  std::ifstream in;
  int numVerticies;
  int numFaces;
  string f;
  int i, j;
  int numIndicies;
  //int size;
  GLfloat c[3];
  //Vertex v;
  in.open("../res/pawn.ply");

  if (in.fail())
  {
    cout << "Failed to open file." << endl;
    exit(0);
  }

  while (in >> f)
  {
    if (f == "element") {
      in >> f;
      if (f == "vertex")
      {
        in >> numVerticies;
        // cout << "Number of verticies is: " << numVerticies << endl;
      }
      else if (f == "face")
      {
        in >> numFaces;
        // cout << "Number of faces is: " << numFaces << endl;
      }
    }
    else if (f == "end_header")
    {
      pawnModel = new Model("PAWN", numVerticies, numFaces);
      
      // Store vertex and normal data
      for (i=0; i < numVerticies; i++)
      {        
        in >> c[0] >> c[1] >> c[2];
        memcpy(pawnModel->vertexData[i].coord, c, 3*sizeof(GLfloat));
        in >> c[0] >> c[1] >> c[2];
        memcpy(pawnModel->vertexData[i].normal, c, 3*sizeof(GLfloat)); 
      }

      // Store face data
      for (i=0; i < numFaces; i++)
      {
        in >> numIndicies;
        pawnModel->faceData[i].numIndicies = numIndicies;
        pawnModel->faceData[i].vIdxs = new int[numIndicies];
        
        for (j=0; j < numIndicies; j++)
        {
          in >> pawnModel->faceData[i].vIdxs[j];
        }
      }

      //pawnModel->PrintData();
    }
    
      /*vertexData = new Vertex[VERTEX_DATA_SIZE];
      cout << "Storing vertex data: size " << VERTEX_DATA_SIZE << endl;
      in >> f;
      for (int i=0; i < VERTEX_DATA_SIZE; i++)
      {        
        in >> c[0] >> c[1] >> c[2];
        memcpy(vertexData[i].coord, c, 3*sizeof(GLfloat)); 
      }*/
    
    /*
    else if (f == "POLYGONS")
    {
      in >> POLYGON_DATA_SIZE;
      polygonData = new Triangle[POLYGON_DATA_SIZE];
      cout << "Storing polygon data: size " << POLYGON_DATA_SIZE << endl;
      in >> f; // Skip second number
      for (int i=0; i < POLYGON_DATA_SIZE; i++)
      {
        // Do not assume there are always 3 points per polygon
        in >> num;
        polygonData[i].numIndicies = num;
        polygonData[i].vIdxs = new int[num];
        
        // Store in each vertex the polgons it is used in to speed up
        // calculation of average (per vertex) normals later
        for (int j=0; j < num; j++)
        {
          in >> polygonData[i].vIdxs[j];
          vertexData[polygonData[i].vIdxs[j]].polys.push_back(i);
        }
      }
    }
    else if (f == "POINT_DATA")
    {
       cout << "Storing texture data" << endl;
      in >> size;
      if (size != VERTEX_DATA_SIZE)
      {
        cout << "ERROR: texture data size to equals to vertex data size." << endl;
      }
     
      // Skip redundant data
      in >> f; in >> f; in >> f; in >> f;
      for (int i=0; i < VERTEX_DATA_SIZE; i++)
      {
        in >> c[0] >> c[1];
        memcpy(vertexData[i].tex_coord, c, 2*sizeof(GLfloat)); 
      }*/
  }
}

//TODO: for now just returns pawn model - will act as lookup for loaded models.
Model* ModelManager::GetModel(string id)
{
  return pawnModel;
}

