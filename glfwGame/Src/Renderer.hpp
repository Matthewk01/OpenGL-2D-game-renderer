//
// Created by matej on 15/09/2019.
//

#ifndef GLFWTEST_RENDERER_HPP
#define GLFWTEST_RENDERER_HPP

#include <memory>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"


class Renderer {
public:
    Renderer(int widthT, int heightT);

    ~Renderer();

    void render(unsigned int texture, glm::vec2 pos, glm::vec2 scale, bool flipHorizontally);

    void clearWindow();

    GLFWwindow *getWindow() const;

    static float getWidth();

    static float getHeight();

    void initShader();

    const std::unique_ptr<Shader> &getShader() const;

private:
    std::unique_ptr<Shader> shader;
    unsigned int VAO;
    unsigned int VBO;
    static float width;
    static float height;
    GLFWwindow *window;

    static void framebuffer_size_callback(GLFWwindow *, int widthT, int heightT);
};


#endif //GLFWTEST_RENDERER_HPP
