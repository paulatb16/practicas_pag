#ifndef imgui_h
#define imgui_h

#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include "Camara.h"
namespace PAG {

    class gui {
    private:
        static gui* instancia;
        gui();
        std::vector<std::string> mensajes; // para almacenar los mensajes que se van a sacar en la ventana de mensajes
        char nombreShader[128] = "";
        TipoMovimientoCamara movimientoActual = TipoMovimientoCamara::ZOOM;
        bool camaraActiva = false;

    public:
        virtual ~gui();
        static gui& getInstancia(); //igual que en renderer el puntero para acceder a la clase
        void inicializar(GLFWwindow* window); //funcion para inicializar en el bucle


        void render();
        void finalizar();


        bool capturaRaton();
        bool capturaTeclado();
        void addMensaje(const std::string& texto);
        TipoMovimientoCamara getMovimientoActual() const { return movimientoActual; }
        bool isCamaraActiva() const { return camaraActiva; }
    };

}

#endif // GUI_H