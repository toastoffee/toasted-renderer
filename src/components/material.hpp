/**
  ******************************************************************************
  * @file           : material.hpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/5/22
  ******************************************************************************
  */



#ifndef TOASTED_RENDERER_MATERIAL_HPP
#define TOASTED_RENDERER_MATERIAL_HPP

#include <shader.h>

class Material{

private:
    Shader      *_shader;       // 材质对应的着色器

public:

    // 构造函数
    Material(Shader *shader){
        _shader = shader;
    }

    ~Material(){

    }

    // 使用着色器
    void UseShader(){
        _shader->Use();
    }
};

#endif //TOASTED_RENDERER_MATERIAL_HPP
