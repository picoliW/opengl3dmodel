#version 330 core

layout (location = 0) in vec3 aPos;    // Posi��o dos v�rtices
layout (location = 1) in vec3 aNormal; // Normais (opcional)
layout (location = 2) in vec2 aTexCoords; // Coordenadas de textura

out vec2 TexCoords; // Envia coordenadas de textura para o fragment shader

uniform mat4 model;      // Matriz do modelo
uniform mat4 view;       // Matriz de visualiza��o
uniform mat4 projection; // Matriz de proje��o

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0); // Calcula a posi��o do v�rtice
    TexCoords = aTexCoords; // Passa as coordenadas de textura
}
