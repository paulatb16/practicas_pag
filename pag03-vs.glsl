#version 410

layout (location = 0) in vec3 posicion;
layout (location = 1) in vec3 vColor;

out vec3 colorInterpolado;

void main ()
{
    colorInterpolado = vColor;
    gl_Position = vec4(posicion, 1.0);
}