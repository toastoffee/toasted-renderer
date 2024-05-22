/**
  ******************************************************************************
  * @file           : render_window.cpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/5/14
  ******************************************************************************
  */



#include "render_window.h"

#include <utility>

RenderWindow::RenderWindow(Camera *camera, std::string name, unsigned int width, unsigned int height) {

    _camera = camera;
    _name   = std::move(name);
    _width  = width;
    _height = height;

    _window = InitWindow();
}

void RenderWindow::TerminateWindow() {

}

void RenderWindow::SetWindowSize(unsigned int width, unsigned int height) {

}

GLFWwindow *RenderWindow::InitWindow() {

    // glfw 初始化和设置
    glfwInit();                                                                                 // GLFW窗口设置初始化
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                                   // 设置openGL的主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                                   // 设置openGL的次版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);                   // 使用openGL的核心模式(core profile)

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);                         // Mac OS X需要额外执行这句
    #endif

    GLFWwindow* window = glfwCreateWindow((int)_width, (int)_height, _name.c_str(),     // 创建GLFW窗口
                                          nullptr, nullptr);

    if(window == nullptr){
        std::cout << "ERROR::GLFW::WINDOW_CREATE_FAILED" << std::endl;                          // GLFW窗口创建失败报错
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);                                                             // 将窗口的上下文设置为当前线程的主上下文

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))                                    // GLAD加载系统相关的OpenGL函数指针地址
    {
        std::cout << "ERROR::GLAD::INITIALIZATION_FAILED" << std::endl;                         // GLAD加载失败报错
        return nullptr;
    }

    return window;
}

void RenderWindow::RenderLoop() {


    while(!glfwWindowShouldClose(_window))
    {
        // 设置清除颜色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        // 清除颜色缓冲和深度缓冲
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(_window);

        glfwPollEvents();
    }

    TerminateWindow();
    
}
