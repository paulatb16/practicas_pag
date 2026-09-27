#include <iostream>
// IMPORTANTE: El include de GLAD debe estar siempre ANTES de el de GLFW

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include "Renderer.h"


#include "gui.h"

float r = 0.6, g = 0.6, b = 0.6;

// - Esta función callback será llamada cuando GLFW produzca algún error

void error_callback(int errno, const char *desc) {
    std::string aux(desc);

    std::cout << "Error de GLFW número " << errno << ": " << aux << std::endl;
}

// - Esta función callback será llamada cada vez que el área de dibujo

// OpenGL deba ser redibujada.

void window_refresh_callback(GLFWwindow *window) {
    PAG::Renderer::getInstancia().refrescar();

    // - GLFW usa un doble buffer para que no haya parpadeo. Esta orden

    // intercambia el buffer back (que se ha estado dibujando) por el

    // que se mostraba hasta ahora front. Debe ser la última orden de

    // este callback

    glfwSwapBuffers(window);

    std::cout << "Refresh callback called" << std::endl;
}

// - Esta función callback será llamada cada vez que se cambie el tamaño

// del área de dibujo OpenGL.

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    PAG::Renderer::getInstancia().viewport(0,0,width,height);

    std::cout << "Resize callback called" << std::endl;
}

// - Esta función callback será llamada cada vez que se pulse una tecla

// dirigida al área de dibujo OpenGL.

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    std::cout << "Key callback called" << std::endl;
}

// - Esta función callback será llamada cada vez que se pulse algún botón

// del ratón sobre el área de dibujo OpenGL.

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        std::cout << "Pulsado el botón: " << button << std::endl;
    } else if (action == GLFW_RELEASE) {
        std::cout << "Soltado el botón: " << button << std::endl;
    }
}

// - Esta función callback será llamada cada vez que se mueva la rueda

// del ratón sobre el área de dibujo OpenGL.

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    std::cout << "Movida la rueda del ratón " << xoffset

            << " Unidades en horizontal y " << yoffset

            << " unidades en vertical" << std::endl;


    //cambiamos el color si se mueve la rueda hacia arriba haciendolo más negro, y hacia abajo más blanco

    if (yoffset > 0) {
        r = r + 0.01;

        g = g + 0.01;

        b = b + 0.01;
    } else if (yoffset < 0) {
        r = r - 0.01;

        g = g - 0.01;

        b = b - 0.01;
    }

    //para la X voy a hacer un cambio que no sea totalmente uniforme en los 3 colores sino que cada uno cambie con un valor distinto

    if (xoffset > 0) {
        r = r + 0.05;

        g = g + 0.02;

        b = b + 0.06;
    }

    if (xoffset < 0) {
        r = r - 0.07;

        g = g - 0.03;

        b = b + 0.09;
    }


    // si se pasa del 1, se quedará en 1, y si se va a pasar del 0 por abajo, se quedará en 0, para no salir de los

    // límites de los colores

    if (r > 1.0f) {
        r = 1.0f;
        g = 1.0f;
        b = 1.0f;
    }

    if (r < 0.0f) {
        r = 0.0f;
        g = 0.0f;
        b = 0.0f;
    }

    PAG::Renderer::getInstancia().ClearColor(r, g, b, 1.0f);
}


int main() {
    std::cout << "Starting Application PAG - Prueba 01" << std::endl;

    // - Este callback hay que registrarlo ANTES de llamar a glfwInit

    glfwSetErrorCallback((GLFWerrorfun) error_callback);


    if (glfwInit() != GLFW_TRUE) {
        std::cout << "Failed to initialize GLFW" << std::endl;

        return -1;
    }

    // - Definimos las características que queremos que tenga el contexto gráfico

    // OpenGL de la ventana que vamos a crear. Por ejemplo, el número de muestras o el

    // modo Core Profile.

    glfwWindowHint(GLFW_SAMPLES, 4); // - Activa antialiasing con 4 muestras.

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // - Esta y las 2

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // siguientes activan un contexto

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // OpenGL Core Profile 4.3.

    // - Definimos el puntero para guardar la dirección de la ventana de la aplicación y

    // la creamos

    GLFWwindow *window;

    // - Tamaño, título de la ventana, en ventana y no en pantalla completa,

    // sin compartir recursos con otras ventanas.

    window = glfwCreateWindow(1024, 576, "PAG Introduction", nullptr, nullptr);

    // - Comprobamos si la creación de la ventana ha tenido éxito.

    if (window == nullptr) {
        std::cout << "Failed to open GLFW window" << std::endl;

        glfwTerminate(); // - Liberamos los recursos que ocupaba GLFW.

        return -2;
    }


    // - Hace que el contexto OpenGL asociado a la ventana que acabamos de crear pase a

    // ser el contexto actual de OpenGL para las siguientes llamadas a la biblioteca

    glfwMakeContextCurrent(window);

    // - Ahora inicializamos GLAD.

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "GLAD initialization failed" << std::endl;

        glfwDestroyWindow(window); // - Liberamos los recursos que ocupaba GLFW.

        window = nullptr;

        glfwTerminate();

        return -3;
    }



    // - Interrogamos a OpenGL para que nos informe de las propiedades del contexto

    // 3D construido.

    std::cout << PAG::Renderer::getInstancia().getRendererInfo()<< std::endl

            << PAG::Renderer::getInstancia().getVendorInfo() << std::endl

            << PAG::Renderer::getInstancia().getVersionInfo() << std::endl

            << PAG::Renderer::getInstancia().getShadingLanguageVersionInfo() << std::endl;


    // - Registramos los callbacks que responderán a los eventos principales

    glfwSetWindowRefreshCallback(window, window_refresh_callback);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetKeyCallback(window, key_callback);

    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glfwSetScrollCallback(window, scroll_callback);


    // - Le decimos a OpenGL que tenga en cuenta la profundidad a la hora de

    // dibujar.

    // No tiene por qué ejecutarse en cada paso por el ciclo de eventos.

    PAG::Renderer::getInstancia().enable();
    PAG::gui::getInstancia().inicializar(window);

    // - Ciclo de eventos de la aplicación. La condición de parada es que la

    // ventana principal deba cerrarse, por ejemplo, si el usuario pulsa el

    // botón de cerrar la ventana (la X).

    while (!glfwWindowShouldClose(window)) {
        // - Obtiene y organiza los eventos pendientes, tales como pulsaciones

        // de teclas o de ratón, etc. Siempre al final de cada iteración del

        // ciclo de eventos y después de glfwSwapBuffers ( window );
        PAG::Renderer::getInstancia().refrescar(); //para que se pinte VA ANTES QUE RENDER DE GUI O SINO SE SUPOERPONE
        PAG::gui::getInstancia().render(); // crear las ventanas de imgui

        glfwSwapBuffers(window); //intercambio de ventanas para que se muestre el nuevo color

        glfwPollEvents();


    }


    std::cout << "Finishing application pag prueba" << std::endl;
    PAG::gui::getInstancia().finalizar();
    glfwDestroyWindow ( window );
    window = nullptr;

    glfwTerminate(); // - Liberamos los recursos que ocupaba GLFW.


    return 0;
}
