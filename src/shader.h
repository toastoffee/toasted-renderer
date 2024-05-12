/**
  ******************************************************************************
  * @file           : shader.h
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/5/10
  ******************************************************************************
  */

#ifndef TOASTED_RENDERER_SHADER_H
#define TOASTED_RENDERER_SHADER_H

#include "glad/glad.h"
#include "glm.hpp"
#include <string>



class Shader {

private:

    unsigned int _programID;                    // 着色器程序ID
    std::string _name;                          // 着色器名称
    std::filesystem::path _vertexPath;          // 顶点着色器文件路径
    std::filesystem::path _fragmentPath;        // 片元着色器文件路径

public:

    // 构造器读取并构建着色器
    Shader(std::filesystem::path vertexPath, std::filesystem::path fragmentPath);

    // 析构函数
    ~Shader();

    // 加载着色器
    void LoadShader();

    // 使用/激活程序
    void use() const;


    // uniform工具函数
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

    void setVec2(const std::string &name, float x, float y) const;
    void setVec2(const std::string &name, const glm::vec2 &val) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setVec3(const std::string &name, const glm::vec3 &val) const;
    void setVec4(const std::string &name, float x, float y, float z, float w) const;
    void setVec4(const std::string &name, const glm::vec4 &val) const;

    void setMat4(const std::string &name, const glm::mat4 &mat) const;


};


#endif //TOASTED_RENDERER_SHADER_H
