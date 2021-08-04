#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace ResWolf;

Camera::Camera(const uint16_t width, const uint16_t height, const float fov):
    cameraPos(0.0f, 0.0f, -3.0f),
    cameraFront(0.0f, 0.0f, 1.0f),  // Looking south
    cameraUp(0.0f, 1.0f, 0.0f),     // Orthogonal to XZ plane
    yaw(-90.f),
    pitch(0.0f),
    fov(fov),
    projection(glm::perspective(
        glm::radians(fov),
        (float)width / (float)height,
        0.1f,       // near plane
        100.0f      // far plane
    ))
{
}

Camera::~Camera()
{

}

void Camera::update()
{
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::moveTo(const glm::vec3& position)
{
    cameraPos = position;
}
