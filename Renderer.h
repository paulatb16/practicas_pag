//
// Created by pauli on 21/09/2026.
//

#ifndef P1_RENDERER_H
#define P1_RENDERER_H
#include <GL/gl.h>
#include "string"

namespace PAG {
    class Renderer {
    private:
        static Renderer* instancia;
        Renderer();
        ~Renderer();
        GLuint idVS = 0; // Identificador del vertex shader
        GLuint idFS = 0; // Identificador del fragment shader
        GLuint idSP = 0; // Identificador del shader program
        GLuint idVAO = 0; // Identificador del vertex array object
        GLuint idVBO = 0; // Identificador del vertex buffer object
        GLuint idIBO = 0; // Identificador del index buffer object
        GLfloat _colorBorrado[4] = { 0.6f, 0.6f, 0.6f, 1.0f };

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
        void Clear();
        void creaShaderProgram( );
        void creaModelo();
        void inicializaOpenGL();

    };
} // PAG

#endif //P1_RENDERER_H