/**
  ******************************************************************************
  * @file           : model.h
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/5/25
  ******************************************************************************
  */



#ifndef TOASTED_RENDERER_MODEL_H
#define TOASTED_RENDERER_MODEL_H

#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include <glm.hpp>

#include <thirdParty/stb_image.h>

#include <vector>
#include <string>
#include <iostream>

#include <components/mesh.hpp>

class Model {

private:

    std::vector<Mesh*> _meshes;                 // 模型的所有网格
    std::string _directory;                     // 模型的加载路径
    std::vector<Texture> _textures_loaded;      // 已经加载的贴图

    // 用assimp加载模型，并且将结果存储在_meshes中
    void loadModel(std::string const &path);

    // 通过递归来处理节点，重复这一过程如果节点下存在子节点
    void processNode(aiNode *node, const aiScene *scene);

    // 将aiMesh转换为mesh
    Mesh* processMesh(aiMesh *mesh, const aiScene *scene);

    // 检查所有材质的贴图，如果他们未被加载则加载他们
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

    //
    unsigned int TextureFromFile(const char *path, const std::string &directory);

public:

    Model(std::string const &path);

    void Draw(const Shader &shader);
};


#endif //TOASTED_RENDERER_MODEL_H
