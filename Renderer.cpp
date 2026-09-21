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

    void Renderer::viewport(int width, int height) {
        glViewport(0, 0, width, height);
    }


} // PAG