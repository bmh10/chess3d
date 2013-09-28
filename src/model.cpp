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

string Model::GetId()
{
  return id;
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

void Model::DrawAt(Coord3D origin, GLfloat scale, Colour colour)
{
  //Draw all vertices for each polygon, setting texture coords and vertex normals
  int a, b;
  Vertex v;
  colour.Set();
  for (a = 0; a < numFaces; a++)
  {
    glBegin(GL_POLYGON);
    for (b = 0; b < faceData[a].numIndicies; b++)
    {
      // Lookup vertex index in polygonData, 
      // then use to get actual vertex from vertexData
      v = vertexData[faceData[a].vIdxs[b]];
      
      // Define texture coordinates of vertex
      // glTexCoord2f(v.tex_coord[0], v.tex_coord[1]);
      
      // Define normal of vertex
      glNormal3f(v.normal[0], v.normal[1], v.normal[2]);

      // Define coordinates of vertex
      glVertex3f(origin.x + v.coord[0]*scale, origin.y + v.coord[1]*scale, origin.z + v.coord[2]*scale);
    }
    glEnd();
  }
}

