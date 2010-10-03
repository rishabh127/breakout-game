/**
*   game.cpp
*/

#include "game.h"


Game::Game() {
    // set paddle
	this->paddle = new Paddle(PADDLE_DEFAULT_WIDTH, PADDLE_DEFAULT_HEIGHT,
		new Color(PADDLE_DEFAULT_COLOR_R, PADDLE_DEFAULT_COLOR_G,
		PADDLE_DEFAULT_COLOR_B));
	this->paddle->setPos(PADDLE_DEFAULT_POS_X, PADDLE_DEFAULT_POS_Y);

	// set ball
	this->ball = new Ball(BALL_DEFAULT_RADIUS, new Color(BALL_DEFAULT_COLOR_R,
		BALL_DEFAULT_COLOR_G, BALL_DEFAULT_COLOR_B));
	this->ball->setPos(BALL_DEFAULT_POS_X, BALL_DEFAULT_POS_Y);
	this->ball->setDir(BALL_DEFAULT_DIR_X, BALL_DEFAULT_DIR_Y);
	this->ball->setSpeed(BALL_DEFAULT_SPEED);

	// set game mode
	this->mode = PAUSED;

	// set colliding test
	this->isColliding = false;

	// set number of lifes
	this->life = NUM_OF_LIFES;
}

Game::~Game() {
    delete this->paddle;
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
	float yPos = this->paddle->getPos()->getY();
	float w = this->paddle->getW();
	float h = this->paddle->getH();

	// check colision -
	if (xPos < -COORD_RANGE) {
		xPos = -COORD_RANGE;
	} else if (xPos + w > COORD_RANGE) {
		xPos = COORD_RANGE - w;
	}

	// update position - fields
	paddle->getPos()->setX(xPos);

	// check colision - ball
	if (collide()) {
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

	// check colision - fields
	if (xPos - radius <= -COORD_RANGE) {
		xPos = -COORD_RANGE + radius;
		ball->getDir()->setX(-xDir);
	} else if (xPos + radius >= COORD_RANGE) {
		xPos = COORD_RANGE - radius;
		ball->getDir()->setX(-xDir);
	}
	if (yPos + radius >= COORD_RANGE) {
		yPos = COORD_RANGE - radius;
		ball->getDir()->setY(-yDir);
	}
	else if (yPos - radius <= -COORD_RANGE - radius) {
			printf("\nLOOSE\n");
	//		yPos = -COORD_RANGE + radius;
	//		ball->getDir()->setY(-yDir);
			//TODO loose life
	}

	// update position
	ball->getPos()->setX(xPos);
	ball->getPos()->setY(yPos);

	// check colision - paddle
	if(collide()) {
		if(!isColliding) {
			ball->getDir()->setY(-yDir);
			isColliding = true;
		}
	}
	else {
		isColliding = false;
	}
}

bool Game::collide() {
	float bX = ball->getPos()->getX();
	float bY = ball->getPos()->getY();
	float radius = ball->getRadius();
	float pX = paddle->getPos()->getX();
	float pY = paddle->getPos()->getY();
	float pH = paddle->getH();
	float pW = paddle->getW();
	bool collide = false;

	if (bY - radius < pY + pH) {
		float maxH = bX + radius;
		float minH = bX - radius;
		if ((maxH >= pX) && (maxH <= pX + pW)) {
			collide = true;
		} else if ((minH >= pX) && (minH <= pX + pW)) {
			collide = true;
		}
	}

	return collide;
}

/*
 * bricks
 */

//TODO brickGenerator() -> funcao que recebe uma quantidade de
// bricks, numero de linhas e preenche a lista de brick
// checar maxBricklines e maxNumBricks

/*
 * game options
 */

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

	// set game mode
	this->mode = PAUSED;

	// set colliding test
	this->isColliding = false;

	// set number of lifes
	this->life = NUM_OF_LIFES;
}
