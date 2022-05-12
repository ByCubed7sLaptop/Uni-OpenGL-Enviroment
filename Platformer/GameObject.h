#pragma once

#include <glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class GameObject
{
public:

    // Constructor
    GameObject(glm::vec3 _position = { 0.0f, 0.0f, 0.0f }, glm::vec3 _up = { 0.0f, 1.0f, 0.0f }, float _yaw = 0, float _pitch = 0)
        : position(_position), front({ 0.0f, 0.0f, -1.0f }), up(_up), yaw(_yaw), pitch(_pitch)
    {
        position = _position;
        worldUp = _up;
        yaw = _yaw;
        pitch = _pitch;
        CalculateVectors();
    }

    // - - Sets

    void Move(glm::vec3 offset) { position += offset; }
    void MoveTo(glm::vec3 newPosition) { position = newPosition; }

    void Rotate(glm::vec3 offset)
    {
        yaw += offset.x;
        pitch += offset.y;
        //roll += offset.z;
        CalculateVectors();
    }

    void RotateTo(glm::vec3 newEular) 
    {
        yaw = newEular.x;
        pitch = newEular.y;
        //roll = newEular.z;
        CalculateVectors();
    }

    // - - Gets

    /// <summary>
    /// Calculate the Veiw matrix using lookat.
    /// </summary>
    /// <returns>the view matrix calculated using Euler Angles and the LookAt Matrix</returns>
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(position, position + front, up);
    }

    glm::vec3 GetPosition() { return position; }
    glm::vec3 GetFront()    { return front; }
    glm::vec3 GetUp()       { return up; }
    glm::vec3 GetRight()    { return right; }


protected:
    // Attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    // Euler rotation
    float yaw;
    float pitch;
    //float roll;
    
    /// <summary>
    /// Recalculates the front, right and up vector.
    /// </summary>
    void CalculateVectors() {
        // Front vector
        glm::vec3 newFront;
        newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        newFront.y = sin(glm::radians(pitch));
        newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(newFront);

        // Right and Up using the cross of Front
        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
    }
};

