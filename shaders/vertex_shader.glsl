#version 330 core

layout (location = 0) in vec3 aPos;    // Posição dos vértices
layout (location = 1) in vec3 aNormal; // Normais (opcional)
layout (location = 2) in vec2 aTexCoords; // Coordenadas de textura

out vec2 TexCoords; // Envia coordenadas de textura para o fragment shader

uniform mat4 model;      // Matriz do modelo
uniform mat4 view;       // Matriz de visualização
uniform mat4 projection; // Matriz de projeção

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0); // Calcula a posição do vértice
    TexCoords = aTexCoords; // Passa as coordenadas de textura
}
