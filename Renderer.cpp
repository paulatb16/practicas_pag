#include <glad/glad.h>
#include "Renderer.h"
#include <GL/gl.h>
#include <fstream>
#include "Camara.h"
#include "ShaderProgram.h"

using namespace std;
namespace PAG {
    Renderer* Renderer::instancia = nullptr;
    Renderer::Renderer() = default;
    Renderer::~Renderer() {
        for (Model* modelo : _modelos) {
            delete modelo;
        }
        _modelos.clear();
    }

    Renderer& Renderer::getInstancia() {
        if (!instancia) {
            instancia = new Renderer();
        }
        return *instancia;
    }

    void Renderer::refrescar() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glm::mat4 matrizVista = Camara::getInstancia().getViewMatrix(); //matrices
        glm::mat4 matrizProyeccion = Camara::getInstancia().getProjectionMatrix();
        ShaderProgram& shader = ShaderProgram::getInstancia(); //shader program
        if (shader.get_id_sp() != 0) {
            for (Model* modelo : _modelos) {
                modelo->render(shader, matrizVista, matrizProyeccion); //dibujamos los modelos de la lista
            }
        }

    }

    void Renderer::viewport(int x, int y, int width, int height) {
        glViewport(x, y, width, height);
        if (height > 0) {
            Camara::getInstancia().setAspect(static_cast<float>(width) / static_cast<float>(height));
        }
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

    void Renderer::inicializaOpenGL() {
        glClearColor(_colorBorrado[0], _colorBorrado[1], _colorBorrado[2], _colorBorrado[3]);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_MULTISAMPLE);
    }


    void Renderer::removeModelo(size_t index) {
        if (index < _modelos.size()) {
            delete _modelos[index];
            _modelos.erase(_modelos.begin() + index);
        }
    }
}