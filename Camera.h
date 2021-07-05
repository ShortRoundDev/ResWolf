#pragma once

#include "glm/glm.hpp"

namespace ResWolf
{
    class Camera
    {

    public:
        Camera(const uint16_t width, const uint16_t height, const float fov);
        ~Camera();

        void update();

        void moveTo(const glm::vec3& position);

        glm::mat4 view;
        glm::mat4 projection;
        glm::vec3 cameraPos;
        glm::vec3 cameraFront;
        glm::vec3 cameraUp;

        float fov;

        float yaw;
        float pitch;
    };
}