/**
  ******************************************************************************
  * @file           : Input.cpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/5/14
  ******************************************************************************
  */



#include "Input.h"

bool Input::GetKey(int glfw_key) const {
    return glfwGetKey(_window, glfw_key) == GLFW_PRESS;
}


