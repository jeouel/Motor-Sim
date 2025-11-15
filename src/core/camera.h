#pragma once
#include <glm/glm.hpp>


enum Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
};

const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;


class Camera
{
public:
    
        Camera(glm::vec3 newPosition = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

        glm::mat4 GetViewMatrix();
        void ProcessKeyboard(Camera_Movement direction, float deltaTime);
        void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch);

private:

        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 worldUp;

        float yaw;
        float pitch;

        float movementSpeed;
        float mouseSensitivity;
        float zoom;

        void updateCameraVectors();
};
