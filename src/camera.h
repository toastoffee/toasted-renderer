/**
  ******************************************************************************
  * @file           : camera.h
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/5/13
  ******************************************************************************
  */


#ifndef TOASTED_RENDERER_CAMERA_H
#define TOASTED_RENDERER_CAMERA_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>


enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
};

class Camera {

private:

    glm::vec3 _position;

    glm::vec3 _front;
    glm::vec3 _up;
    glm::vec3 _right;


    float _moveSpeed;
    float _mouseSensitivity;
    float _zoom;

public:


};


#endif //TOASTED_RENDERER_CAMERA_H
