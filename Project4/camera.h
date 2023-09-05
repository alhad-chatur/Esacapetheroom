#pragma once
#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include<iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>


enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};


const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 3.0f;
const float SENSITIVITY = 0.2f;
const float ZOOM = 45.0f;

using namespace std;
// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 mouseFront;
    glm::vec3 keyfront;
    glm::vec3 Up;
    glm::vec3 mouseRight;
    glm::vec3 keyright;
    glm::vec3 WorldUp;
    glm::vec3 keyUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed = SPEED;
    float MouseSensitivity =SENSITIVITY;
    float Zoom = ZOOM;

    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : mouseFront(glm::vec3(0.0f, 0.0f, -1.0f))
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : mouseFront(glm::vec3(0.0f, 0.0f, -1.0f))
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + mouseFront, Up);
    }

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += keyfront * velocity;
        if (direction == BACKWARD)
            Position -= keyfront * velocity;
        if (direction == LEFT)
            Position -= keyright * velocity;
        if (direction == RIGHT)
            Position += keyright * velocity;
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }
private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        glm::vec3 frt;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        mouseFront = glm::normalize(front);
        // also re-calculate the Right and Up vector
        mouseRight = glm::normalize(glm::cross(mouseFront, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(mouseRight, mouseFront));

        frt.x = cos(glm::radians(Yaw));
        frt.z = sin(glm::radians(Yaw));
        frt.y = 0;

        keyfront = glm::normalize(frt);
        keyright = glm::normalize(glm::cross(keyfront, WorldUp));
        keyUp = glm::normalize(glm::cross(keyright, keyfront));
    }
};
#endif