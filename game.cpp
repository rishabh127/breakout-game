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
	this->life = NUM_OF_LIFES;
	this->level = 0;
	this->totalScore = 0;
	this->timer = 0;
	newLevel();
}

void Game::newLevel() {
	level++;

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
	generateBricks(INITIAL_NUM_BRICKS + level-1,
		INITIAL_NUM_BRICKS + level-1, BRICKS_HEIGHT);

	bricksTotal = bricks->size();

	this->newGame = true;
	this->mode = PAUSED;
	this->isCollidingPaddle = false;
	this->score = 0;
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
	if(mode == PAUSED && newGame) {
		newGame = false;
		mode = STARTING;
		return mode;
	}
	Game::GameMode newMode = (this->mode != RUNNING) ? RUNNING : PAUSED;
	mode = newMode;
	return mode;
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
	if (ball->collide((Entity *)paddle)) {
		if (!isCollidingPaddle) {
			ball->getDir()->setY(
				- ball->getDir()->getY()
			);
			isCollidingPaddle = true;
		}
	} else {
		isCollidingPaddle = false;
	}

	// starting mode
	if(mode == STARTING) {
		ball->getPos()->setX(paddle->getPos()->getX() + paddle->getW() / 2);
		ball->getPos()->setY(paddle->getPos()->getY() + paddle->getH()
				+ ball->getRadius() + 0.001);
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
	bool collide;
	std::list<Brick *>::iterator bricksItr;

	// starting mode
	if(mode == STARTING) {
		ball->getPos()->setX(paddle->getPos()->getX() + paddle->getW() / 2);
		ball->getPos()->setY(paddle->getPos()->getY() + paddle->getH()
				+ ball->getRadius() + 0.001);
		return;
	}

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
		lose();
	}

	// check collision with paddle
	if(ball->collide((Entity *)paddle)) {
		if(!isCollidingPaddle) {
			ball->getDir()->setY(-yDir);
			ball->getDir()->setX( ( (ball->getPos()->getX() - (paddle->getPos()->getX()
					+ paddle->getW()/2) ) / paddle->getW() ) );
			//ball->incSpeed(0.5 * fabs(paddle->getSpeed()) - PADDLE_POWER/4);
			if(ball->getSpeed() < BALL_MIN_SPEED) {
				ball->setSpeed(BALL_MIN_SPEED);
			}
			isCollidingPaddle = true;
		}
	}
	else {
		isCollidingPaddle = true;
	}

	// check collision if bricks
	collide = false;
	for(bricksItr = bricks->begin(); bricksItr != bricks->end(); bricksItr++) {
		if (ball->collide(*bricksItr)) {
			ball->getDir()->setY(-yDir);
			collide = true;
			break;
		}
	}
	if(collide) {
		hit(&bricksItr);
	}
}


/*
 * bricks
 */

void Game::setBricks(std::list<Brick *> *bricks) {
	this->bricks = bricks;
}

std::list<Brick *> *Game::getBricks() {
	return this->bricks;
}

void Game::generateBricks(int bricksPerLine, int numLines, float bricksHeight) {
	float brickW;
	float brickPosX = BRICK_SPACE;
	float brickPosY = BRICKS_TOP_POS_Y;

	bricks->clear();
	brickW = ((float)COORD_RANGE-BRICK_SPACE)/(float)bricksPerLine;
	for(int l=1; l<=numLines; l++) {
		for(int i=1; i<=bricksPerLine; i++) {
			// random life
			srand(time(NULL)*l*i);
			int brickLife = (rand()%3) + 1;

			Color *brickColor = NULL;
			switch(brickLife) {
			case 1:
				brickColor = new Color(BRICK1_COLOR_R, BRICK1_COLOR_G, BRICK1_COLOR_B);
				break;
			case 2:
				brickColor = new Color(BRICK2_COLOR_R, BRICK2_COLOR_G, BRICK2_COLOR_B);
				break;
			case 3:
				brickColor = new Color(BRICK3_COLOR_R, BRICK3_COLOR_G, BRICK3_COLOR_B);
				break;
			}
			// set brick
			Brick *brick = new Brick(brickLife, brickW-BRICK_SPACE, bricksHeight, brickColor);
			brick->setPos(brickPosX, brickPosY);
			this->bricks->push_back(brick);
			brickPosX += brickW;
		}
		brickPosY -= (bricksHeight + BRICK_SPACE);
		if(l%2) {
			bricksPerLine--;
			brickPosX = BRICK_SPACE + brickW/2;
		}
		else {
			bricksPerLine++;
			brickPosX = BRICK_SPACE;
		}
	}
}

int Game::getTotalBricks() {
	return this->bricksTotal;
}


/*
 * game status
 */

int Game::getLife() {
	return this->life;
}

int Game::getScore() {
	return this->score;
}

int Game::getTotalScore() {
	return this->totalScore;
}

int Game::getLevel() {
	return this->level;
}

unsigned long Game::getTimer() {
	return this->timer;
}

void Game::addTimer(int t) {
	timer += t;
}


/*
 * game states
 */

void Game::lose() {
	life--;
	if(life > 0) {
		mode = STARTING;
	}
	else {
		mode = GAME_OVER;
	}
}

void Game::hit(std::list<Brick *>::iterator *bricksItr) {
	Brick *brick = *(*bricksItr);
	brick->decLife();

	switch (brick->getLife()) {
	case 1:
		brick->getColor()->setRGB(BRICK1_COLOR_R, BRICK1_COLOR_G, BRICK1_COLOR_B);
		break;
	case 2:
		brick->getColor()->setRGB(BRICK2_COLOR_R, BRICK2_COLOR_G, BRICK2_COLOR_B);
		break;
	case 3:
		brick->getColor()->setRGB(BRICK3_COLOR_R, BRICK3_COLOR_G, BRICK3_COLOR_B);
		break;
	default:
		bricks->erase(*bricksItr);
		score++;
		totalScore++;
		// level up
		if(score == bricksTotal) {
			if(level == NUM_OF_LEVELS) {
				mode = FINISHED;
			}
			else {
				mode = WIN;
			}
		}
	}
}
