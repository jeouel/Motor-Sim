#include "camera.h"
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>


Camera::Camera(glm::vec3 newPosition, glm::vec3 up, float newYaw, float newPitch):front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM), rotationSpeed(ROTATION){
        position = newPosition;
        worldUp = up;
        yaw = newYaw;
        pitch = newPitch;
        constrainPitch = true;
        updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix(){
        return glm::lookAt(position, position + front, up);
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime){
        float velocity = movementSpeed * deltaTime;
        if (direction == FORWARD) 
                position += glm::vec3(0.0f, 0.0f, -1.0f) * velocity;
        if (direction == BACKWARD) 
                position -= glm::vec3(0.0f, 0.0f, -1.0f) * velocity;
        if (direction == LEFT) 
                position -= glm::vec3(1.0f, 0.0f, 0.0f) * velocity;
        if (direction == RIGHT) 
                position += glm::vec3(1.0f, 0.0f, 0.0f) * velocity;
        if (direction == UP) 
                position += glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
        if (direction == DOWN) 
                position -= glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
        
}

void Camera::processArrows(Camera_Movement direction, float deltaTime){
        float angularVelocity = rotationSpeed * deltaTime;

        if (direction == UP)
                pitch += angularVelocity;
        if (direction == DOWN)
                pitch -= angularVelocity;
        if (direction == RIGHT)
                yaw += angularVelocity;
        if (direction == LEFT)
                yaw -= angularVelocity;
        if (constrainPitch){
                if (pitch > 89.0f)
                        pitch = 89.0f;
                if (pitch < -89.0f)
                        pitch = -89.0f;
        }
        updateCameraVectors();
}

void Camera::processMouseMovement(float xoffset, float yoffset){
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
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(front);
        right = glm::normalize(glm::cross(front, worldUp));
        up    = glm::normalize(glm::cross(right, front));
}