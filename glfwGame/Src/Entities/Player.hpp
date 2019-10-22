//
// Created by matej on 15/09/2019.
//

#ifndef GLFWTEST_PLAYER_HPP
#define GLFWTEST_PLAYER_HPP


#include <string>

class Player {
public:
    enum class State : short {
        IDLE, ATTACKING, RUNNING
    };

    Player();

    bool input;
    float x;
    float y;
    float xVel;
    float yVel;
    bool isJumping;
    std::string textureID[3];
    State state;

    void update(double time);

    int getCurrentFrame() const;

    bool isWatchingRight() const;

    void setWatchingRight(bool watchingRight);

    void attack();

    void run();

    void resetState();

private:
    int counter;
    int currentFrame;
    int framesCount;
    int frameSpeed;
    bool watchingRight;
};


#endif //GLFWTEST_PLAYER_HPP
