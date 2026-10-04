//
// Created by pauli on 21/09/2026.
//
#include <glad/glad.h>
#include "Renderer.h"
#include <GL/gl.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
namespace PAG {
    Renderer* Renderer::instancia = nullptr;
    Renderer::Renderer ()=default;
    Renderer::~Renderer() {
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
    

    PAG::Renderer& PAG::Renderer::getInstancia ()
    { if ( !instancia )
    { instancia = new Renderer ();
    }
        return *instancia;
    }

    void Renderer::refrescar() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


        if (idSP != 0) {
            glUseProgram(idSP);
            glBindVertexArray(idVAO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
        }
    }

    void Renderer::viewport(int x, int y, int width, int height) {
        glViewport(x, y, width, height);
    }


    std::string Renderer::getRendererInfo() {
        return reinterpret_cast<const char*>(glGetString(GL_RENDERER));
    }
    std::string Renderer::getVendorInfo() {
        return reinterpret_cast<const char*>(glGetString(GL_VENDOR));
    }
    std::string Renderer::getVersionInfo() {
        return reinterpret_cast<const char*>(glGetString(GL_VERSION));
    }
    std::string Renderer::getShadingLanguageVersionInfo() {
        return reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));
    }


    void Renderer::enable() {
        glEnable(GL_DEPTH_TEST);
    }

    void Renderer::ClearColor(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
    }


// métodos shader

// Este método lo hago con un bool para que luego pueda sacar los mensajes en main por la ventana de gui sin tener que conectar gui con renderer
bool Renderer::creaShaderProgram(std::string prefijo, std::string &error){

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




void Renderer::creaModelo()
{
    GLfloat vertices[] = { -.5, -.5, 0,
                            .5, -.5, 0,
                            .0,  .5, 0 };
    GLuint indices[] = { 0, 1, 2 };

    glGenVertexArrays(1, &idVAO);
    glBindVertexArray(idVAO);

    glGenBuffers(1, &idVBO);
    glBindBuffer(GL_ARRAY_BUFFER, idVBO);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &idIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLuint), indices, GL_STATIC_DRAW);
}

/**
* Método para inicializar los parámetros globales de OpenGL
*/
void Renderer::inicializaOpenGL()
{
    glClearColor(_colorBorrado[0], _colorBorrado[1], _colorBorrado[2], _colorBorrado[3]);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
}


    // metodo para leer archivos
    std::string Renderer::leeArchivoTexto(const std::string& doc) {
        std::ifstream archivo(doc);
        if (!archivo) {
            return "";
        }
        std::stringstream stream;
        stream << archivo.rdbuf();
        return stream.str();
    }


}