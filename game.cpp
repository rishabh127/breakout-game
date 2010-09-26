/**
*   game.cpp
*/

#include "game.h"


Game::Game() {
    // set paddle
    this->paddle = new Paddle(
        PADDLE_DEFAULT_WIDTH, 
        PADDLE_DEFAULT_HEIGHT,
        new Color(PADDLE_DEFAULT_COLOR_R, 
                  PADDLE_DEFAULT_COLOR_G,
                  PADDLE_DEFAULT_COLOR_B)
    );
    this->paddle->setPos(new Vector<float>(
        PADDLE_DEFAULT_POS_X, 
        PADDLE_DEFAULT_POS_Y)
    );

    // set game mode
    this->mode = PAUSED;
}

Game::~Game() {
    delete this->paddle;
}

void Game::setMode(Game::GameMode mode) {
    this->mode = mode;
}

Game::GameMode Game::getMode() {
    return this->mode;
}

void Game::setPaddle(Paddle *paddle) {
    this->paddle = paddle;
}

Paddle *Game::getPaddle() {
    return this->paddle;
}

