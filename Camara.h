//
// Created by pauli on 13/10/2026.
//

#ifndef P1_CAMARA_H
#define P1_CAMARA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace PAG {
    enum class TipoMovimientoCamara {
        ZOOM,
        PAN,
        TILT,
        DOLLY,
        CRANE,
        ORBIT
    };
    class Camara {
        private:
        glm::vec3 pos;
        glm::vec3 lookAt;
        glm::vec3 up;
        float fov;
        float znear;
        float zfar;
        float aspect;
        static Camara *instancia;
        Camara();
        ~Camara();


    public:

       glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix();
        static Camara &getInstancia();

        void setAspect(float a) { aspect = a; }
        float getFov() const { return fov; }


        void aplicarZoom(float delta);
        void aplicarPan(float angulo);
        void aplicarTilt(float angulo);
        void aplicarDolly(float despFrente, float despLateral);
        void aplicarCrane(float desplazamiento);
        void aplicarOrbit(float deltaLat, float deltaLon);





    };
}


#endif //P1_CAMARA_H