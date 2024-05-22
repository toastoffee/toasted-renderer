/**
  ******************************************************************************
  * @file           : shader.cpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/5/10
  ******************************************************************************
  */

#include <shader.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


// 构造器存储着色器路径
Shader::Shader(std::filesystem::path vertexPath, std::filesystem::path fragmentPath) {

    _vertexPath    = std::move(vertexPath);
    _fragmentPath  = std::move(fragmentPath);

    LoadShader();
}


// 析构函数
Shader::~Shader() {
    glDeleteProgram(_programID);
}

// 读取并构建着色器
void Shader::LoadShader() {

    // 1. 从文件路径中获取顶点/片元着色器文件
    std::string     vertexCode;
    std::string     fragmentCode;
    std::ifstream   vertexShaderFile;
    std::ifstream   fragmentShaderFile;

    // 确保ifstream可以抛出异常
    vertexShaderFile.exceptions(std::ifstream ::failbit | std::ifstream ::badbit);
    fragmentShaderFile.exceptions(std::ifstream ::failbit | std::ifstream ::badbit);

    try {
        // 打开文件
        vertexShaderFile.open(_vertexPath);
        fragmentShaderFile.open(_fragmentPath);

        // 将文件内容读进流中
        std::stringstream vertexShaderStream, fragmentShaderStream;
        vertexShaderStream    << vertexShaderFile.rdbuf();
        fragmentShaderStream  << fragmentShaderFile.rdbuf();

        // 关闭文件
        vertexShaderFile.close();
        fragmentShaderFile.close();

        // 将stringStream转换为string
        vertexCode = vertexShaderStream.str();
        fragmentCode = fragmentShaderStream.str();
    }
    catch (std::ifstream::failure &e){
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }

    // 2.编译着色器代码
    const char* vertexShaderCode = vertexCode.c_str();
    const char* fragmentShaderCode = fragmentCode.c_str();

    unsigned int vertexShaderID, fragmentShaderID;
    int success;
    char infoLog[512];

    // 编译顶点着色器代码
    vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID, 1, &vertexShaderCode, nullptr);
    glCompileShader(vertexShaderID);
    // 检查并打印顶点着色器编译错误
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShaderID, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 编译片元着色器代码
    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID, 1, &fragmentShaderCode, nullptr);
    glCompileShader(fragmentShaderID);
    // 检查并打印片元着色器编译错误
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShaderID, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 创建着色器程序并链接
    _programID = glCreateProgram();
    glAttachShader(_programID, vertexShaderID);
    glAttachShader(_programID, fragmentShaderID);
    glLinkProgram(_programID);
    // 检查并打印链接错误
    glGetProgramiv(_programID, GL_LINK_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(_programID, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // 3. 删除顶点片元着色器（因为已经链接到着色器中）
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

// 使用/激活程序
void Shader::Use() const{
    glUseProgram(_programID);
}

void Shader::SetBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(_programID, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(_programID, name.c_str()), value);
}

void Shader::SetFloat(const std::string &name, float value) const{
    glUniform1f(glGetUniformLocation(_programID, name.c_str()), value);
}

void Shader::SetVec2(const std::string &name, float x, float y) const {
    glUniform2f(glGetUniformLocation(_programID, name.c_str()), x, y);
}

void Shader::SetVec2(const std::string &name, const glm::vec2 &val) const {
    glUniform2fv(glGetUniformLocation(_programID, name.c_str()), 1, &val[0]);
}

void Shader::SetVec3(const std::string &name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(_programID, name.c_str()), x, y, z);
}

void Shader::SetVec3(const std::string &name, const glm::vec3 &val) const {
    glUniform3fv(glGetUniformLocation(_programID, name.c_str()), 1, &val[0]);
}

void Shader::SetVec4(const std::string &name, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(_programID, name.c_str()), x, y, z, w);
}

void Shader::SetVec4(const std::string &name, const glm::vec4 &val) const {
    glUniform4fv(glGetUniformLocation(_programID, name.c_str()), 1, &val[0]);
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(_programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

