#include "camera.h"

Camera::Camera() {}

Camera::Camera(Coord3D cameraPos, GLfloat cameraAngle, Coord3D lookAtPos, CameraState state)
{
  this->cameraPos = cameraPos;
  this->cameraAngle = cameraAngle;
  this->lookAtPos = lookAtPos;
  this->state = state;
}

Camera::~Camera()
{
}

void Camera::Init()
{
}

Coord3D Camera::GetCameraPos()
{
  return cameraPos;
}

GLfloat Camera::GetCameraAngle()
{
  return cameraAngle;
}

void Camera::RotateToWhite(bool whiteToMove)
{
  if (whiteToMove)
    RotateTo(0.0);
  else
    RotateTo(180.0);
}

void Camera::RotateTo(GLfloat angle)
{
  state = ROTATING;
  targetAngle = angle;
  GLfloat dir = targetAngle - cameraAngle;

  if (dir > 0 ^ abs(dir) > 180) increment = 5.0f;
  else increment = -5.0;
}

void Camera::Update()
{
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z,
    lookAtPos.x, lookAtPos.y, lookAtPos.z, 0.0f, 0.0f, 1.0f);

  if (state == CONTINOUS_ROTATE)
  {
    cameraAngle += 0.25f;
  }
  else if (state == ROTATING)
  {
    // TODO: make it rotate shortest distance rather than same way all the time.
    cameraAngle += increment;
    GLfloat diff = abs(abs(cameraAngle) - targetAngle);
    if (diff <= 5.0)
    {
      cameraAngle = targetAngle;
      state = STATIONARY;
    }
  }

  if (cameraAngle >= 360.0f || cameraAngle <= -360.0f)
  {
    cameraAngle = 0.0f;  
  }

  glTranslatef(lookAtPos.x, lookAtPos.y, lookAtPos.z);
  glRotatef(cameraAngle, 0.0f, 0.0f, 1.0f);
  glTranslatef(-lookAtPos.x, -lookAtPos.y, -lookAtPos.z);
}

void Camera::KeyboardPress(unsigned char key)
{
    // Left/right to rotate camera.
  if (key == 'a') cameraAngle += 2.5f;
  else if (key == 'd') cameraAngle -= 2.5f;

  // Up/down to zoom in or out.
  if (key == 'w') Zoom(true);
  else if (key == 's') Zoom(false);

/*
  if (key == 'q') cameraPos[0] += 0.01;
  else if (key == 'a') cameraPos[0] -= 0.01;
  else if (key == 'w') cameraPos[1] += 0.01;
  else if (key == 's') cameraPos[1] -= 0.01;
  else if (key == 'e') cameraPos[2] += 0.01;
  else if (key == 'd') cameraPos[2] -= 0.01;
  
  else if (key == 'u') lightPos[0] += 0.01;
  else if (key == 'j') lightPos[0] -= 0.01;
  else if (key == 'i') lightPos[1] += 0.01;
  else if (key == 'k') lightPos[1] -= 0.01;
  else if (key == 'o') lightPos[2] += 0.01;
  else if (key == 'l') lightPos[2] -= 0.01;
*/
}

void Camera::MousePress(int button, int state, int x, int y)
{
  // Use scroll wheel to zoom in or out.
  if (button == 3) Zoom(true);
  else if (button == 4) Zoom(false);
}

void Camera::Zoom(bool zoomIn)
{
  if (zoomIn && cameraPos.y < ZOOM_MAX)
  {
    cameraPos.y += 0.01f;
  }
  else if (!zoomIn && cameraPos.y > ZOOM_MIN)
  {
    cameraPos.y -= 0.01f; 
  }
}
