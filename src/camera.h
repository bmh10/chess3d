#ifndef _CAMERA_H
#define _CAMERA_H

#include "headers.h"
#include "coord3d.h"

#define ZOOM_MAX 0.07f
#define ZOOM_MIN -0.07f

enum CameraState { STATIONARY, ROTATING, CONTINOUS_ROTATE };

class Camera
{
  private:
    CameraState state;
    Coord3D cameraPos;
    GLfloat cameraAngle;
    Coord3D lookAtPos;

    GLfloat targetAngle;
    GLfloat increment;

    void Init();
    void Zoom(bool zoomIn);

  public:
    Camera(Coord3D cameraPos, GLfloat cameraAngle, Coord3D lookAtPos, CameraState state);
    ~Camera();

    Coord3D GetCameraPos();
    GLfloat GetCameraAngle();

    void RotateToWhite(bool whiteToMove);
    void RotateTo(GLfloat angle);
    void Update();
    void KeyboardPress(unsigned char key);
    void MousePress(int button, int state, int x, int y);

};

#endif
