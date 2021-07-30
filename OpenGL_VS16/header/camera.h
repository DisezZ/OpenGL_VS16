#ifndef CAMERA_H
#define CAMERA_H

#include <glx.h>
#include <util.h>

// possible camera type
enum Camera_Type {
  CAM_FLY,
  CAM_FPS,
};

// possible camera movement
enum Camera_Movement {
  CAM_FORWARD,
  CAM_BACKWARD,
  CAM_LEFT,
  CAM_RIGHT,
  CAM_UP,
  CAM_DOWN,
  CAM_SPEED_UP,
  CAM_SPEED_DOWN
};

// default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIIVITY = 0.1f;
const float FOV = 45.0f;

class Camera
{
private:
  void updateCameraVectors();

public:
  glm::vec3 position;
  glm::vec3 front;
  glm::vec3 up;
  glm::vec3 right;
  glm::vec3 worldUp;
  float yaw;
  float pitch;
  float speed;
  float sensitivity;
  float fov;
  Camera(glm::vec3 cam_position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 cam_up = glm::vec3(0.0f, 1.0f, 0.0f), float pitch = PITCH, float yaw = YAW);
  ~Camera();
  glm::mat4 getViewMatrix();
  glm::vec3 getViewDir();
  void processKeyboard(Camera_Movement direction, float deltaTime);
  void processMouseMovement(float offsetX, float offsetY, bool constraintPitch = true);
  void processMouseScroll(float offsetY);
};

#endif