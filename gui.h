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
    };

}

#endif // GUI_H