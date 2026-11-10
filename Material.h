//
// Created by pauli on 10/11/2026.
//

#ifndef P1_MATERIAL_H
#define P1_MATERIAL_H
#include <glm/glm.hpp>

namespace PAG {
    class Material {
    private:
        glm::vec4 ambiente;
        glm::vec4 difuso;
        glm::vec4 especular;
        float brillo;

    public:

        Material(
            const glm::vec4& amb = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            const glm::vec4& dif = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            const glm::vec4& esp = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            float brill = 1.0f
        ) : ambiente(amb), difuso(dif), especular(esp), brillo(brill) {}
        ~Material() = default;
        glm::vec4 getAmbiente() const { return ambiente; }
        glm::vec4 getDifuso() const { return difuso; }
        glm::vec4 getEspecular() const { return especular; }
        float getbrillo() const { return brillo; }

        void setAmbiente(const glm::vec4& amb) { ambiente = amb; }
        void setDifuso(const glm::vec4& dif) { difuso = dif; }
        void setEspecular(const glm::vec4& esp) { especular = esp; }
        void setbrillo(float bri) { brillo= bri; }
    };
}


#endif //P1_MATERIAL_H
