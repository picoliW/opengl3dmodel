# **Modelo 3D com OpenGL**

## **Descrição**
Este projeto renderiza um modelo 3D interativo utilizando **OpenGL**, **GLFW**, **GLEW** e **GLM**. Foi desenvolvido para exibir um modelo de um **Audi R8 2017**, permitindo manipulação de câmera com o **mouse** e **teclado**.

---

## **Funcionalidades**
- Renderização de modelos 3D carregados a partir de arquivos `.obj`.
- Controle da câmera com o **mouse** (rotação).
- Controle adicional da posição e orientação usando o **teclado**.
- Shaders personalizáveis utilizando arquivos GLSL.
- Suporte a movimentação interativa para explorar o modelo.

---

## **Pré-requisitos**
Para compilar e executar o projeto, você precisará do seguinte:

### **Bibliotecas necessárias**
- **OpenGL**: Biblioteca para renderização gráfica.
- **GLFW**: Para criar janelas e capturar entradas do teclado e mouse.
- **GLEW**: Para carregar extensões do OpenGL.
- **GLM**: Biblioteca para manipulação de matrizes e vetores.
- **Assimp**: Para carregamento de modelos 3D no formato .obj.

---

## **Instruções de Instalação**

### **1. Instale as dependências**

#### **No Windows (via vcpkg)**

Se você estiver usando o `vcpkg`, pode instalar as dependências com os seguintes comandos:

```bash
vcpkg install glew glfw3 glm
```

#### **No Windows (via apt)**

Em sistemas baseados em Debian/Ubuntu, você pode instalar as dependências com:

```bash
sudo apt-get install libglew-dev libglfw3-dev libglm-dev
```

## Uso

### Controle do Modelo 3D
• Mouse: 
    
    Movimente o mouse para rotacionar a câmera em torno do modelo.

• Teclado:

    W/S: mover para frente/trás.

    A/D: mover para a esquerda/direita.
    
    Setas esquerda/direita: rotacionar o modelo no eixo Y.

## Estrutura do Projeto

```bash
/3dmodel
├── /shaders
│   ├── vertex_shader.glsl
│   └── fragment_shader.glsl
├── /models
│   └── Audi_R8_2017.obj
├── /src
│   ├── main.cpp
│   ├── ModelLoader.cpp
│   └── ModelLoader.h
└── CMakeLists.txt
```
