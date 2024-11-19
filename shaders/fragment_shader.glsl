#version 330 core

in vec2 TexCoords; // Coordenadas de textura recebidas do vertex shader
out vec4 FragColor; // Cor final do fragmento

uniform sampler2D texture_diffuse; // Textura aplicada ao modelo

void main() {
    FragColor = texture(texture_diffuse, TexCoords); // Aplica a textura
    // Se não tiver textura, use uma cor fixa:
    // FragColor = vec4(1.0, 0.5, 0.3, 1.0); // Cor RGB com alpha = 1.0
}
