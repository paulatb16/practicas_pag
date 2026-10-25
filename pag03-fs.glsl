#version 410 core

in vec3 vNormal;

out vec4 colorFragmento;

void main() {
  
    vec3 n = normalize(vNormal);
    vec3 colorNormal = n * 0.5 + vec3(0.5);

    colorFragmento = vec4(colorNormal, 1.0);
}