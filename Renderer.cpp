//
// Created by pauli on 21/09/2026.
//

#include "Renderer.h"
#include <glad/glad.h>
#include <GL/gl.h>
#include <iostream>
using namespace std;
namespace PAG {
    Renderer* Renderer::instancia = nullptr;
    Renderer::Renderer ()=default;
    Renderer::~Renderer(){}

    PAG::Renderer& PAG::Renderer::getInstancia ()
    { if ( !instancia )
    { instancia = new Renderer ();
    }
        return *instancia;
    }

    void Renderer::refrescar ()
    { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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


} // PAG