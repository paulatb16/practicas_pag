//
// Created by pauli on 21/09/2026.
//
#include <glad/glad.h>
#include "Renderer.h"
#include <GL/gl.h>

#include <fstream>

#include "ShaderProgram.h"
using namespace std;
namespace PAG {
    Renderer* Renderer::instancia = nullptr;
    Renderer::Renderer ()=default;
    Renderer::~Renderer()=default;
    

    PAG::Renderer& PAG::Renderer::getInstancia ()
    { if ( !instancia )
    { instancia = new Renderer ();
    }
        return *instancia;
    }

    void Renderer::refrescar() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


        if (ShaderProgram::getInstancia().get_id_sp()!= 0) {
            glUseProgram(ShaderProgram::getInstancia().get_id_sp());
            glBindVertexArray(ShaderProgram::getInstancia().get_id_vao());
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ShaderProgram::getInstancia().get_id_ibo());
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




/**
* Método para inicializar los parámetros globales de OpenGL
*/
void Renderer::inicializaOpenGL()
{
    glClearColor(_colorBorrado[0], _colorBorrado[1], _colorBorrado[2], _colorBorrado[3]);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
}




}