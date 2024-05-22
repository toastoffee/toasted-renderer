/**
  ******************************************************************************
  * @file           : mesh_renderer.hpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/5/22
  ******************************************************************************
  */



#ifndef TOASTED_RENDERER_MESH_RENDERER_HPP
#define TOASTED_RENDERER_MESH_RENDERER_HPP

#include <components/material.hpp>
#include <components/mesh.hpp>

class MeshRenderer{
private:
    Material    *_material;     // 材质
    Mesh        *_mesh;         // 网格

public:

    // 构造函数
    MeshRenderer(Material *material, Mesh *mesh){
        _material = material;
        _mesh = mesh;
    }


    void DrawMesh(){

        // 1. 使用着色器
        _material->UseShader();

        // 2.绘制网格
        _mesh->DrawMesh();
    }
};

#endif //TOASTED_RENDERER_MESH_RENDERER_HPP
