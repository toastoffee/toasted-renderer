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

#include <glad/glad.h>
#include "glm.hpp"
#include <string>
#include <filesystem>


class Shader {

private:

    unsigned int            _programID;           // 着色器程序ID
    std::string             _name;                // 着色器名称
    std::filesystem::path   _vertexPath;          // 顶点着色器文件路径
    std::filesystem::path   _fragmentPath;        // 片元着色器文件路径

public:

//    auto ProgramID() const -> unsigned int {return _programID;}

    // 构造器读取并构建着色器
    Shader(std::filesystem::path vertexPath, std::filesystem::path fragmentPath);

    // 析构函数
    ~Shader();

    // 加载着色器
    void LoadShader();

    // 使用/激活程序
    void Use() const;


    // uniform工具函数
    void SetBool (const std::string &name, bool  value) const;
    void SetInt  (const std::string &name, int   value) const;
    void SetFloat(const std::string &name, float value) const;

    void SetVec2(const std::string &name, float x, float y) const;
    void SetVec2(const std::string &name, const glm::vec2 &val) const;
    void SetVec3(const std::string &name, float x, float y, float z) const;
    void SetVec3(const std::string &name, const glm::vec3 &val) const;
    void SetVec4(const std::string &name, float x, float y, float z, float w) const;
    void SetVec4(const std::string &name, const glm::vec4 &val) const;

    void SetMat4(const std::string &name, const glm::mat4 &mat) const;


};


#endif //TOASTED_RENDERER_SHADER_H
