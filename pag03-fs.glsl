#version 410 core

in salidaVS {
    vec3 posicionV;
    vec3 normalV;
    vec2 texCoordV;
} entrada;

struct Material {
    vec4 ambiente;
    vec4 difuso;
    vec4 especular;
    float brillo;
};
uniform Material uMaterial;

subroutine vec4 fCalcularColor();

subroutine uniform fCalcularColor uMetodoColorElegido;

//alambre
subroutine (fCalcularColor)
vec4 colorAlambre() {
    return vec4(1.0, 0.0, 0.0, 1.0); 
}

//modo solido
subroutine (fCalcularColor)
vec4 colorSolido() {
    return uMaterial.difuso;
}

out vec4 colorFragmento;

void main() {

    colorFragmento = uMetodoColorElegido();
}
