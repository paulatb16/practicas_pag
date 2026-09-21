//
// Created by pauli on 21/09/2026.
//

#ifndef P1_RENDERER_H
#define P1_RENDERER_H
#include <glad/glad.h>
#include <GL/gl.h>

namespace PAG {
    class Renderer {
    private:
        static Renderer* instancia;
        Renderer();
        ~Renderer();


    public:
        static Renderer& getInstancia();
        void refrescar();
        void viewport(int width, int height);
        void callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    };
} // PAG

#endif //P1_RENDERER_H