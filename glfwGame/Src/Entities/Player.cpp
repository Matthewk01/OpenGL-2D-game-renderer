//
// Created by matej on 15/09/2019.
//

#include "Player.hpp"

Player::Player() : input(false), x(0), y(0), xVel(0), yVel(0), isJumping(false), textureID{"player", "playerAttack", "playerRun"}, state(State::IDLE), counter(0), currentFrame(0), framesCount(4), frameSpeed(25), watchingRight(true){

}

void Player::update(double time) {
    if(counter % frameSpeed == 0) {
        currentFrame = (currentFrame + 1) % framesCount;
        counter = 0;
        if(currentFrame == 0 && !input) {
            resetState();
        }
    }
    ++counter;

    this->x += this->xVel * time;
    this->y += this->yVel * time;

    // Acceleration
    if(xVel > 5) {
        xVel -= 2000 * time;
    } else if(xVel < -5) {
        xVel += 2000 * time;
    } else {
        xVel = 0;
    }

    yVel += 1000 * time;

    if(yVel >= 400) {
        yVel = 400;
        isJumping = false;
    }

    if(this->y >= 200) {
        y = 200;
        yVel = 0;
    }
}

int Player::getCurrentFrame() const {
    return currentFrame;
}

bool Player::isWatchingRight() const {
    return watchingRight;
}

void Player::setWatchingRight(bool watchingRight) {
    Player::watchingRight = watchingRight;
}

void Player::attack() {
    this->framesCount = 5;
    this->currentFrame = 0;
    this->frameSpeed = 10;
    this->state = State::ATTACKING;
}

void Player::run() {
    this->framesCount = 6;
    this->currentFrame = 0;
    this->frameSpeed = 20;
    this->state = State::RUNNING;
}

void Player::resetState() {
    framesCount = 4;
    state = State::IDLE;
    currentFrame = 0;
    frameSpeed = 40;
}


