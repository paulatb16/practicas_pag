#version 410 core

layout (location = 0) in vec3 posicion;
layout (location = 1) in vec3 normal;

uniform mat4 u_matrizModel;
uniform mat4 u_matrizView;
uniform mat4 u_matrizProjection;

out vec3 vNormal;

void main() {
    vNormal = mat3(transpose(inverse(u_matrizModel))) * normal;
    
    gl_Position = u_matrizProjection * u_matrizView * u_matrizModel * vec4(posicion, 1.0);
}