/**
  ******************************************************************************
  * @file           : Input.h
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/5/14
  ******************************************************************************
  */

#include "utils/singleton.h"
#include <GLFW/glfw3.h>

#ifndef TOASTED_RENDERER_INPUT_H
#define TOASTED_RENDERER_INPUT_H


// 致敬传奇游戏引擎Unity
class Input : public Singleton<Input>{
private:
    GLFWwindow *_window;
public:

    // 当对应按键处于按下状态的时候返回true,否则false
    bool GetKey(int glfw_key) const;


};


#endif //TOASTED_RENDERER_INPUT_H
