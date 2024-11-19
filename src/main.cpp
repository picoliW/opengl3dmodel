#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include "ModelLoader.h"

float lastX = 400, lastY = 300; // Posi��o inicial do mouse no centro da tela
float yaw = 0.0f, pitch = 0.0f; // �ngulos de rota��o do modelo
bool firstMouse = true;         // Para lidar com o primeiro movimento do mouse

glm::mat4 modelMatrix = glm::mat4(1.0f); // Matriz do modelo

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xOffset = xpos - lastX;
    float yOffset = lastY - ypos; // Inverter porque as coordenadas Y da tela aumentam para baixo
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // Sensibilidade do mouse
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw += xOffset;   // Rota��o em torno do eixo Y
    pitch += yOffset; // Rota��o em torno do eixo X

    // Limitar o pitch para evitar "virar de cabe�a para baixo"
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
}

// Callback para redimensionar a janela
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

glm::vec3 modelPosition(0.0f, 0.0f, 0.0f); // Posi��o do modelo
float rotationSpeed = 50.0f;               // Velocidade de rota��o (graus por segundo)
float movementSpeed = 2.5f;                // Velocidade de movimento (unidades por segundo)

void processInput(GLFWwindow* window, float deltaTime) {
    // Movimento para frente
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        modelPosition.z -= movementSpeed * deltaTime;

    // Movimento para tr�s
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        modelPosition.z += movementSpeed * deltaTime;

    // Movimento para a esquerda
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        modelPosition.x -= movementSpeed * deltaTime;

    // Movimento para a direita
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        modelPosition.x += movementSpeed * deltaTime;

    // Rota��o para a esquerda
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        yaw -= rotationSpeed * deltaTime;

    // Rota��o para a direita
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        yaw += rotationSpeed * deltaTime;
}


// Fun��o para compilar os shaders
GLuint loadShaderProgram(const char* vertexPath, const char* fragmentPath) {
    // Ler o c�digo do vertex shader
    std::string vertexCode;
    std::ifstream vShaderFile(vertexPath);
    std::stringstream vShaderStream;
    vShaderStream << vShaderFile.rdbuf();
    vertexCode = vShaderStream.str();

    // Ler o c�digo do fragment shader
    std::string fragmentCode;
    std::ifstream fShaderFile(fragmentPath);
    std::stringstream fShaderStream;
    fShaderStream << fShaderFile.rdbuf();
    fragmentCode = fShaderStream.str();

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // Compilar vertex shader
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    // Verificar erros de compila��o
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Compilar fragment shader
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    // Verificar erros de compila��o
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Vincular os shaders em um programa
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    // Verificar erros de linking
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // Deletar os shaders j� que est�o no programa
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;
}


int main() {
    // Inicializa��o do GLFW
    if (!glfwInit()) {
        std::cerr << "Falha ao inicializar o GLFW" << std::endl;
        return -1;
    }
    float lastFrame = 0.0f, deltaTime = 0.0f;

    // Configura��o do OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // Cria��o da janela
    GLFWwindow* window = glfwCreateWindow(800, 600, "Modelo Audi R8", nullptr, nullptr);
    if (!window) {
        std::cerr << "Falha ao criar a janela GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Inicializa��o do GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Falha ao inicializar o GLEW" << std::endl;
        return -1;
    }

    // Configura��o do viewport
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // Configura��o de callbacks
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Ativar o depth buffer
    glEnable(GL_DEPTH_TEST);

    // Carregar shaders
    GLuint shaderProgram = loadShaderProgram(
        "C:/Users/ledua/source/repos/3dmodel/shaders/vertex_shader.glsl",
        "C:/Users/ledua/source/repos/3dmodel/shaders/fragment_shader.glsl"
    );

    // Carregamento do modelo
    Model audiModel("C:/Users/ledua/source/repos/3dmodel/models/Audi_R8_2017.obj");

    // Loop de renderiza��o
    while (!glfwWindowShouldClose(window)) {
        // Calcular deltaTime
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Processar entradas
        processInput(window, deltaTime);

        // Limpar os buffers
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Atualizar matrizes
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), modelPosition);
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
        rotation = glm::rotate(rotation, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
        modelMatrix = translation * rotation;

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        glUseProgram(shaderProgram);

        GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
        GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
        GLuint projLoc = glGetUniformLocation(shaderProgram, "projection");

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

        // Renderizar o modelo
        audiModel.Draw(shaderProgram);

        // Trocar os buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    // Finaliza��o
    glfwTerminate();
    return 0;
}

