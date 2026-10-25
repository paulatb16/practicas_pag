//
// Created by pauli on 21/09/2026.
//

#ifndef P1_RENDERER_H
#define P1_RENDERER_H
#include <GL/gl.h>
#include "string"
#include "model.h"

namespace PAG {
    class Renderer {
    private:
        static Renderer* instancia;
        Renderer();
        ~Renderer();
        GLfloat _colorBorrado[4] = { 0.6f, 0.6f, 0.6f, 1.0f };
        std::vector<Model*> _modelos;

    public:
        static Renderer& getInstancia();
        void refrescar();
        void viewport(int x, int y,int width, int height);
        std::string getRendererInfo();
        std::string getVendorInfo();
        std::string getVersionInfo();
        std::string getShadingLanguageVersionInfo();
        void enable();
        void ClearColor(float r, float g, float b, float a);
        void inicializaOpenGL();
        //para añadir modelos
        void addModelo(Model* modelo) {
            _modelos.push_back(modelo);
        }
        //paara la lista de modelos en el gui
        std::vector<Model*>& getModelos() {
            return _modelos;
        }

    };
} // PAG

#endif //P1_RENDERER_H