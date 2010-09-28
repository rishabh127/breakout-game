/**
*   game.h
*/

#ifndef GAME_H
#define GAME_H

#include "brick.h"
#include "paddle.h"
#include "color.h"

// constants
// paddle
#define PADDLE_DEFAULT_WIDTH        0.20
#define PADDLE_DEFAULT_HEIGHT       0.04
#define PADDLE_DEFAULT_COLOR_R      0.5f
#define PADDLE_DEFAULT_COLOR_G      0.5f
#define PADDLE_DEFAULT_COLOR_B      0.0f
#define PADDLE_DEFAULT_POS_X        -0.10
#define PADDLE_DEFAULT_POS_Y        -0.96
#define PADDLE_POWER				0.2
#define PADDLE_MAX_SPEED			0.005


class Game
{
    public:
        
        enum GameMode {
            PAUSED,
            RUNNING
        };

    
    private:

        enum GameMode mode;
        Paddle *paddle;
//    Ball ball;
//    List<Brick> bricks;

    public:
    
        Game();
        ~Game();
    
        void setMode(GameMode mode);
        GameMode getMode();
        GameMode swapMode();
        void setPaddle(Paddle *paddle);
        Paddle *getPaddle();

};


#endif

