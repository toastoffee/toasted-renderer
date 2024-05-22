/**
  ******************************************************************************
  * @file           : mesh.hpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/5/22
  ******************************************************************************
  */


#ifndef TOASTED_RENDERER_MESH_HPP
#define TOASTED_RENDERER_MESH_HPP



#include <glm.hpp>

#include <string>
#include <vector>

#include <shader.h>

struct Vertex
{
public:
    glm::vec3 Position;         // 顶点位置
    glm::vec3 Normal;           // 顶点法线向量
    glm::vec2 TexCoords;        // 顶点纹理坐标
};

struct Texture
{
public:
    unsigned int Id;            // 纹理的id
    std::string Type;           // 纹理的类型
};

class Mesh
{
private:
    std::vector<Vertex> _vertices;          // 网格的顶点
    std::vector<unsigned int> _indices;     // 网格的顶点索引
    std::vector<Texture> _textures;         // 网格的纹理

    unsigned int VAO,                       // 顶点数组对象(Vertex Array Object, VAO)
                 VBO,                       // 顶点缓冲对象(Vertex Buffer Object, VBO)
                 EBO;                       // 元素缓冲对象(Element Buffer Object，EBO)


private:

    // 初始化缓冲区
    void setUpMesh(){

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), _vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), _indices.data(), GL_STATIC_DRAW);

        // 顶点位置
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        // 顶点法线
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Normal));

        // 顶点纹理坐标
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, TexCoords));

        glBindVertexArray(0);
    }

public:

    // 构造函数
    Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures){
        _vertices = vertices;
        _indices = indices;
        _textures = textures;

        setUpMesh();
    }

};


#endif //TOASTED_RENDERER_MESH_HPP
