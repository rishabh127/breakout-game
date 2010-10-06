/**
*   game.h
*/

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <list>
#include "brick.h"
#include "paddle.h"
#include "ball.h"


// constants
#define WINDOW_INIT_POSITION_X      10
#define WINDOW_INIT_POSITION_Y      10
#define WINDOW_INIT_WIDTH           820
#define WINDOW_INIT_HEIGHT          680
#define WINDOW_DEFAULT_COLOR_R      1.0f
#define WINDOW_DEFAULT_COLOR_G      1.0f
#define WINDOW_DEFAULT_COLOR_B      1.0f
#define WINDOW_TITLE                "Breakout"
#define TIMER_MSECS                 33
#define COORD_RANGE                 1.0

// game
#define NUM_OF_LIFES                 3

// paddle
#define PADDLE_DEFAULT_WIDTH        0.24f
#define PADDLE_DEFAULT_HEIGHT       0.04f
#define PADDLE_DEFAULT_COLOR_R      0.5f
#define PADDLE_DEFAULT_COLOR_G      0.5f
#define PADDLE_DEFAULT_COLOR_B      0.0f
#define PADDLE_DEFAULT_POS_X        -0.10
#define PADDLE_DEFAULT_POS_Y        -1.0
#define PADDLE_POWER				0.15

// ball
#define BALL_DEFAULT_RADIUS        0.025f
#define BALL_DEFAULT_COLOR_R       0.0f
#define BALL_DEFAULT_COLOR_G       0.0f
#define BALL_DEFAULT_COLOR_B       0.0f
#define BALL_DEFAULT_DIR_X         0.0001
#define BALL_DEFAULT_DIR_Y         0.16
#define BALL_DEFAULT_POS_X         PADDLE_DEFAULT_POS_X + PADDLE_DEFAULT_WIDTH/2
#define BALL_DEFAULT_POS_Y         PADDLE_DEFAULT_POS_Y + PADDLE_DEFAULT_HEIGHT + BALL_DEFAULT_RADIUS + 0.001
#define BALL_DEFAULT_SPEED		   0.2
#define BALL_MIN_SPEED			   0.06

// bricks
//TODO


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
        Ball *ball;
        std::list<Brick *> *bricks;

        bool isColliding;
        int life;

    public:
    
        Game();
        ~Game();
    
        void setMode(GameMode mode);
        GameMode getMode();
        GameMode swapMode();

        void setPaddle(Paddle *paddle);
        Paddle *getPaddle();
        void updatePaddle();

        void setBall(Ball *ball);
        Ball *getBall();
        void updateBall();

        void generateBricks(int bricksPerLine, int numLines);
        void setBricks(std::list<Brick *> *bricks);
        std::list<Brick *> *getBricks();

        void reset();

};


#endif

