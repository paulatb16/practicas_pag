#version 410

layout (location = 0) in vec3 posicion;
layout (location = 1) in vec3 vColor;
uniform mat4 u_matrizMVP;

out vec3 colorInterpolado;

void main ()
{
  colorInterpolado = vColor;
      gl_Position = u_matrizMVP * vec4(posicion, 1.0);
}