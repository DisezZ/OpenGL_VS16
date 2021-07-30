#include <camera.h>

Camera::Camera(glm::vec3 cam_position, glm::vec3 world_up, float cam_pitch, float cam_yaw)
{
    position = cam_position;
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    worldUp = world_up;
    yaw = cam_yaw;
    pitch = cam_pitch;
    speed = SPEED;
    sensitivity = SENSITIIVITY;
    fov = FOV;
    updateCameraVectors();
}

Camera::~Camera()
{
}

void Camera::updateCameraVectors()
{
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getViewDir()
{
    return front;
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = speed * deltaTime;
    if (direction == CAM_FORWARD)
        position += glm::vec3(cos(glm::radians(yaw)), 0.0f, sin(glm::radians(yaw))) * velocity;
    if (direction == CAM_BACKWARD)
        position -= glm::vec3(cos(glm::radians(yaw)), 0.0f, sin(glm::radians(yaw))) * velocity;
    if (direction == CAM_LEFT)
        position -= right * velocity;
    if (direction == CAM_RIGHT)
        position += right * velocity;
    if (direction == CAM_UP)
        position += worldUp * velocity;
    if (direction == CAM_DOWN)
        position -= worldUp * velocity; 
    if (direction == CAM_SPEED_UP)
        speed = SPEED * 3;
    if (direction == CAM_SPEED_DOWN)
        speed = SPEED;
        
}

void Camera::processMouseMovement(float offsetX, float offsetY, bool constraintPitch)
{
    offsetX *= sensitivity;
    offsetY *= sensitivity;

    yaw += offsetX;   //glm::mod(yaw + offsetX, 360.0f);
    pitch -= offsetY; //glm::mod(yaw + offsetY, 360.0f);

    if (constraintPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }
    updateCameraVectors();
}

void Camera::processMouseScroll(float offsetY)
{
    fov -= (float)offsetY;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}