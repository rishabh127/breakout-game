/**
*   game.h
*/

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <list>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "brick.h"
#include "paddle.h"
#include "ball.h"


// constants
#define WINDOW_INIT_POSITION_X      10
#define WINDOW_INIT_POSITION_Y      10
#define WINDOW_INIT_WIDTH           720
#define WINDOW_INIT_HEIGHT          640
#define WINDOW_DEFAULT_COLOR_R      0.0f
#define WINDOW_DEFAULT_COLOR_G      0.0f
#define WINDOW_DEFAULT_COLOR_B      0.0f
#define WINDOW_TITLE                "Breakout"
#define TIMER_MSECS                 10
#define COORD_RANGE                 1.0

// game options
#define NUM_OF_LIFES                 5
#define NUM_OF_LEVELS				 10
#define INITIAL_NUM_BRICKS			 4

// paddle
#define PADDLE_DEFAULT_WIDTH        0.135f
#define PADDLE_DEFAULT_HEIGHT       0.018f
#define PADDLE_DEFAULT_COLOR_R      0.5f
#define PADDLE_DEFAULT_COLOR_G      0.5f
#define PADDLE_DEFAULT_COLOR_B      0.0f
#define PADDLE_DEFAULT_POS_X        0.5 - PADDLE_DEFAULT_WIDTH / 2
#define PADDLE_DEFAULT_POS_Y        0.007
#define PADDLE_POWER				0.050

// ball
#define BALL_DEFAULT_RADIUS        0.012f
#define BALL_DEFAULT_COLOR_R       0.0f
#define BALL_DEFAULT_COLOR_G       0.0f
#define BALL_DEFAULT_COLOR_B       1.0f
#define BALL_DEFAULT_DIR_X         0.05
#define BALL_DEFAULT_DIR_Y         0.3
#define BALL_DEFAULT_POS_X         PADDLE_DEFAULT_POS_X + PADDLE_DEFAULT_WIDTH/2
#define BALL_DEFAULT_POS_Y         PADDLE_DEFAULT_POS_Y + PADDLE_DEFAULT_HEIGHT + BALL_DEFAULT_RADIUS + 0.001
#define BALL_DEFAULT_SPEED		   0.025
#define BALL_MIN_SPEED			   0.005

// bricks
#define BRICK1_COLOR_R      		  0.0f
#define BRICK1_COLOR_G      		  0.0f
#define BRICK1_COLOR_B      		  0.6f
#define BRICK2_COLOR_R      		  0.0f
#define BRICK2_COLOR_G      		  0.6f
#define BRICK2_COLOR_B      		  0.0f
#define BRICK3_COLOR_R      		  0.6f
#define BRICK3_COLOR_G      		  0.0f
#define BRICK3_COLOR_B      		  0.0f
#define BRICK_SPACE				  	  0.007f
#define BRICKS_TOP_POS_Y		  	  0.8f
#define BRICKS_HEIGHT       		  0.03f

// score
#define SCORE_POSITION			   	0.92f
#define SCORE_DEFAULT_COLOR_R       0.0f
#define SCORE_DEFAULT_COLOR_G       0.9f
#define SCORE_DEFAULT_COLOR_B       0.0f


class Game
{
    public:
        
        enum GameMode {
            PAUSED,
            RUNNING,
            STARTING,
            GAME_OVER,
            WIN,
            FINISHED
        };
    
    private:

        enum GameMode mode;
        Paddle *paddle;
        Ball *ball;
        std::list<Brick *> *bricks;
        int bricksTotal;
        unsigned long timer;

        bool newGame;
        bool isCollidingPaddle;
        int life;
        int score;
        int totalScore;
        int level;

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

        void generateBricks(int bricksPerLine, int numLines, float bricksHeight);
        void setBricks(std::list<Brick *> *bricks);
        std::list<Brick *> *getBricks();
        int getTotalBricks();

        int getLife();
        int getScore();
        int getTotalScore();
        int getLevel();
        unsigned long getTimer();
        void addTimer(int t);

        void reset();
        void newLevel();
        void lose();
        void hit(std::list<Brick *>::iterator *bricksItr);
};


#endif

