// #include "cgRender.h"

// /*
//  * Graphics coursework - Rendering using OpenGL (bmh10)
//  */

// #define VTK_FILE "../data/face.vtk"
// #define PPM_FILE "../data/face.ppm"
// #define DEBUG 0

// // Holds data about a single vertex in the model
// struct Vertex
// {
//   GLfloat coord[3];      //Vertex coordinates
//   GLfloat tex_coord[2];  //Texture coordinates
//   GLfloat normal[3];     //Average normal vector
//   vector<int> polys;     //Used to prestore polygons this vertex is used in
// };

// // Holds data about a single polygon in the model
// struct Triangle
// {
//   int     *vIdxs;        // Vertex indicies
//   int     numIndicies;   // Size of vIdxs
// };

// int VERTEX_DATA_SIZE;
// int POLYGON_DATA_SIZE;
// Vertex *vertexData;
// Triangle *polygonData;

// float avgVertex[3];
// GLfloat cameraPos[3];
// GLfloat lightPos[3] = {0.36, -0.1448, -0.010616};

// GLuint texture;
// bool textureOn = true;

// /*
//  * Loads verticies, polygon data and texture data from VTK file
//  */
// void loadModelData()
// {
//   std::ifstream in;
//   string f;
//   int num;
//   int size;
//   GLfloat c[3];
//   Vertex v;
//   in.open(VTK_FILE);
//   cout << "loadModelData()" << endl;
//   if (in.fail())
//   {
//     cout << "Failed to open file." << endl;
//     exit(0);
//   }

//   while (in >> f)
//   {

//     if (f == "POINTS") {
//       in >> VERTEX_DATA_SIZE;
//       vertexData = new Vertex[VERTEX_DATA_SIZE];
//       cout << "Storing vertex data: size " << VERTEX_DATA_SIZE << endl;
//       in >> f;
//       for (int i=0; i < VERTEX_DATA_SIZE; i++)
//       {        
//         in >> c[0] >> c[1] >> c[2];
//         memcpy(vertexData[i].coord, c, 3*sizeof(GLfloat)); 
//       }
//     }
//     else if (f == "POLYGONS")
//     {
//       in >> POLYGON_DATA_SIZE;
//       polygonData = new Triangle[POLYGON_DATA_SIZE];
//       cout << "Storing polygon data: size " << POLYGON_DATA_SIZE << endl;
//       in >> f; // Skip second number
//       for (int i=0; i < POLYGON_DATA_SIZE; i++)
//       {
//         // Do not assume there are always 3 points per polygon
//         in >> num;
//         polygonData[i].numIndicies = num;
//         polygonData[i].vIdxs = new int[num];
        
//         // Store in each vertex the polgons it is used in to speed up
//         // calculation of average (per vertex) normals later
//         for (int j=0; j < num; j++)
//         {
//           in >> polygonData[i].vIdxs[j];
//           vertexData[polygonData[i].vIdxs[j]].polys.push_back(i);
//         }
//       }
//     }
//     else if (f == "POINT_DATA")
//     {
//        cout << "Storing texture data" << endl;
//       in >> size;
//       if (size != VERTEX_DATA_SIZE)
//       {
//         cout << "ERROR: texture data size to equals to vertex data size." << endl;
//       }
     
//       // Skip redundant data
//       in >> f; in >> f; in >> f; in >> f;
//       for (int i=0; i < VERTEX_DATA_SIZE; i++)
//       {
//         in >> c[0] >> c[1];
//         memcpy(vertexData[i].tex_coord, c, 2*sizeof(GLfloat)); 
//       }
//     }
//   }
// }

// /*
//  * Loads texture from PPM file and creates mipmap to use with model
//  */
// GLuint texture_load(const char *filename)
// {
//     cout << "Loading texture file" << endl;
     
//     GLuint texture;
//     int width, height;
//     unsigned char *data;
//     char *header;
//     FILE * file;

//     // Read in PPM file
//     file = fopen(filename, "rb");
//     if (file == NULL) {
//       cout << "Could not open file " << filename << endl;
//       return 0;
//     }
   
//     // Get texture dimensions from PPM header
//     header = (char *) malloc(15);
//     fread(header, 15, 1, file);
//     char *split = strtok(header, " \n");
//     int n = 0;
//     while (split != NULL)
//     {
//       if (n==1) width = atoi(split);
//       else if (n==2) height = atoi(split);
//       split = strtok (NULL, " \n");
//       n++;	
//     }
    
//     // Buffer with rgb for each pixel in texture
//     data = (unsigned char *) malloc(width*height*3);
//     // Ensure we start reading from after header 
//     fseek (file, 15, SEEK_SET);
//     fread(data, width * height * 3, 1, file);
//     fclose(file);
     
//      // Allocate texture name
//      glGenTextures(1, &texture);
 
//      // Set current texture
//      glBindTexture(GL_TEXTURE_2D, texture);
 
//      // Select modulate to mix texture with color for shading
//      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
 
//      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
//      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);
 
