//
// Created by pauli on 05/10/2026.
//

#ifndef P1_SHADERPROGRAM_H
#define P1_SHADERPROGRAM_H
#include "string"


class ShaderProgram {
private:
    ShaderProgram();
    ~ShaderProgram();
    ShaderProgram *instancia;
    GLuint idVS = 0; // Identificador del vertex shader
    GLuint idFS = 0; // Identificador del fragment shader
    GLuint idSP = 0; // Identificador del shader program
    GLuint idVAO = 0; // Identificador del vertex array object
    GLuint idVBO = 0; // Identificador del vertex buffer object
    GLuint idIBO = 0; // Identificador del index buffer object
public:
    GLuint get_id_vs() const {
        return idVS;
    }

    GLuint get_id_fs() const {
        return idFS;
    }

    GLuint get_id_sp() const {
        return idSP;
    }

    GLuint get_id_vao() const {
        return idVAO;
    }

    GLuint get_id_vbo() const {
        return idVBO;
    }

    GLuint get_id_ibo() const {
        return idIBO;
    }

    std::string leeArchivoTexto(const std::string& archivo) ;
    bool creaShaderProgram(std::string prefijo, std::string &error );
    void creaModelo();
    ShaderProgram& getInstancia() ;
};


#endif //P1_SHADERPROGRAM_H