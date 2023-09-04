#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

class Camera {
public:
    Camera(glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 up = glm::vec3(0.0, 1.0, 0.0), float yaw = YAW, float pitch = PITCH) :
        _front(glm::vec3(0, 0, -1)), _movementSpeed(SPEED), _mouseSensitivity(SENSITIVITY), _zoom(ZOOM)
    {
        _position = position;
        _worldUp = up;
        _yaw = yaw;
        _pitch = pitch;
        UpdateCameraVectors();
    }

    glm::mat4 GetViewMatrix() {
        return glm::lookAt(_position, _position + _front, _up);
    }

    float GetZoom() const {
        return _zoom;
    }

    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = _movementSpeed * deltaTime;
        if (direction == FORWARD)
            _position += _front * velocity;
        if (direction == BACKWARD)
            _position -= _front * velocity;
        if (direction == LEFT)
            _position -= _right * velocity;
        if (direction == RIGHT)
            _position += _right * velocity;
    }

    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
    {
        xoffset *= _mouseSensitivity;
        yoffset *= _mouseSensitivity;

        _yaw += xoffset;
        _pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (_pitch > 89.0f)
                _pitch = 89.0f;
            else if (_pitch < -89.0f)
                _pitch = -89.0f;
        }

        UpdateCameraVectors();
    }

    void ProcessMouseScroll(float yoffset)
    {
        _zoom -= (float)yoffset;
        if (_zoom < 1.0f)
            _zoom = 1.0f;
        else if (_zoom > 45.0f)
            _zoom = 45.0f;
    }


private:
    void UpdateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 newFront;
        newFront.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
        newFront.y = sin(glm::radians(_pitch));
        newFront.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
        _front = glm::normalize(newFront);
        // also re-calculate the Right and Up vector
        _right = glm::normalize(glm::cross(_front, _worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        _up    = glm::normalize(glm::cross(_right, _front));
    }

    glm::vec3 _position;
    glm::vec3 _front;
    glm::vec3 _up;
    glm::vec3 _right;
    glm::vec3 _worldUp;
    // euler Angles
    float _yaw;
    float _pitch;
    // camera options
    float _movementSpeed;
    float _mouseSensitivity;
    float _zoom;
};