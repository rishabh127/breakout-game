/**
*   game.cpp
*/

#include "game.h"


Game::Game() {
    // set paddle
	this->paddle = new Paddle(PADDLE_DEFAULT_WIDTH, PADDLE_DEFAULT_HEIGHT,
		new Color(PADDLE_DEFAULT_COLOR_R, PADDLE_DEFAULT_COLOR_G,
		PADDLE_DEFAULT_COLOR_B));

	// set ball
	this->ball = new Ball(BALL_DEFAULT_RADIUS, new Color(BALL_DEFAULT_COLOR_R,
		BALL_DEFAULT_COLOR_G, BALL_DEFAULT_COLOR_B));

	// set bricks
	this->bricks = new std::list<Brick *>();

	reset();
}

void Game::reset() {
    // set paddle
	paddle->setW(PADDLE_DEFAULT_WIDTH);
	paddle->setH(PADDLE_DEFAULT_HEIGHT);
	paddle->getColor()->setR(PADDLE_DEFAULT_COLOR_R);
	paddle->getColor()->setG(PADDLE_DEFAULT_COLOR_G);
	paddle->getColor()->setB(PADDLE_DEFAULT_COLOR_B);
	paddle->setPos(PADDLE_DEFAULT_POS_X, PADDLE_DEFAULT_POS_Y);

	// set ball
	ball->setRadius(BALL_DEFAULT_RADIUS);
	ball->getColor()->setR(BALL_DEFAULT_COLOR_R);
	ball->getColor()->setG(BALL_DEFAULT_COLOR_G);
	ball->getColor()->setB(BALL_DEFAULT_COLOR_B);
	ball->setPos(BALL_DEFAULT_POS_X, BALL_DEFAULT_POS_Y);
	ball->setDir(BALL_DEFAULT_DIR_X, BALL_DEFAULT_DIR_Y);
	ball->setSpeed(BALL_DEFAULT_SPEED);

	// set bricks
	generateBricks(10, 10);

	// set game mode
	this->mode = PAUSED;

	// set colliding test
	this->isColliding = false;

	// set number of lifes
	this->life = NUM_OF_LIFES;
}


Game::~Game() {
    delete this->paddle;
    delete this->ball;
}


/*
 * game mode
 */

void Game::setMode(Game::GameMode mode) {
    this->mode = mode;
}

Game::GameMode Game::getMode() {
    return this->mode;
}

Game::GameMode Game::swapMode() {
	Game::GameMode newMode = (this->mode == PAUSED) ? RUNNING : PAUSED;
	this->mode = newMode;
	return newMode;
}


/*
 * paddle
 */

void Game::setPaddle(Paddle *paddle) {
    this->paddle = paddle;
}

Paddle *Game::getPaddle() {
    return this->paddle;
}

void Game::updatePaddle() {
	// calculate paddle position
	float xPos = this->paddle->getPos()->getX() + this->paddle->getSpeed();
	float w = this->paddle->getW();

	// check colision -
	if (xPos < 0) {
		xPos = 0;
	} else if (xPos + w > COORD_RANGE) {
		xPos = COORD_RANGE - w;
	}

	// update position - fields
	paddle->getPos()->setX(xPos);

	// check colision - ball
	if (paddle->collide(ball)) {
		if (!isColliding) {
			ball->getDir()->setY(
				- ball->getDir()->getY()
			);
			isColliding = true;
		}
	} else {
		isColliding = false;
	}
}


/*
 * ball
 */

void Game::setBall(Ball *ball) {
	this->ball = ball;
}

Ball *Game::getBall() {
	return this->ball;
}

void Game::updateBall() {
	// calculate ball position
	float xDir =  this->ball->getDir()->getX();
	float yDir = this->ball->getDir()->getY();
	float radius = this->ball->getRadius();
	float xPos = this->ball->getPos()->getX() +
			this->ball->getSpeed() * xDir;
	float yPos = this->ball->getPos()->getY() +
			this->ball->getSpeed() * yDir;

	// update position
	ball->getPos()->setX(xPos);
	ball->getPos()->setY(yPos);

	// check collision - fields
	if (xPos <= radius) {
		xPos = radius;
		ball->getDir()->setX(-xDir);
	} else if (xPos + radius >= COORD_RANGE) {
		xPos = COORD_RANGE - radius;
		ball->getDir()->setX(-xDir);
	}
	if (yPos + radius >= SCORE_POSITION) {
		yPos = COORD_RANGE - radius;
		ball->getDir()->setY(-yDir);
	}
	else if (yPos <= radius) {
			printf("\nLOOSE\n");
	//		yPos = -COORD_RANGE + radius;
			ball->getDir()->setY(-yDir);
			//TODO loose life
	}

	// check collision with paddle
	if(ball->collide(this->paddle)) {
		//if(!isColliding) {
			ball->getDir()->setY(-yDir);
			ball->getDir()->setX( ( (ball->getPos()->getX() - (paddle->getPos()->getX()
					+ paddle->getW()/2) ) / paddle->getW() ) );
			//ball->incSpeed(0.5 * fabs(paddle->getSpeed()) - PADDLE_POWER/4);
			if(ball->getSpeed() < BALL_MIN_SPEED) {
				ball->setSpeed(BALL_MIN_SPEED);
			}
//			isColliding = true;
//		}
//		return;
	}

	// check collision if bricks
//	if (ball->collide(*bricks->begin())) {
//		if (!isColliding) {
//			ball->getDir()->setY(-yDir);
			//ball->getDir()->setX(-xDir);
//			isColliding = true;
//		}
	}

//	else {
//		isColliding = false;
//	}

//}


/*
 * bricks
 */

//TODO brickGenerator() -> funcao que recebe uma quantidade de
// bricks, numero de linhas e preenche a lista de brick
// checar maxBricklines e maxNumBricks

void Game::setBricks(std::list<Brick *> *bricks) {
	this->bricks = bricks;
}

std::list<Brick *> *Game::getBricks() {
	return this->bricks;
}

void Game::generateBricks(int bricksPerLine, int numLines) {
	// sort life
	int breakLife = 3; //TODO sort life

	// set brick
	Brick *brick = new Brick(breakLife, 0.04, 0.04, new Color(0, 0.0, 1.0*life/10));
	brick->setH(0.04);
	brick->setW(0.1);
	brick->setPos(0.5, 0.5);
	this->bricks->push_back(brick);

	int life = 6; //TODO sort life
	brick = new Brick(breakLife, 0.04, 0.04, new Color(0, 0.0, 1.0*life/10.0));
	brick->setH(0.04);
	brick->setW(0.1);
	brick->setPos(0.546, 0.536);
	this->bricks->push_back(brick);

	life = 6; //TODO sort life
	brick = new Brick(breakLife, 0.04, 0.04, new Color(0, 0.0, 1.0*life/10.0));
	brick->setH(0.04);
	brick->setW(0.1);
	brick->setPos(0.45, 0.536);
	this->bricks->push_back(brick);
}

/*
 * game options
 */


