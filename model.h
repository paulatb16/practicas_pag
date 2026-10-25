#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include "ShaderProgram.h"

namespace PAG {

    class Model {
    private:

        GLuint _vao = 0;
        GLuint _vbo = 0;
        GLuint _ibo = 0;
        GLsizei _indexCount = 0;


        glm::vec3 _position{0.0f, 0.0f, 0.0f};
        glm::vec3 _rotation{0.0f, 0.0f, 0.0f};
        glm::vec3 _scale{1.0f, 1.0f, 1.0f};

        std::string _name;


        void setupBuffers(const std::vector<float>& interleavedVertices, const std::vector<unsigned int>& indices);

    public:
        Model(const std::string& filePath, const std::string& name = "Modelo");
        ~Model();

        
        void loadOBJ(const std::string& filePath);


        void render(ShaderProgram& shader, const glm::mat4& viewMatrix, const glm::mat4& projMatrix);

        glm::mat4 getModelMatrix() const;

        glm::vec3& getPosition() { return _position; }
        glm::vec3& getRotation() { return _rotation; }
        glm::vec3& getScale()    { return _scale; }
        const std::string& getName() const { return _name; }
    };

}