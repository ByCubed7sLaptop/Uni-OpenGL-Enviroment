#pragma once

#include "GameObject.h"

#include <vector>
#include <iostream>
#include <algorithm>

#include <glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Default camera attributes 
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

enum Direction {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera : public GameObject
{
public:

    // constructor with vectors
    Camera(glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f), float _yaw = YAW, float _pitch = PITCH)
        : GameObject(_position, _up, _yaw, _pitch), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
    {
        position = _position;
        worldUp = _up;
        yaw = _yaw;
        pitch = _pitch;
        CalculateVectors();
    }

    // - - Gets

    float GetMovementSpeed() { return movementSpeed; }
    float GetMouseSensitivity() { return mouseSensitivity; }
    float GetZoom() { return zoom; }

    // - - Events

    /// <summary>
    /// When a movement key is pressed
    /// </summary>
    /// <param name="direction">The local direction key that was pressed</param>
    /// <param name="deltaTime">The delta time</param>
    void OnKeyboard(Direction direction, float deltaTime)
    {
        float velocity = movementSpeed * deltaTime;
        if (direction == FORWARD) Move(front * velocity);
        if (direction == BACKWARD) Move(-front * velocity);
        if (direction == LEFT) Move(-right * velocity);
        if (direction == RIGHT) Move(right * velocity);
    }

    /// <summary>
    /// When the mouse is moved across the screen
    /// </summary>
    /// <param name="xoffset">The X offset</param>
    /// <param name="yoffset">The Y offset</param>
    /// <param name="constrainPitch">Whether to clamp the pitch</param>
    void OnMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        Rotate(glm::vec3({ xoffset, yoffset, 0 }) * mouseSensitivity);

        // Clamp pitch
        if (constrainPitch)
        {
            if (pitch > 89.0f)  pitch =  89.0f;
            if (pitch < -89.0f) pitch = -89.0f;
        }

        // Update Vectors
        CalculateVectors();
    }

    /// <summary>
    /// When the mouse is scrolled
    /// </summary>
    /// <param name="yoffset"></param>
    void OnMouseScroll(float yoffset)
    {
        zoom -= (float)yoffset;
        if (zoom < 1.0f) zoom = 1.0f;
        if (zoom > 45.0f) zoom = 45.0f;
    }

private:
    // Attributes
    float movementSpeed;
    float mouseSensitivity;
    float zoom;
};