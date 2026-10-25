#include <glad/glad.h>
#include "ShaderProgram.h"
#include <GL/gl.h>
#include <fstream>
#include <sstream>

namespace PAG {
    ShaderProgram* ShaderProgram::instancia = nullptr;
    ShaderProgram::ShaderProgram() = default;

    ShaderProgram& ShaderProgram::getInstancia() {
        if (!instancia) {
            instancia = new ShaderProgram();
        }
        return *instancia;
    }

    ShaderProgram::~ShaderProgram() {
        if (idVS != 0) {
            glDeleteShader(idVS);
        }
        if (idFS != 0) {
            glDeleteShader(idFS);
        }
        if (idSP != 0) {
            glDeleteProgram(idSP);
        }
    }

    bool ShaderProgram::creaShaderProgram(std::string prefijo, std::string &error) {
        std::string VS = prefijo + "-vs.glsl";
        std::string FS = prefijo + "-fs.glsl";
        error = "";

        std::string miVertexShader = leeArchivoTexto(VS);
        std::string miFragmentShader = leeArchivoTexto(FS);

        if (miVertexShader == "") {
            error = "el archivo no se puede abrir del vertex shader no se puede abrir";
            return false;
        }
        if (miFragmentShader == "") {
            error = "el archivo no se puede abrir del fragment shader no se puede abrir";
            return false;
        }

        // Vertex Shader
        idVS = glCreateShader(GL_VERTEX_SHADER);
        if (idVS == 0) {
            error = "Cannot create shader object (Vertex Shader).";
            return false;
        }

        const GLchar* fuenteVS = miVertexShader.c_str();
        glShaderSource(idVS, 1, &fuenteVS, nullptr);
        glCompileShader(idVS);

        GLint compileResultVS;
        glGetShaderiv(idVS, GL_COMPILE_STATUS, &compileResultVS);
        if (compileResultVS == GL_FALSE) {
            GLint logLen = 0;
            glGetShaderiv(idVS, GL_INFO_LOG_LENGTH, &logLen);
            if (logLen > 0) {
                char* cLogString = new char[logLen];
                GLint written = 0;
                glGetShaderInfoLog(idVS, logLen, &written, cLogString);
                error = "Cannot compile GL_VERTEX_SHADER:\n" + std::string(cLogString);
                delete[] cLogString;
            }
            glDeleteShader(idVS);
            idVS = 0;
            return false;
        }

        // Fragment Shader
        idFS = glCreateShader(GL_FRAGMENT_SHADER);
        if (idFS == 0) {
            error = "Cannot create shader object (Fragment Shader).";
            return false;
        }

        const GLchar* fuenteFS = miFragmentShader.c_str();
        glShaderSource(idFS, 1, &fuenteFS, nullptr);
        glCompileShader(idFS);

        GLint compileResultFS;
        glGetShaderiv(idFS, GL_COMPILE_STATUS, &compileResultFS);
        if (compileResultFS == GL_FALSE) {
            GLint logLen = 0;
            glGetShaderiv(idFS, GL_INFO_LOG_LENGTH, &logLen);
            if (logLen > 0) {
                char* cLogString = new char[logLen];
                GLint written = 0;
                glGetShaderInfoLog(idFS, logLen, &written, cLogString);
                error = "Cannot compile GL_FRAGMENT_SHADER:\n" + std::string(cLogString);
                delete[] cLogString;
            }
            glDeleteShader(idFS);
            idFS = 0;
            return false;
        }

        // Shader Program
        idSP = glCreateProgram();
        if (idSP == 0) {
            error = "Cannot create shader program.";
            return false;
        }

        glAttachShader(idSP, idVS);
        glAttachShader(idSP, idFS);
        glLinkProgram(idSP);

        GLint linkSuccess = 0;
        glGetProgramiv(idSP, GL_LINK_STATUS, &linkSuccess);
        if (linkSuccess == GL_FALSE) {
            GLint logLen = 0;
            glGetProgramiv(idSP, GL_INFO_LOG_LENGTH, &logLen);
            if (logLen > 0) {
                char* cLogString = new char[logLen];
                GLint written = 0;
                glGetProgramInfoLog(idSP, logLen, &written, cLogString);
                error = "Cannot link shader program:\n" + std::string(cLogString);
                delete[] cLogString;
            }
            glDeleteProgram(idSP);
            idSP = 0;
            return false;
        }

        return true;
    }

    std::string ShaderProgram::leeArchivoTexto(const std::string& doc) {
        std::ifstream archivo(doc);
        if (!archivo) {
            return "";
        }
        std::stringstream stream;
        stream << archivo.rdbuf();
        return stream.str();
    }
}