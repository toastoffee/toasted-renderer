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

    
}

void Camera::ProcessMouseScroll(float yOffset) {

}
