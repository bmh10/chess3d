#include "openglUtil.h"

void OpenGLUtil::StartOrtho()
{
  // Save projection matrix on stack then set it up for ortho drawing.
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0.0, WINDOW_HEIGHT, 0.0, WINDOW_WIDTH, -1.0, 10.0);

  // Save model view matrix then reset it.
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  
  // Disable face culling, depth buffering and lighting for 2D drawing.
  // TODO: not sure if necessary
  glDisable(GL_CULL_FACE);
  glDisable(GL_LIGHTING);
  glClear(GL_DEPTH_BUFFER_BIT);
}

void OpenGLUtil::EndOrtho()
{
  // Restore saved matricies ready for 3D rendering.
  glEnable(GL_LIGHTING);
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
}