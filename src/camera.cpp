/**
  ******************************************************************************
  * @file           : camera.cpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/5/13
  ******************************************************************************
  */



#include "camera.h"

void Camera::updateCameraVectors() {

    // 计算新的向前向量
    glm::vec3 front;
    front.x = cos(glm::radians(_yaw) * cos(glm::radians(_pitch)));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

    _front  = glm::normalize(front);

    _right  = glm::normalize(glm::cross(_front, _worldUp));
    _up     = glm::normalize(glm::cross(_right, _front));
}

Camera::Camera(glm::vec3 position, glm::vec3 worldUp, float yaw, float pitch) {

    _front = glm::vec3(0.0f, 0.0f,-1.0f);

    _moveSpeed = SPEED;
    _mouseSensitivity = SENSITIVITY;
    _fov = FOV;

    _position = position;
    _worldUp = worldUp;
    _yaw = yaw;
    _pitch = pitch;

    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(_position, _position + _front, _up);
}

glm::mat4 Camera::GetProjectionMatrix(float aspect, float zNear, float zFar) {
    return glm::perspective(glm::radians(_fov), aspect, zNear, zFar);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = _moveSpeed * deltaTime;

    if(direction == FORWARD){
        _position += _front * velocity;
    }else if(direction == BACKWARD){
        _position -= _front * velocity;
    }else if(direction == RIGHT){
        _position += _right * velocity;
    }else if(direction == LEFT){
        _position -= _right * velocity;
    }
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch) {

    xOffset *= _mouseSensitivity;
    yOffset *= _mouseSensitivity;

    _yaw += xOffset;
    _pitch += yOffset;

    // 确保俯仰角在范围内，以免屏幕翻转
    if(constrainPitch){
        if(_pitch > 89.0f){
            _pitch = 89.0f;
        }else if(_pitch < -89.0f){
            _pitch = -89.0f;
        }
    }

    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yOffset) {
    _fov -= (float)yOffset;

    // 将fov限制在一定范围
    if(_fov < 1.0f){
        _fov = 1.0f;
    }else if(_fov > 45.0f){
        _fov = 45.0f;
    }

}

void Camera::Update(float deltaTime) {


    if (InputSystem::Instance()->GetKey(GLFW_KEY_W)){
        ProcessKeyboard(FORWARD, deltaTime);
    }

    if (InputSystem::Instance()->GetKey(GLFW_KEY_S))
        ProcessKeyboard(BACKWARD, deltaTime);

    if (InputSystem::Instance()->GetKey(GLFW_KEY_A))
        ProcessKeyboard(LEFT, deltaTime);

    if (InputSystem::Instance()->GetKey(GLFW_KEY_D))
        ProcessKeyboard(RIGHT, deltaTime);

}
