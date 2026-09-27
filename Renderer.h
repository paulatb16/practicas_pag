//
// Created by pauli on 21/09/2026.
//

#ifndef P1_RENDERER_H
#define P1_RENDERER_H
#include <glad/glad.h>
#include <GL/gl.h>
#include "string"

namespace PAG {
    class Renderer {
    private:
        static Renderer* instancia;
        Renderer();
        ~Renderer();


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

    };
} // PAG

#endif //P1_RENDERER_H