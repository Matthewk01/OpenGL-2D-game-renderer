//
// Created by matej on 15/09/2019.
//

#ifndef GLFWTEST_GAME_HPP
#define GLFWTEST_GAME_HPP

#include "ResourceLoader.hpp"
#include "Shader.hpp"
#include "Renderer.hpp"
#include "Entities/Player.hpp"


class Game {
public:
    Game();

    ~Game();

    void run();

private:
    Player player;
    Renderer renderer;

    void gameInit();

    void gameLoop();

    void processInput(GLFWwindow *window);

    void update(double time);

    void render();
};


#endif //GLFWTEST_GAME_HPP
