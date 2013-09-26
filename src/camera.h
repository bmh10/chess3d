#ifndef _CAMERA_H
#define _CAMERA_H

#include "headers.h"

#define ZOOM_MAX 0.07f
#define ZOOM_MIN -0.07f

enum CameraState { STATIONARY, ROTATING, CONTINOUS_ROTATE };

class Camera
{
  private:
    CameraState state;
    GLfloat* cameraPos;
    GLfloat cameraAngle;
    GLfloat targetAngle;
    GLfloat increment;

    void Init();
    void Zoom(bool zoomIn);

  public:
    Camera(GLfloat* cameraPos, GLfloat cameraAngle, CameraState state);
    ~Camera();

    GLfloat* GetCameraPos();
    GLfloat GetCameraAngle();

    void RotateToWhite(bool whiteToMove);
    void RotateTo(GLfloat angle);
    void Update();
    void KeyboardPress(unsigned char key);
    void MousePress(int button, int state, int x, int y);

};

#endif
