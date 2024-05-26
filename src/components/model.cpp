/**
  ******************************************************************************
  * @file           : model.cpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/5/25
  ******************************************************************************
  */



#include "model.h"


Model::Model(const std::string &path) {
    loadModel(path);
}

void Model::loadModel(const std::string &path) {

    // 通过 assimp 读取文件
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    // 检查错误
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    // 记录模型的加载路径
    _directory = path.substr(0, path.find_last_of('/'));

    // 处理模型的根节点
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {

    // 处理节点的全部网格
    for (unsigned int i = 0; i < node-> mNumMeshes; ++i) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        _meshes.push_back(processMesh(mesh, scene));
    }

    // 对其所有的子节点重复这一过程
    for (unsigned int i = 0; i < node->mNumChildren; ++i) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh *Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    // 处理顶点位置、法线和纹理坐标
    for(unsigned int i = 0; i < mesh->mNumVertices; i++){

        Vertex vertex;

        // 创建一个glm::vec3的临时变量，用来装参数(因为assimp有自己的vec3类)
        glm::vec3 vector3;

        // 位置向量 position
        vector3.x = mesh->mVertices[i].x;
        vector3.y = mesh->mVertices[i].y;
        vector3.z = mesh->mVertices[i].z;
        vertex.Position = vector3;

        // 法线向量 normal
        if(mesh->HasNormals()) {
            vector3.x = mesh->mNormals[i].x;
            vector3.y = mesh->mNormals[i].y;
            vector3.z = mesh->mNormals[i].z;
            vertex.Normal = vector3;
        }

        // 贴图uv texCoords
        if(mesh->mTextureCoords[0]){
            glm::vec2 vector2;

            vector2.x = mesh->mTextureCoords[0][i].x;
            vector2.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vector2;
        }else{
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }


        vertices.push_back(vertex);
    }

    // 处理索引
    // 遍历mesh的每一个面（每一个面都是triangle）
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {

        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }


    // 处理材质
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffuseMaps = loadMaterialTextures(material,aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<Texture> specularMaps = loadMaterialTextures(material,aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return new Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName) {

    std::vector<Texture> textures;

    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for(unsigned int j = 0; j < _textures_loaded.size(); j++)
        {
            if(std::strcmp(_textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(_textures_loaded[j]);
                skip = true;
                break;
            }
        }
        if(!skip)
        {   // 如果纹理还没有被加载，则加载它
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), _directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            _textures_loaded.push_back(texture); // 添加到已加载的纹理中
        }
    }
    return textures;
}

unsigned int Model::TextureFromFile(const char *path, const std::string &directory) {

    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

void Model::Draw(const Shader &shader) {

    shader.Use();

    for (unsigned int i = 0; i < _meshes.size(); ++i) {
        _meshes[i]->DrawWithTexture(shader);
    }
}
