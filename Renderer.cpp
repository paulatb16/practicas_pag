//
// Created by pauli on 21/09/2026.
//
#include <glad/glad.h>
#include "Renderer.h"
#include <GL/gl.h>
#include <iostream>
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

    void Renderer::refrescar ()
    { glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
        glUseProgram ( idSP );
        glBindVertexArray ( idVAO );
        glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, idIBO );
        glDrawElements ( GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr );
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
    void Renderer::creaShaderProgram( )
    { std::string miVertexShader =
    "#version 410\n"
    "layout (location = 0) in vec3 posicion;\n"
    "void main ()\n"
    "{ gl_Position = vec4 ( posicion, 1 );\n"
    "}\n";
        std::string miFragmentShader =
        "#version 410\n"
        "out vec4 colorFragmento;\n"
        "void main ()\n"
        "{ colorFragmento = vec4 ( 1.0, .4, .2, 1.0 );\n"
        "}\n";
        idVS = glCreateShader ( GL_VERTEX_SHADER );
        const GLchar* fuenteVS = miVertexShader.c_str ();
        glShaderSource ( idVS, 1, &fuenteVS, nullptr );
        glCompileShader ( idVS );
        idFS = glCreateShader ( GL_FRAGMENT_SHADER );
        const GLchar* fuenteFS = miFragmentShader.c_str ();
        glShaderSource ( idFS, 1, &fuenteFS, nullptr );
        glCompileShader ( idFS );
        idSP = glCreateProgram ();
        glAttachShader ( idSP, idVS );
        glAttachShader ( idSP, idFS );
        glLinkProgram ( idSP );
    }

    void Renderer::creaModelo ( )
    { GLfloat vertices[] = { -.5, -.5, 0,
    .5, -.5, 0,
    .0, .5, 0 };
        GLuint indices[] = { 0, 1, 2 };
        glGenVertexArrays ( 1, &idVAO );
        glBindVertexArray ( idVAO );
        glGenBuffers ( 1, &idVBO );
        glBindBuffer ( GL_ARRAY_BUFFER, idVBO );
        glBufferData ( GL_ARRAY_BUFFER, 9*sizeof(GLfloat), vertices, GL_STATIC_DRAW );
        glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), nullptr );
        glEnableVertexAttribArray ( 0 );
        glGenBuffers ( 1, &idIBO );
        glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, idIBO );
        glBufferData ( GL_ELEMENT_ARRAY_BUFFER, 3*sizeof(GLuint), indices, GL_STATIC_DRAW );
    }

    /**
* Método para inicializar los parámetros globales de OpenGL
*/
    void Renderer::inicializaOpenGL ( )
    { glClearColor ( _colorBorrado[0], _colorBorrado[1], _colorBorrado[2], _colorBorrado[3] );
        glEnable ( GL_DEPTH_TEST );
        glEnable ( GL_MULTISAMPLE );
    }



} // PAG