//      // When texture area is small, bilinear filter the closest mipmap
//      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
//      // When texture area is large, bilinear filter the first mipmap
//      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 
//      // Texture should tile
//      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
 
//      // Build our texture mipmap
//      gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
 
//      delete(data);
//      return texture;
// }

// /*
//  * Adds together the vectors v0 and v1 and gives ret as result
//  */
// void add(GLfloat *ret, GLfloat *v0, GLfloat *v1)
// {
//   for (int i=0; i < 3; i++)
//     ret[i] = v0[i] + v1[i];
// }

// /*
//  * Subtracts v1 from v0 and gives ret as result
//  */
// void sub(GLfloat* ret, GLfloat *v0, GLfloat *v1)
// {
//   for (int i=0; i < 3; i++)
//     ret[i] = v0[i] - v1[i];
// }

// /*
//  * Divides vector v0 by a constant d
//  */
// void divide(GLfloat *v0, GLfloat d)
// {
//   if (d==0) return;
//   for (int i=0; i < 3; i++)
//     v0[i] = v0[i] / d;
// }

// /*
//  * Normalises the vector v0
//  */
// void normalise(GLfloat *v0)
// {
//   GLfloat magnitude = sqrt(pow(v0[0], 2) + pow(v0[1], 2) + pow(v0[2], 2));
//   divide(v0, magnitude);
// }

// /*
//  * Calculataes cross product of vectors v0 and v1 and gives ret as result
//  */
// void cross(GLfloat *ret, GLfloat *v0, GLfloat *v1)
// {
//   ret[0] = v0[1]*v1[2] - v0[2]*v1[1];
//   ret[1] = v0[2]*v1[0] - v0[0]*v1[2];
//   ret[2] = v0[0]*v1[1] - v0[1]*v1[0];
// }

// /*
//  * Calculates per polygon normals and then uses these to calculate
//  * average per vertex normals
//  */
// void calculateAverageNormals()
// {
//   cout << "Calculating average normals" << endl;
//   Triangle t;
//   Vertex vs[3];
//   GLfloat *u = new GLfloat[3];
//   GLfloat *v = new GLfloat[3];
//   GLfloat *normal = new GLfloat[3];
//   GLfloat *sum;
//   int max, pIdx, idx, i;

//   // Find how many polygons a vertex belongs to and sum all the polygon normals   
//   // each vertex belongs to, then calculate average normal of each vertex
 
//   for (idx=0; idx < VERTEX_DATA_SIZE; idx++)
//   {
//     sum = new GLfloat[3];
//     max = vertexData[idx].polys.size();
    
//     // Already prestored which polygons each vertex belongs to, so simply iterate 
//     // through polygons summing normals. Number of polygons = size of array
//     for (i=0; i < max; i++)
//     {
//       pIdx = vertexData[idx].polys[i];
//       // Get polygon this vertex is used in
//       t = polygonData[pIdx];
//       for (int j=0; j < 3; j++)
//       {
//         vs[j] = vertexData[t.vIdxs[j]];
//       }

//       // Calculate polygon's normal and normalise
//       sub(u, vs[0].coord, vs[1].coord);
//       sub(v, vs[0].coord, vs[2].coord);
//       cross(normal, u, v);
//       normalise(normal);
      
//       // Keep track of sum of all relevent polygon normals
//       add(sum, sum, normal);
//     }
//     // Divide sum of polygon normals by number
//     // of polygons to get avg normal for vertex
//     divide(sum, max);
//     normalise(sum);
//     memcpy(vertexData[idx].normal, sum, sizeof(GLfloat)*3);
//     delete(sum);
//   }
  
//   //Free memory
//   delete(u);
//   delete(v);
//   delete(normal);
// }

// /*
//  * Calculates near central point of model by averaging all of vertices
//  */
// void calculateCenterPoint()
// {
//   float sum[3];
//   int i, j;
//   for (i=0; i < VERTEX_DATA_SIZE; i++)
//   {
//     for (j=0; j < 3; j++)
//     {
//       sum[j] += vertexData[i].coord[j];
//     }
//   }
  
//   for (i=0; i < 3; i++)
//   {
//     sum[i] /= VERTEX_DATA_SIZE;
//   }
//   memcpy(avgVertex, sum, sizeof(GLfloat)*3);
// }

// void init() 
// {
//   glClearColor (0.0, 0.0, 0.0, 0.0);
//   cout << "init" << endl;
  
//   // Load model data, calculate normals and load texture
//   loadModelData();
//   calculateAverageNormals();
//   calculateCenterPoint();
//   texture = texture_load(PPM_FILE);

//   glShadeModel (GL_SMOOTH);
//   GLfloat LightAmbient[] = {0.0, 0.0, 0.0, 1.0};
//   GLfloat LightDiffuse[] = {1.0, 1.0, 1.0, 1.0};
//   GLfloat LightSpecular[] = {1.0, 1.0, 1.0, 0.1};
//   GLfloat MaterialSpecular[] = {0.1, 0.1, 0.1, 1.0};
//   GLfloat MaterialShininess[] = {128};
  
