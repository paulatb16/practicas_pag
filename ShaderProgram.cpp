//
// Created by pauli on 05/10/2026.
//
#include <glad/glad.h>
#include "ShaderProgram.h"
#include <GL/gl.h>
#include <fstream>
#include <sstream>


namespace PAG {
    ShaderProgram* ShaderProgram::instancia = nullptr;
    ShaderProgram::ShaderProgram()=default;




    ShaderProgram& ShaderProgram::getInstancia() {
        if (!instancia) {
            instancia = new ShaderProgram();
        }
        return *instancia;
    }

    ShaderProgram:: ~ShaderProgram() {
        if ( idVS != 0 )
        { glDeleteShader ( idVS );
        }
        if ( idFS != 0 )
        { glDeleteShader ( idFS );
        }
        if ( idSP != 0 )
        { glDeleteProgram ( idSP );
        }
        if ( idVBO != 0 )
        { glDeleteBuffers ( 1, &idVBO );
        }
        if ( idIBO != 0 )
        { glDeleteBuffers ( 1, &idIBO );
        }
        if ( idVAO != 0 )
        { glDeleteVertexArrays ( 1, &idVAO );
        }
    }



    // métodos shader

    // Este método lo hago con un bool para que luego pueda sacar los mensajes en main por la ventana de gui sin tener que conectar gui con renderer
    bool ShaderProgram::creaShaderProgram(std::string prefijo, std::string &error){

        std::string VS = prefijo + "-vs.glsl";
        std::string FS = prefijo + "-fs.glsl";
        error = "";

        // comprobacion de que abren todos los archivos
        std::string miVertexShader=leeArchivoTexto(VS);

        std::string miFragmentShader=leeArchivoTexto(FS);
        if (miVertexShader=="" ){
            error="el archivo no se puede abrir del vertex shader no se puede abrir";
            return false;
        }
        if (miFragmentShader=="" ){
            error="el archivo no se puede abrir del fragment shader no se puede abrir";
            return false;
        }

        //vertex shader
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

        // fragment shader
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

        // shader Program
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




    void ShaderProgram::creaModelo()
    {
        GLuint indices[] = { 0, 1, 2 };

        //no entrlazada
        GLfloat posiciones[] = {
            -.5f, -.5f, 0.0f,
             .5f, -.5f, 0.0f,
             .0f,  .5f, 0.0f
        };

        GLfloat colores[] = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
        };

        glGenVertexArrays(1, &idVAO);
        glBindVertexArray(idVAO);

        //posiciones
        GLuint vbo[2];
        glGenBuffers(2, vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), posiciones, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);

        //colores
        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colores, GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(1);


        idVBO = vbo[0];
        glGenBuffers(1, &idIBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLuint), indices, GL_STATIC_DRAW);


        //entrelazado comentado
        /*
        GLfloat verticesEntrelazados[] = {

            -.5f, -.5f, 0.0f,      1.0f, 0.0f, 0.0f,
             .5f, -.5f, 0.0f,      0.0f, 1.0f, 0.0f,
             .0f,  .5f, 0.0f,      0.0f, 0.0f, 1.0f
        };

        glGenVertexArrays(1, &idVAO);
        glBindVertexArray(idVAO);

        glGenBuffers(1, &idVBO);
        glBindBuffer(GL_ARRAY_BUFFER, idVBO);
        glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), verticesEntrelazados, GL_STATIC_DRAW);

        GLsizei stride = 6 * sizeof(GLfloat);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glGenBuffers(1, &idIBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLuint), indices, GL_STATIC_DRAW);
        */



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
