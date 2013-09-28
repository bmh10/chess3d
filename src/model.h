#ifndef _MODEL_H
#define _MODEL_H

#include "headers.h"
#include "colour.h"

// Holds data about a single vertex in the model
struct Vertex
{
  GLfloat coord[3];      //Vertex coordinates
  GLfloat tex_coord[2];  //Texture coordinates
  GLfloat normal[3];     //Average normal vector
  vector<int> polys;     //Used to prestore polygons this vertex is used in
};

// Holds data about a single polygon in the model
struct Face
{
  int     *vIdxs;        // Vertex indicies
  int     numIndicies;   // Size of vIdxs
};

class Model
{
  private:
    string id;
    int numVerticies;
    int numFaces;

  public:
    Model(string id, int numVerticies, int numFaces);
    ~Model();

    Vertex *vertexData;
    Face *faceData;

    string GetId();
    void PrintData();
    void DrawAt(GLfloat i, GLfloat j, GLfloat k, GLfloat scale, Colour colour);
};

#endif
