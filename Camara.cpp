#include "Camara.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace PAG {
    Camara* Camara::instancia = nullptr;

    Camara::Camara() {
        pos = glm::vec3(0.0f, 0.0f, 3.0f);
        lookAt = glm::vec3(0.0f, 0.0f, 0.0f);
        up = glm::vec3(0.0f, 1.0f, 0.0f);
        fov = glm::radians(45.0f);
        znear = 0.1f;
        zfar = 100.0f;
        aspect = 16.0f / 9.0f;
    }

    Camara::~Camara() = default;

    glm::mat4 Camara::getViewMatrix() {
        return glm::lookAt(pos, lookAt, up);
    }

    glm::mat4 Camara::getProjectionMatrix() {
        return glm::perspective(fov, aspect, znear, zfar);
    }

    Camara& Camara::getInstancia() {
        if (!instancia) {
            instancia = new Camara();
        }
        return *instancia;
    }

    void Camara::aplicarZoom(float nuevoFovRad) {
        fov = nuevoFovRad;
        if (fov < glm::radians(1.0f)) fov = glm::radians(1.0f);
        if (fov > glm::radians(179.0f)) fov = glm::radians(179.0f);
    }

    void Camara::aplicarPan(float angulo) {
        glm::vec3 direccion = lookAt - pos;
        glm::mat4 rotacion = glm::rotate(glm::mat4(1.0f), angulo, up);
        glm::vec4 nuevaDir = rotacion * glm::vec4(direccion, 0.0f);
        lookAt = pos + glm::vec3(nuevaDir);
    }

    void Camara::aplicarTilt(float angulo) {
        glm::vec3 direccion = lookAt - pos;
        glm::vec3 n = glm::normalize(direccion);
        glm::vec3 u = glm::normalize(glm::cross(n, up));
        
        glm::mat4 rotacion = glm::rotate(glm::mat4(1.0f), angulo, u);
        glm::vec4 nuevaDir = rotacion * glm::vec4(direccion, 0.0f);
        lookAt = pos + glm::vec3(nuevaDir);
    }

    void Camara::aplicarDolly(float desplazamiento) {
        glm::vec3 direccion = glm::normalize(lookAt - pos);
        pos += direccion * desplazamiento;
        lookAt += direccion * desplazamiento;
    }

    void Camara::aplicarCrane(float desplazamiento) {
        pos.y += desplazamiento;
        lookAt.y += desplazamiento;
    }

    void Camara::aplicarOrbit(float deltaLat, float deltaLon) {
        glm::vec3 r = pos - lookAt;
        float radio = glm::length(r);
        

        glm::mat4 rotLon = glm::rotate(glm::mat4(1.0f), deltaLon, up);
        glm::vec3 n = glm::normalize(r);
        glm::vec3 u = glm::normalize(glm::cross(n, up));
        glm::mat4 rotLat = glm::rotate(glm::mat4(1.0f), deltaLat, u);

        glm::vec4 nuevaPos = rotLon * rotLat * glm::vec4(r, 1.0f);
        pos = lookAt + glm::vec3(nuevaPos);
    }
}