//   // Enable lighting
//   glEnable (GL_LIGHTING);
//   glEnable (GL_LIGHT0);
//   glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
//   glLightfv(GL_LIGHT0, GL_AMBIENT,  LightAmbient);
//   glLightfv(GL_LIGHT0, GL_DIFFUSE,  LightDiffuse);
//   glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
  
//   // Set material parameters
//   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  MaterialSpecular);
//   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, MaterialShininess);
  
//   //glEnable(GL_COLOR_MATERIAL);
//   //glColorMaterial(GL_FRONT,GL_DIFFUSE);
  
//   // Enable Z-buffering
//   glEnable(GL_DEPTH_TEST);
  
//   // Cull back faces of polygons
//   glEnable(GL_CULL_FACE);
//   glCullFace(GL_BACK);
  
//   // Set initial camera position relative to centre point of model
//   for (int i=0; i < 3; i++)
//     cameraPos[i] = avgVertex[i];
//   cameraPos[0] += 0.025;
//   cameraPos[2] -= 0.1;
// }

// void display(void)
// {
//   //Clear colour and depth buffers
//   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//   Vertex v;
  
//   if (DEBUG)
//   {
//     // Draw triangle at light source
//     glBegin(GL_TRIANGLES);
//     glColor3f(1.0, 0.0, 0.0);
//     glVertex3f(lightPos[0], lightPos[1], lightPos[2]);
//     glVertex3f(lightPos[0], lightPos[1]+0.1, lightPos[2]);
//     glVertex3f(lightPos[0], lightPos[1]+0.1, lightPos[2]+0.1);
//     glEnd();
//   }
  
//   if (textureOn)
//     glEnable(GL_TEXTURE_2D);
//   else
//     glDisable(GL_TEXTURE_2D);
  
//   //Draw all vertices for each polygon, setting texture coords and vertex normals
//   for (int i=0; i < POLYGON_DATA_SIZE; i++)
//   {
//     glBegin(GL_POLYGON);
//     for (int j=0; j < polygonData[i].numIndicies; j++)
//     {
//       // Lookup vertex index in polygonData, 
//       // then use to get actual vertex from vertexData
//       v = vertexData[polygonData[i].vIdxs[j]];
      
//       // Define texture coordinates of vertex
//       glTexCoord2f(v.tex_coord[0], v.tex_coord[1]);
      
//       // Define normal of vertex
//       glNormal3f(v.normal[0], v.normal[1], v.normal[2]);

//       // Define coordinates of vertex
//       glVertex3f(v.coord[0], v.coord[1], v.coord[2]);
//     }
//     glEnd();
//    }
//   glutSwapBuffers();
// }

// void reshape (int w, int h)
// {
//   cout << "reshape" << endl;
//   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  
//   // Setup perspective
//   glMatrixMode (GL_PROJECTION);
//   glLoadIdentity();
//   gluPerspective (90, (GLfloat)w / (GLfloat)h, 0.01, 10.0);
// }

// void update()
// {
//   // Move light depending on current coords
//   glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

//   // Move camera depending on current coords
//   glMatrixMode (GL_MODELVIEW);
//   glLoadIdentity();
//   gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2],
//     avgVertex[0], avgVertex[1], avgVertex[2], 0.0f, 1.0f,  0.0f);
//   display();
// }

// /*
//  * Allows user to move camera and light positions using keyboard
//  */
// void keyboard(unsigned char key, int x, int y)
// {
//   switch (key) {
//   case 27: // ESC
//     exit(0);
//     break;
//   }

//   if (key == 'q') cameraPos[0] += 0.01;
//   else if (key == 'a') cameraPos[0] -= 0.01;
//   else if (key == 'w') cameraPos[1] += 0.01;
//   else if (key == 's') cameraPos[1] -= 0.01;
//   else if (key == 'e') cameraPos[2] += 0.01;
//   else if (key == 'd') cameraPos[2] -= 0.01;
  
//   else if (key == 'u') lightPos[0] += 0.01;
//   else if (key == 'j') lightPos[0] -= 0.01;
//   else if (key == 'i') lightPos[1] += 0.01;
//   else if (key == 'k') lightPos[1] -= 0.01;
//   else if (key == 'o') lightPos[2] += 0.01;
//   else if (key == 'l') lightPos[2] -= 0.01;
  
//   else if (key == 't') textureOn = !textureOn;
// }

// int main(int argc, char** argv)
// {
//   // Initialize graphics window
//   glutInit(&argc, argv);
//   // Use double buffering and depth testing
//   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 

//   glutInitWindowSize (512, 512); 
//   glutInitWindowPosition (0, 0);
//   glutCreateWindow ("Graphics coursework - OpenGL");

//   // Initialize OpenGL
//   init();

//   // Initialize callback functions
//   glutDisplayFunc(display);
//   glutIdleFunc(update); 
//   glutReshapeFunc(reshape);
//   glutKeyboardFunc(keyboard);

//   // Start rendering 
//   glutMainLoop();
// }
