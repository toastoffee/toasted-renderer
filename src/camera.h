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

#include <glad/glad.h>

#include <input_system.h>

enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float FOV        =  45.0f;


class Camera {

private:

    glm::vec3 _position;        // 位置
    glm::vec3 _front;           // 向前向量
    glm::vec3 _up;              // 向上向量
    glm::vec3 _right;           // 向右向量
    glm::vec3 _worldUp;         // 世界向上向量

    float _yaw;                 // 偏航角
    float _pitch;               // 俯仰角

    float _moveSpeed;           // 相机移动速度
    float _mouseSensitivity;    // 鼠标敏感度
    float _fov;                // Field Of View

    void updateCameraVectors();

public:

    // 构造函数
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

    // 获取视图矩阵
    glm::mat4 GetViewMatrix();

    // 获取投影矩阵
    glm::mat4 GetProjectionMatrix(float aspect, float zNear, float zFar);

    // 处理键盘输入
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);

    // 处理鼠标输入
    void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true);

    // 处理滚轮输入
    void ProcessMouseScroll(float yOffset);

    // 更新相机
    void Update(float deltaTime);

};


#endif //TOASTED_RENDERER_CAMERA_H
