#include "camera.h"
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>


Camera::Camera(glm::vec3 newPosition, glm::vec3 up, float yaw, float pitch): front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM){
        position = newPosition;
        worldUp = up;
        yaw = yaw;
        pitch = pitch;
        updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix(){
        return glm::lookAt(position, position + front, up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime){
        float velocity = movementSpeed * deltaTime;
        if (direction == FORWARD)
                position += front * velocity;
        if (direction == BACKWARD)
                position -= front * velocity;
        if (direction == LEFT)
                position -= right * velocity;
        if (direction == RIGHT)
                position += right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true){
        xoffset *= mouseSensitivity;
        yoffset *= mouseSensitivity;

        yaw   += xoffset;
        pitch += yoffset;

        if (constrainPitch)
        {
        if (pitch > 89.0f)
                pitch = 89.0f;
        if (pitch < -89.0f)
                pitch = -89.0f;
        }

        updateCameraVectors();
}

void Camera::updateCameraVectors(){
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(front);
        right = glm::normalize(glm::cross(front, worldUp));
        up    = glm::normalize(glm::cross(right, front));
}