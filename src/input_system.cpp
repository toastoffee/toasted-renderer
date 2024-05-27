/**
  ******************************************************************************
  * @file           : InputSystem.cpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/5/14
  ******************************************************************************
  */



#include "input_system.h"

void InputSystem::Init(GLFWwindow *window) {
    _window = window;
}

bool InputSystem::GetKey(int glfw_key) const {
    return glfwGetKey(_window, glfw_key) == GLFW_PRESS;
}



