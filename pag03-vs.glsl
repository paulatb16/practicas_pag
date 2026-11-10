#version 410 core

layout (location = 0) in vec3 posicion;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

uniform mat4 u_matrizModel;
uniform mat4 u_matrizView;
uniform mat4 u_matrizProjection;
uniform mat4 u_matrizNormal;

out salidaVS {
    vec3 posicionV;
    vec3 normalV;
    vec2 texCoordV;
} salida;

void main() {
    salida.normalV = mat3(u_matrizNormal) * normal;
    salida.posicionV = vec3(u_matrizModel * vec4(posicion, 1.0));
    salida.texCoordV = texCoord;
    gl_Position = u_matrizProjection * u_matrizView * u_matrizModel * vec4(posicion, 1.0);
}