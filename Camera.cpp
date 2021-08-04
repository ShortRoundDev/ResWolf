#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace ResWolf;


//3.672019, 0.467100, 0.250625 : -0.999312, 0.024432, 0.027911
Camera::Camera(const uint16_t width, const uint16_t height, const float fov):
    cameraPos(3.672019f, 0.467100f, 0.250625f),
    cameraFront(-0.999312f, 0.024432f, 0.027911f),  // Looking south
    cameraUp(0, 1.0f, 0),     // Orthogonal to XZ plane
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
