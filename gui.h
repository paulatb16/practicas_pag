#ifndef imgui_h
#define imgui_h

#include <GLFW/glfw3.h>

namespace PAG {

    class gui {
    private:
        static gui* instancia;
        gui();

    public:
        virtual ~gui();
        static gui& getInstancia(); //igual que en renderer el puntero para acceder a la clase
        void inicializar(GLFWwindow* window); //funcion para inicializar en el bucle


        void render();
        void finalizar();

        void procesaClick(int button, int action);
        void procesaScroll(double xoffset, double yoffset);
        void procesaTeclado(GLFWwindow* window, int key, int scancode, int action, int mods);
        bool capturaRaton();
        bool capturaTeclado();
    };

}

#endif // GUI_H