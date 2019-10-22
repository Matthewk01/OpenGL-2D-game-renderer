//
// Created by matej on 15/09/2019.
//

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.hpp"
#include "Renderer.hpp"

Renderer::Renderer(int widthT, int heightT) : shader(nullptr) {
    Renderer::width = widthT;
    Renderer::height = heightT;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *windowTmp = glfwCreateWindow(width, height, "LearnOpenGL", nullptr, nullptr);
    if (!windowTmp) {
        std::cout << "GLFW error!" << std::endl;
        glfwTerminate();
    }
    this->window = windowTmp;

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "GLAD load error!";
    }
    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(window, Renderer::framebuffer_size_callback);

    // Triangle
//    float vertices[] = {
//            // positions      // colors        // texture coords
//            0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // top right
//            1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,   // bottom right
//            0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,   // bottom left
//
//            0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,    // top left
//            1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
//            1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f
//    };

    float vertices[] = {
            // positions      // colors        // texture coords
            0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // top right
            1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,   // bottom right
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,   // bottom left
            1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,    // top left
    };


    unsigned int indices[] = {
            0, 1, 2, // first triangle
            0, 1, 3 // second triangle
    };

    // Create VAO
    unsigned int VAOtmp;
    glGenVertexArrays(1, &VAOtmp);

    // Create VBO
    unsigned int VBOtmp;
    glGenBuffers(1, &VBOtmp);

    // Create EBO
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    // HOW TO INTERPRET DATA
    glBindVertexArray(VAOtmp);
    glBindBuffer(GL_ARRAY_BUFFER, VBOtmp);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    this->VAO = VAOtmp;
    this->VBO = VBOtmp;
}

void Renderer::framebuffer_size_callback(GLFWwindow *, int widthT, int heightT) {
    glViewport(0, 0, width, height);
    Renderer::width = widthT;
    Renderer::height = heightT;
}

GLFWwindow *Renderer::getWindow() const {
    return window;
}

void Renderer::render(unsigned int texture, glm::vec2 pos, glm::vec2 scale, bool flipHorizontally) {
    shader->use();

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    if (flipHorizontally) {
        model = glm::translate(model, glm::vec3(pos.x + scale.x, pos.y, 0.0f));
        model = glm::scale(model, glm::vec3(scale.x, scale.y, 0.0f));
        model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
    } else {
        model = glm::translate(model, glm::vec3(pos.x, pos.y, 0.0f));
        model = glm::scale(model, glm::vec3(scale.x, scale.y, 0.0f));
    }
    projection = glm::ortho(0.0f, Renderer::getWidth(), Renderer::getHeight(), 0.0f, -1.0f, 1.0f);

    shader->setTransform("model", model);
    shader->setTransform("view", view);
    shader->setTransform("projection", projection);

    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

float Renderer::width{};

float Renderer::height{};

float Renderer::getWidth() {
    return width;
}

float Renderer::getHeight() {
    return height;
}

void Renderer::clearWindow() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::initShader() {
    if (!this->shader) {
        shader = std::make_unique<Shader>("Shaders/vertexShader.vs",
                                          "Shaders/fragmentShader.fs");
    }
    shader->use();
}

const std::unique_ptr<Shader> &Renderer::getShader() const {
    return shader;
}
