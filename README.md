# PRACTICA 1 PAG

### Explicación de la práctica 
He implementado el cambio del color con la rueda del ratón, haciendo que cuando se mueva la rueda se vaya sumando un número (en este caso he puesto que de arriba a abajo sea  el mismo para los tres colores y hacia los lados sean números distintos). Esta parte la he implementado en la función de callback scroll_callback. A continuación he añadido en el while del main en el que se gestionan los eventos glClearColor(r,g,b,1) poniendo los colores como constantes globales, y  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT). Por último al final de este while la función para el intercambio de ventanas (glfwSwapBuffers ( window )) para que se muestre el nuevo color pintado y glfwPollEvents (). 

### Respuesta reflexión

Para poder llamar a los métodos de la nueva clase y usarlos como callbacks, primero debemos crear un objeto de nuestra nueva clase. A continuación en la misma clase crearemos una función que, pasandole este objeto, llame a nuestra función nueva de refrescar ventana, usándola así como función puente. El punto está en que esta función puente debe ser estática, así C++ nos permitirá usarla en el registro del callback, quedando así:

*glfwSetWindowRefreshCallback ( window, PAG::Renderer::funcionpuente)*


