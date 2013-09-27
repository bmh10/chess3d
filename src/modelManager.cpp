#include "modelManager.h"

#define checkImageWidth 64
#define checkImageHeight 64
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];

ModelManager::ModelManager()
{
  this->models = vector<Model*>();
}

ModelManager::~ModelManager()
{
}

void ModelManager::LoadAllTextures()
{
  Logger::Info("Loading textures.");
  string path = "../res/";
  //LoadTexture("pieces2d", path + "pieces2d.png");
}

void ModelManager::LoadAllModels()
{
  Logger::Info("Loading models.");
  string path = "../res/";
  LoadModel("PAWN", path + "pawn.ply");
  LoadModel("CASTLE", path + "castle.ply");
}

// TESTING...
void ModelManager::LoadTextures()
{ 
  // Load file and decode image.
  vector<unsigned char> image;
  unsigned width, height;
  // TODO: switch to picoPNG?
  unsigned error = lodepng::decode(image, width, height, "../res/pieces2dtrans.png");

  // If there's an error, display it.
  if(error != 0)
  {
    std::cout << "error " << error << ": " << lodepng_error_text(error) << std::endl;
  }

  GLuint texName;

  for (int i = 0; i < 6; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      unsigned subImageWidth = width/6;
      unsigned subImageHeight = height/4;

      glPixelStorei(GL_UNPACK_ROW_LENGTH, width);
      glPixelStorei(GL_UNPACK_SKIP_PIXELS, subImageWidth*i);
      glPixelStorei(GL_UNPACK_SKIP_ROWS, subImageHeight*j);
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

      glGenTextures(1, &texName);
      glBindTexture(GL_TEXTURE_2D, texName);

      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      //cout << width << ":" << height << endl;
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, subImageWidth, 
                     subImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
                     &image[0]);

      pieces2d[i][j] = texName;
    }
  }
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
    if (f == "element")
    {
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

GLuint ModelManager::GetPiece2d(PieceType type, PieceColour colour)
{
  return pieces2d[type][colour];
  // uint col = colour = ? 0 : 1;
  // switch (type)
  // {
  //   case KING: return pieces2d[0][col];
  //   case QUEEN: return pieces2d[1][col];
  //   case CASTLE: return pieces2d[2][col];
  //   case BISHOP: return pieces2d[3][col];
  //   case KNIGHT: return pieces2d[4][col];
  //   case PAWN: return pieces2d[5][col];
  // }
  
}

