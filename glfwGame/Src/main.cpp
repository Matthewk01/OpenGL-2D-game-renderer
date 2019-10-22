#include <iostream>
#include "Game.hpp"

int main() {
    std::cout << "glfwTest.exe started!" << std::endl;

    Game game;
    game.run();
    return 0;
}