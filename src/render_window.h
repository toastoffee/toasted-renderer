/**
  ******************************************************************************
  * @file           : render_window.h
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/5/14
  ******************************************************************************
  */

#ifndef TOASTED_RENDERER_RENDER_WINDOW_H
#define TOASTED_RENDERER_RENDER_WINDOW_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <camera.h>

class RenderWindow {
private:
    GLFWwindow      *_window;           // GLFW窗口对象
    float           *_clearColor;       // 背景清除颜色
    Camera          *_camera;           // 场景内的摄像机
    std::string     _name;              // 窗口名
    unsigned int    _width;             // 窗口宽度
    unsigned int    _height;            // 窗口高度

public:
    auto GetWindow() -> GLFWwindow* { return _window; }



private:

    // 初始化GLFW窗口
    GLFWwindow *InitWindow();

public:
    // 构造函数
    RenderWindow(Camera *camera, std::string name, unsigned int width, unsigned int height);

    // 终止渲染窗口
    void TerminateWindow();

    // 设置渲染窗口尺寸
    void SetWindowSize(unsigned int width, unsigned int height);

    // 打开深度测试
    void EnableDepthTest(){
        glEnable(GL_DEPTH_TEST);
    }

};


#endif //TOASTED_RENDERER_RENDER_WINDOW_H
