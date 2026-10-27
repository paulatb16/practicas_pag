#include "Model.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stdexcept>
#include <iostream>

namespace PAG {

Model::Model(const std::string& filePath, const std::string& name) : _name(name) {
    loadOBJ(filePath);
}

Model::~Model() {
    if (_ibo != 0) glDeleteBuffers(1, &_ibo);
    if (_vbo != 0) glDeleteBuffers(1, &_vbo);
    if (_vao != 0) glDeleteVertexArrays(1, &_vao);
}



void Model::loadOBJ(const std::string& filePath) {
    Assimp::Importer importer;


    const aiScene* scene = importer.ReadFile(
        filePath,
        aiProcess_JoinIdenticalVertices |
        aiProcess_Triangulate |
        aiProcess_GenSmoothNormals
    );

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        throw std::runtime_error("Error al cargar OBJ con Assimp: " + std::string(importer.GetErrorString()));
    }

    std::vector<float> interleavedVertices;
    std::vector<unsigned int> indices;
    unsigned int indexOffset = 0;


    for (unsigned int m = 0; m < scene->mNumMeshes; ++m) {
        aiMesh* mesh = scene->mMeshes[m];

      
        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {

            interleavedVertices.push_back(mesh->mVertices[i].x);
            interleavedVertices.push_back(mesh->mVertices[i].y);
            interleavedVertices.push_back(mesh->mVertices[i].z);


            if (mesh->HasNormals()) {
                interleavedVertices.push_back(mesh->mNormals[i].x);
                interleavedVertices.push_back(mesh->mNormals[i].y);
                interleavedVertices.push_back(mesh->mNormals[i].z);
            } else {
                interleavedVertices.push_back(0.0f);
                interleavedVertices.push_back(1.0f);
                interleavedVertices.push_back(0.0f);
            }
        }


        for (unsigned int f = 0; f < mesh->mNumFaces; ++f) {
            aiFace face = mesh->mFaces[f];
            for (unsigned int j = 0; j < face.mNumIndices; ++j) {
                indices.push_back(indexOffset + face.mIndices[j]);
            }
        }

        indexOffset += mesh->mNumVertices;
    }

    _indexCount = static_cast<GLsizei>(indices.size());
    

    setupBuffers(interleavedVertices, indices);
}


void Model::setupBuffers(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) {
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ibo);

    glBindVertexArray(_vao);


    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    GLsizei stride = 6 * sizeof(float);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}


glm::mat4 Model::getModelMatrix() const {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, _position);
    model = glm::rotate(model, glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, _scale);
    return model;
}


void Model::render(ShaderProgram& shader, const glm::mat4& viewMatrix, const glm::mat4& projMatrix) {
    shader.usar();

    glm::mat4 modelMatrix = getModelMatrix();
    

    shader.setUniform("u_matrizModel", modelMatrix);
    shader.setUniform("u_matrizView", viewMatrix);
    shader.setUniform("u_matrizProjection", projMatrix);

    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

}