#ifndef P1_SHADERPROGRAM_H
#define P1_SHADERPROGRAM_H

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace PAG {
    class ShaderProgram {
    private:
        ShaderProgram();
        ~ShaderProgram();
        static ShaderProgram *instancia;

        GLuint idVS = 0; // Identificador del vertex shader
        GLuint idFS = 0; // Identificador del fragment shader
        GLuint idSP = 0; // Identificador del shader program

    public:
        // Deshabilitar copia
        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;

        static ShaderProgram& getInstancia();

        GLuint get_id_vs() const { return idVS; }
        GLuint get_id_fs() const { return idFS; }
        GLuint get_id_sp() const { return idSP; }

        std::string leeArchivoTexto(const std::string& archivo);
        bool creaShaderProgram(std::string prefijo, std::string &error);

        // Activa este shader en la tarjeta gráfica
        void usar() const {
            if (idSP != 0) glUseProgram(idSP);
        }

        // Envía una matriz 4x4 al shader (por ejemplo, la matriz MVP o de Modelo)
        void setUniform(const std::string& nombre, const glm::mat4& matriz) const {
            GLint loc = glGetUniformLocation(idSP, nombre.c_str());
            if (loc != -1) {
                glUniformMatrix4fv(loc, 1, GL_FALSE, &matriz[0][0]);
            }
        }
    };
}
#endif //P1_SHADERPROGRAM_H