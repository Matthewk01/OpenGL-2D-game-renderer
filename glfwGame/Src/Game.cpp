//
// Created by matej on 15/09/2019.
//

#include <GLFW/glfw3.h>
#include "Game.hpp"
#include <string>

Game::Game() : player(), renderer(1600, 800) {}

void Game::run() {
    gameInit();
    gameLoop();
}

void Game::gameInit() {
    // Shader
    renderer.initShader();

    // Textures
    char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

    for(int i = 0; i < 4; ++i) {
        ResourceLoader::createTexture("player" + std::string(1, digits[i]),
                                      "Textures/Player/adventurer-idle-2-0" + std::string(1, digits[i]) + ".png" ,
                                      true);
    }

    for(int i = 0; i < 5; ++i) {
        ResourceLoader::createTexture("playerAttack" + std::string(1, digits[i]),
                                      "Textures/Player/adventurer-attack1-0" + std::string(1, digits[i]) + ".png" ,
                                      true);
    }

    for(int i = 0; i < 6; ++i) {
        ResourceLoader::createTexture("playerRun" + std::string(1, digits[i]),
                                      "Textures/Player/adventurer-run-0" + std::string(1, digits[i]) + ".png" ,
                                      true);
    }

    ResourceLoader::createTexture("bg", "Textures/grassTile.jpg", false);
}

void Game::gameLoop() {
    const double CONST_FPS = 144;
    const double dt = 1.0 / CONST_FPS;
    double previous = glfwGetTime();
    double lag = 0.0;
    while (!glfwWindowShouldClose(renderer.getWindow())) {
        double current = glfwGetTime();
        double elapsed = current - previous;
        previous = current;
        lag += elapsed;

        // Poll for events and input
        processInput(renderer.getWindow());
        glfwPollEvents();

        // Clear
        renderer.clearWindow();

        while (lag >= dt) {
            update(dt);
            lag -= dt;
        }

        // Render object
        render();

        // Swap buffers
        glfwSwapBuffers(renderer.getWindow());
    }
}

void Game::processInput(GLFWwindow *window) {
    player.input = false;

    if (glfwGetKey(window, GLFW_KEY_D)) {
        player.input = true;
        player.xVel = 500;
        player.setWatchingRight(true);
        if(player.state != Player::State::RUNNING) {
            player.run();
        }
    } else if (glfwGetKey(window, GLFW_KEY_A)) {
        player.input = true;
        player.xVel = -500;
        player.setWatchingRight(false);
        if(player.state != Player::State::RUNNING) {
            player.run();
        }
    } else {
        if(player.state == Player::State::RUNNING) {
                player.resetState();
        }
    }

    if (glfwGetKey(window, GLFW_KEY_W)) {
//        player.yVel = -500;
    }
    if (glfwGetKey(window, GLFW_KEY_S)) {
//        player.yVel = 500;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE)) {
        player.input = true;
        if (!player.isJumping) {
            player.yVel = -400;
            player.isJumping = true;
        }
    }

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1)){
        player.input = true;
        if(player.state != Player::State::RUNNING && player.state != Player::State::ATTACKING) {
            player.attack();
        }
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
//    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
//        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
//        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
}

void Game::update(double time) {
    player.update(time);
}

void Game::render() {
    int tileSize = 50;
    for (int i = 0; i <= ((int) Renderer::getWidth() / tileSize * 2); ++i) {
        for (int j = 0; j <= ((int) Renderer::getHeight() / tileSize); ++j) {
            renderer.render(ResourceLoader::getTextureID("bg"), glm::vec2(i * tileSize + (-player.x/3), j * tileSize),
                            glm::vec2(tileSize, tileSize), false);
        }
    }

    std::stringstream ss;
    ss << player.getCurrentFrame();

    renderer.render(ResourceLoader::getTextureID(player.textureID[static_cast<int>(player.state)] + ss.str()), glm::vec2(player.x, player.y),
                    glm::vec2(200, 200), !player.isWatchingRight());
}

Game::~Game() {
    glfwDestroyWindow(renderer.getWindow());
    glfwTerminate();
}

