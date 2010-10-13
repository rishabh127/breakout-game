/**
*   breakout.cpp
*/

#include "breakout.h"

                   
int main(int argc, char** argv) {
    // openGL initialization
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

	// window configuration
    glutInitWindowPosition(WINDOW_INIT_POSITION_X, WINDOW_INIT_POSITION_Y);
    glutInitWindowSize(WINDOW_INIT_WIDTH, WINDOW_INIT_HEIGHT);
    glutInit(&argc, argv);
    glutCreateWindow(WINDOW_TITLE);

    // set draw function
    glutDisplayFunc(drawPaused);
    glutTimerFunc(TIMER_MSECS, drawGame, 1);

    // set reshap function
    glutReshapeFunc(changeSize);

    // set input proccessing functions
    glutKeyboardFunc(processNormalKeys);
    glutMouseFunc(processMouse);
   	glutPassiveMotionFunc(processMousePassiveMotion);
   	glutEntryFunc(processMouseEntry);

    // main loop
    init();
    glutMainLoop();
}


void init(void) {
    // set background color as black
    glClearColor(WINDOW_DEFAULT_COLOR_R,
				 WINDOW_DEFAULT_COLOR_G,
				 WINDOW_DEFAULT_COLOR_B,
				 0.0f
	);

//   	glDisable(GL_ALPHA_TEST);

    // set global variables
    GAME = new Game();
    WINDOW_WIDTH = WINDOW_INIT_WIDTH;
    WINDOW_HEIGHT = WINDOW_INIT_HEIGHT;
    LAST_MODE = Game::STARTING;
	glLineWidth(8.0);

	// load textures
	BACKGROUND[0] = new GLTexture("images/space01.png");
	BACKGROUND[1] = new GLTexture("images/space02.png");
	BACKGROUND[2] = new GLTexture("images/space03.png");
	BACKGROUND[3] = new GLTexture("images/space04.png");
	BACKGROUND[4] = new GLTexture("images/space05.png");
	BACKGROUND[5] = new GLTexture("images/space06.png");
	BACKGROUND[6] = new GLTexture("images/space07.png");
	BACKGROUND[7] = new GLTexture("images/space08.png");
	BACKGROUND[8] = new GLTexture("images/space09.png");
	BACKGROUND[9] = new GLTexture("images/space10.png");
	BACKGROUND[10] = new GLTexture("images/end.png");
}


void changeSize(GLsizei w, GLsizei h) {
	if (h == 0) {
		h = 1;
	}
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, COORD_RANGE, 0, COORD_RANGE);
}


/**
 *  draw funcions
 */

void drawGame(int i) {
	switch(GAME->getMode()) {
	case Game::GAME_OVER:
		drawGameOver();
		break;
	case Game::PAUSED:
		break;
	case Game::WIN:
		// TODO - verifica se subiu de level ou se zerou
		drawWin();
		break;
	case Game::FINISHED :
		drawFinish();
		break;
	default:
		GAME->updatePaddle();
		GAME->updateBall();
		renderGame();
		GAME->addTimer(TIMER_MSECS);
		glutTimerFunc(TIMER_MSECS, drawGame, 1);
	}
}

void renderGame(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    
	drawBackground();
	drawPaddle();
    drawBall();
    drawBricks();
    drawScore();

    glPopMatrix();
    glutSwapBuffers();
}

void drawPaddle() {
    Paddle *paddle = GAME->getPaddle();
    float x = paddle->getPos()->getX();
    float y = paddle->getPos()->getY();
    float width = paddle->getW();
    float height = paddle->getH();

    glBegin(GL_TRIANGLE_STRIP);
		glColor3f(paddle->getColor()->getR() / 2.5, paddle->getColor()->getG()
				/ 2.5, paddle->getColor()->getB() / 2.5);
		glVertex2f(x, y);
		glVertex2f(x + width, y);
		glColor3f(paddle->getColor()->getR(), paddle->getColor()->getG(),
				paddle->getColor()->getB());
		glVertex2f(x + width / 2, y + height / 2);
		glColor3f(paddle->getColor()->getR() / 2.5, paddle->getColor()->getG()
				/ 2.5, paddle->getColor()->getB() / 2.5);
		glVertex2f(x + width, y + height);
		glVertex2f(x, y + height);
		glColor3f(paddle->getColor()->getR(), paddle->getColor()->getG(),
				paddle->getColor()->getB());
		glVertex2f(x + width / 2, y + height / 2.5);
		glColor3f(paddle->getColor()->getR() / 2.5, paddle->getColor()->getG()
				/ 2.5, paddle->getColor()->getB() / 2.5);
		glVertex2f(x, y);
	glEnd();

}

void drawBall() {
	Ball *ball = GAME->getBall();

	// set color
	glColor3f(ball->getColor()->getR(),
			ball->getColor()->getG(),
	        ball->getColor()->getB()
	);

	// draw a solid disc from a bunch of triangles
	float originX = ball->getPos()->getX();
	float originY = ball->getPos()->getY();
	float vectorX1 = originX, vectorY1 = originY;
	float radius = ball->getRadius();
	glBegin(GL_TRIANGLES);
		for (int i = 0; i <= NUM_TRIANGLES_IN_CIRCLE; i++) {
			float angle = (float) (((double) i) / TRIANGLE_ANGLE_IN_CIRCLE);
			float vectorX = originX + (radius * (float) sin((double) angle));
			float vectorY = originY + (radius * (float) cos((double) angle));
			glVertex2d(originX, originY);
			glVertex2d(vectorX1, vectorY1);
			glVertex2d(vectorX, vectorY);
			vectorY1 = vectorY;
			vectorX1 = vectorX;
		}

		// set color
		glColor3f(ball->getColor()->getR()-0.3,
			ball->getColor()->getG()-0.3,
		    ball->getColor()->getB()-0.3
		);
		radius = ball->getRadius() - 0.0025;

		for (int i = 0; i <= NUM_TRIANGLES_IN_CIRCLE; i++) {
			float angle = (float) (((double) i) / TRIANGLE_ANGLE_IN_CIRCLE);
			float vectorX = originX + (radius * (float) sin((double) angle));
			float vectorY = originY + (radius * (float) cos((double) angle));
			glVertex2d(originX, originY);
			glVertex2d(vectorX1, vectorY1);
			glVertex2d(vectorX, vectorY);
			vectorY1 = vectorY;
			vectorX1 = vectorX;
		}
	glEnd();
}


void drawBricks() {
	std::list<Brick *> *bricks = GAME->getBricks();
	std::list<Brick *>::iterator itr;
	float x, y, width, height;

	for (itr = bricks->begin(); itr != bricks->end(); itr++) {
		Brick *brick = (*itr);
		x = brick->getPos()->getX();
		y = brick->getPos()->getY();
		width = brick->getW();
		height = brick->getH();
		glBegin(GL_TRIANGLE_STRIP);
			glColor3f(brick->getColor()->getR() / 2.5, brick->getColor()->getG()
					/ 2.5, brick->getColor()->getB() / 2.5);
			glVertex2f(x, y);
			glVertex2f(x + width, y);
			glColor3f(brick->getColor()->getR(), brick->getColor()->getG(),
					brick->getColor()->getB());
			glVertex2f(x + width / 2, y + height / 2);
			glColor3f(brick->getColor()->getR() / 2.5, brick->getColor()->getG()
					/ 2.5, brick->getColor()->getB() / 2.5);
			glVertex2f(x + width, y + height);
			glVertex2f(x, y + height);
			glColor3f(brick->getColor()->getR(), brick->getColor()->getG(),
					brick->getColor()->getB());
			glVertex2f(x + width / 2, y + height / 2.5);
			glColor3f(brick->getColor()->getR() / 2.5, brick->getColor()->getG()
					/ 2.5, brick->getColor()->getB() / 2.5);
			glVertex2f(x, y);
		glEnd();
	}
}

void drawScore() {
	char buffer[100];
	float originX, originY;
	float vectorX1, vectorY1;
	float radius;

	// set score color
	glColor3f(SCORE_DEFAULT_COLOR_R,
			  SCORE_DEFAULT_COLOR_G,
			  SCORE_DEFAULT_COLOR_B
	);

	// draw informations
	sprintf(buffer, "BREAKOUT");
	drawText(0.05,0.947, buffer, GLUT_BITMAP_TIMES_ROMAN_24);
	sprintf(buffer, "LEVEL: %.2d/%.2d", GAME->getLevel(), NUM_OF_LEVELS);
	drawText(0.33,0.95, buffer, GLUT_BITMAP_9_BY_15);
	sprintf(buffer, "SCORE: %.2d/%.2d", GAME->getScore(), GAME->getTotalBricks());
	drawText(0.53,0.95, buffer, GLUT_BITMAP_9_BY_15);
	sprintf(buffer, "LIFES: ");
	drawText(0.74,0.95, buffer, GLUT_BITMAP_9_BY_15);
	radius = 0.009;
	originX = 0.81;
	originY = 0.957;
	for(int i=0; i<GAME->getLife(); i++) {
		originX += 0.025;
		vectorX1 = originX, vectorY1 = originY;
		glBegin(GL_TRIANGLES);
			for (int i = 0; i <= NUM_TRIANGLES_IN_CIRCLE; i++) {
				float angle = (float) (((double) i) / TRIANGLE_ANGLE_IN_CIRCLE);
				float vectorX = originX + (radius * (float) sin((double) angle));
				float vectorY = originY + (radius * (float) cos((double) angle));
				glVertex2d(originX, originY);
				glVertex2d(vectorX1, vectorY1);
				glVertex2d(vectorX, vectorY);
				vectorY1 = vectorY;
				vectorX1 = vectorX;
			}
		glEnd();
	}

	// draw lines
	glBegin(GL_LINES);
		glVertex2f(0.28, SCORE_POSITION);
		glVertex2f(0.28, 1);
		glVertex2f(0.000, SCORE_POSITION);
		glVertex2f(COORD_RANGE, SCORE_POSITION);
		glVertex2f(0.002, SCORE_POSITION);
		glVertex2f(0.002, 1);
		glVertex2f(0.998, SCORE_POSITION);
		glVertex2f(0.998, 1);
		glVertex2f(0.002, 0.998);
		glVertex2f(COORD_RANGE, 0.998);
		glVertex2f(0.998, SCORE_POSITION);
		glVertex2f(0.998, 1);
	glEnd();
}

void drawPaused() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	drawBackground();
	drawPaddle();
	drawBall();
	drawBricks();
	drawScore();

	// draw
	char buffer[100];
	sprintf(buffer, "PAUSED");

	// set color
	glColor3f(SCORE_DEFAULT_COLOR_R, SCORE_DEFAULT_COLOR_G,
		SCORE_DEFAULT_COLOR_B
	);

	// draw border
	glBegin(GL_LINES);
		glVertex2f(0.37, 0.447);
		glVertex2f(0.37, 0.555);
		glVertex2f(0.63, 0.447);
		glVertex2f(0.63, 0.555);
		glVertex2f(0.37, 0.45);
		glVertex2f(0.63, 0.45);
		glVertex2f(0.37, 0.55);
		glVertex2f(0.63, 0.55);
	glEnd();

	glColor3f(0.0,0.0,0.0);
	glRectf(0.3725, 0.453, 0.6275, 0.548);

	glColor3f(SCORE_DEFAULT_COLOR_R, SCORE_DEFAULT_COLOR_G,
			SCORE_DEFAULT_COLOR_B
	);
	drawText(0.435, 0.49, buffer, GLUT_BITMAP_TIMES_ROMAN_24);

	glPopMatrix();
	glutSwapBuffers();
}

void drawStateInfo() {
	float x, y, w, h, speed;
	std::list<Brick *> *bricks = GAME->getBricks();
	std::list<Brick *>::iterator itr;

	GAME->updatePaddle();
	GAME->updateBall();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	drawBackground();
	drawPaddle();
	drawBall();
	drawBricks();
	drawScore();

	// set color
	glColor3f(SCORE_DEFAULT_COLOR_R, SCORE_DEFAULT_COLOR_G,
		SCORE_DEFAULT_COLOR_B
	);

	// draw
	char buffer[100];

	// draw attributes
	x = GAME->getBall()->getPos()->getX();
	y = GAME->getBall()->getPos()->getY();
	speed = GAME->getBall()->getSpeed();
	sprintf(buffer, "speed: %.3f", speed);
	drawText(x+0.005, y+0.008, buffer, GLUT_BITMAP_HELVETICA_10);
	sprintf(buffer, "x: %.3f, y: %.3f", x, y);
	drawText(x, y-0.01, buffer, GLUT_BITMAP_HELVETICA_10);

	x = GAME->getPaddle()->getPos()->getX();
	y = GAME->getPaddle()->getPos()->getY();
	w = GAME->getPaddle()->getW();
	speed = GAME->getPaddle()->getSpeed();
	sprintf(buffer, "speed: %.3f", speed);
	drawText(x+0.007, y+0.038, buffer, GLUT_BITMAP_HELVETICA_10);
	sprintf(buffer, "x: %.3f, y: %.3f", x, y);
	drawText(x+0.002, y+0.02, buffer, GLUT_BITMAP_HELVETICA_10);

	for (itr = bricks->begin(); itr != bricks->end(); itr++) {
		Brick *brick = (*itr);
		x = brick->getPos()->getX();
		y = brick->getPos()->getY();
		h = brick->getH();
		sprintf(buffer, "x: %.2f", x);
		drawText(x+0.001, y+h/2+0.001, buffer, GLUT_BITMAP_HELVETICA_10);
		sprintf(buffer, "y: %.2f",y);
		drawText(x+0.001, y+0.001, buffer, GLUT_BITMAP_HELVETICA_10);
	}

	glPopMatrix();
	glutSwapBuffers();
}

void drawGameOver() {
	char buffer[100];
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	drawBackground();
	drawPaddle();
	drawBall();
	drawBricks();
	drawScore();

	// set color
	glColor3f(SCORE_DEFAULT_COLOR_R, SCORE_DEFAULT_COLOR_G,
		SCORE_DEFAULT_COLOR_B
	);

	// draw border
	glBegin(GL_LINES);
		glVertex2f(0.35, 0.416);
		glVertex2f(0.35, 0.555);
		glVertex2f(0.65, 0.416);
		glVertex2f(0.65, 0.555);
		glVertex2f(0.35, 0.42);
		glVertex2f(0.65, 0.42);
		glVertex2f(0.35, 0.55);
		glVertex2f(0.65, 0.55);
	glEnd();

	glColor3f(0.0,0.0,0.0);
	glRectf(0.3525, 0.424, 0.6465, 0.5475);

	glColor3f(SCORE_DEFAULT_COLOR_R, SCORE_DEFAULT_COLOR_G,
			SCORE_DEFAULT_COLOR_B
	);
	sprintf(buffer, "GAME OVER");
	drawText(0.398, 0.5, buffer, GLUT_BITMAP_TIMES_ROMAN_24);
	sprintf(buffer, "TOTAL SCORE: %.3d", GAME->getTotalScore());
	drawText(0.4, 0.47, buffer, GLUT_BITMAP_9_BY_15);
	sprintf(buffer, "PRESS \"r\" TO RESTART");
	drawText(0.378, 0.445, buffer, GLUT_BITMAP_9_BY_15);

	glPopMatrix();
	glutSwapBuffers();
}

void drawWin() {
	char buffer[100];
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	drawBackground();
	drawScore();

	// set color
	glColor3f(SCORE_DEFAULT_COLOR_R, SCORE_DEFAULT_COLOR_G,
			SCORE_DEFAULT_COLOR_B
	);

	// draw border
	glBegin(GL_LINES);
		glVertex2f(0.35, 0.416);
		glVertex2f(0.35, 0.555);
		glVertex2f(0.65, 0.416);
		glVertex2f(0.65, 0.555);
		glVertex2f(0.35, 0.42);
		glVertex2f(0.65, 0.42);
		glVertex2f(0.35, 0.55);
		glVertex2f(0.65, 0.55);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glRectf(0.3525, 0.424, 0.6465, 0.5475);

	glColor3f(SCORE_DEFAULT_COLOR_R, SCORE_DEFAULT_COLOR_G,
		SCORE_DEFAULT_COLOR_B
	);
	sprintf(buffer, "LEVEL UP!");
	drawText(0.415, 0.49, buffer, GLUT_BITMAP_TIMES_ROMAN_24);
	sprintf(buffer, "CLICK TO CONTINUE");
	drawText(0.393, 0.45, buffer, GLUT_BITMAP_9_BY_15);

	glPopMatrix();
	glutSwapBuffers();
}

void drawFinish() {
	char buffer[100];
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	drawBackground();
	drawScore();

	// set color
	glColor3f(0,0,0);
	sprintf(buffer, "CONGRATULATIONS !!!");
	drawText(0.32, 0.7, buffer, GLUT_BITMAP_TIMES_ROMAN_24);
	sprintf(buffer, "YOU SPENT %ld MINUTES (%lds) OF YOUR LIFE", GAME->getTimer()/60000, GAME->getTimer()/1000);
	drawText(0.27, 0.63, buffer, GLUT_BITMAP_9_BY_15);
	sprintf(buffer, "PRESS \"r\" TO SPEND MORE");
	drawText(0.36, 0.57, buffer, GLUT_BITMAP_9_BY_15);
	sprintf(buffer, "TOTAL SCORE: %.3d", GAME->getTotalScore());
	drawText(0.4, 0.5, buffer, GLUT_BITMAP_9_BY_15);
	sprintf(buffer, "CREDITS");
	drawText(0.429, 0.35, buffer, GLUT_BITMAP_TIMES_ROMAN_24);
	sprintf(buffer, "Lucas Cunha de Oliveira Miranda");
	drawText(0.319, 0.28, buffer, GLUT_BITMAP_9_BY_15);
	sprintf(buffer, "lucmir@dcc.ufmg.br");
	drawText(0.393, 0.23, buffer, GLUT_BITMAP_9_BY_15);

	glColor3f(SCORE_DEFAULT_COLOR_R, SCORE_DEFAULT_COLOR_G,
		SCORE_DEFAULT_COLOR_B
	);
	sprintf(buffer, "CONGRATULATIONS !!!");
	drawText(0.3215, 0.7, buffer, GLUT_BITMAP_TIMES_ROMAN_24);
	sprintf(buffer, "YOU SPENT %ld MINUTES (%lds) OF YOUR LIFE", GAME->getTimer()/60000, GAME->getTimer()/1000);
	drawText(0.2715, 0.63, buffer, GLUT_BITMAP_9_BY_15);
	sprintf(buffer, "PRESS \"r\" TO SPEND MORE");
	drawText(0.362, 0.57, buffer, GLUT_BITMAP_9_BY_15);
	sprintf(buffer, "TOTAL SCORE: %.3d", GAME->getTotalScore());
	drawText(0.402, 0.5, buffer, GLUT_BITMAP_9_BY_15);
	sprintf(buffer, "CREDITS");
	drawText(0.4305, 0.35, buffer, GLUT_BITMAP_TIMES_ROMAN_24);
	sprintf(buffer, "Lucas Cunha de Oliveira Miranda");
	drawText(0.320, 0.28, buffer, GLUT_BITMAP_9_BY_15);
	sprintf(buffer, "lucmir@dcc.ufmg.br");
	drawText(0.394, 0.23, buffer, GLUT_BITMAP_9_BY_15);

	glPopMatrix();
	glutSwapBuffers();
}

void drawBackground() {
	int num = (GAME->getMode() == Game::FINISHED) ? 10 :
		(GAME->getLevel()-1)%10;
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	BACKGROUND[num]->drawEntire(0, 1, 1, 0);
	glDisable(GL_TEXTURE_2D);
}

void drawText(float x, float y, char *string, void *font)
{
	int len, i;
	glRasterPos2f(x, y);
	len = (int) strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font, string[i]);
	}
}


/**
 *	input process
 */

void processNormalKeys(unsigned char key, int x, int y) {
	switch(key) {
		case 'Q':
		case 'q':
			exit(0);
		case 'L':
		case 'l':
			CHEAT[0] = true;
			break;
		case 'U':
		case 'u':
			if(CHEAT[0]) {
				CHEAT[1] = true;
			}
			break;
		case 'C':
		case 'c':
			if(CHEAT[1]) {
				CHEAT[2] = true;
			}
			break;
		case 'A':
		case 'a':
			if(CHEAT[2]) {
				CHEAT[3] = true;
			}
			break;
		case 'S':
		case 's':
			if(CHEAT[3]) {
				GAME->setMode(Game::FINISHED);
				drawFinish();
			}
		break;
		case 'R':
		case 'r':
			GAME->reset();
			drawPaused();
			LAST_MODE = Game::STARTING;
		default:
			for(int i=0; i<4; i++) {
				CHEAT[i] = false;
			}
	}
}

void processMouse(int button, int state, int x, int y) {
	if(state == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
			if(GAME->getMode() == Game::WIN) {
				if(GAME->getLevel() < NUM_OF_LEVELS) {
					GAME->newLevel();
				}
				else {
					GAME->setMode(Game::FINISHED);
				}
			}
			if(GAME->getMode() != Game::GAME_OVER
					&& GAME->getMode() != Game::FINISHED) {
				LAST_MODE = GAME->swapMode();
				if(GAME->getMode() == Game::RUNNING
						|| GAME->getMode() == Game::STARTING) {
					processMousePassiveMotion(x, y);
					drawGame(0);
				}
				else {
					drawPaused();
				}
			}
		}
		else if (button == GLUT_MIDDLE_BUTTON) {
		}
		else {
			if(GAME->getMode() != Game::GAME_OVER
					&& GAME->getMode() != Game::WIN
					&& GAME->getMode() != Game::FINISHED) {
				GAME->setMode(LAST_MODE);
				if(LAST_MODE == Game::PAUSED) {
					GAME->setMode(Game::RUNNING);
				}
				processMousePassiveMotion(x, y);
				drawStateInfo();
				if(GAME->getMode() == Game::STARTING) {
					LAST_MODE = Game::STARTING;
				}
				GAME->setMode(Game::PAUSED);
			}
		}
	}
}

void processMousePassiveMotion(int x, int y) {
	if(GAME->getMode() != Game::PAUSED) {
		// update paddle speed
		float mouseLoc = (float)x;
		if(WINDOW_WIDTH != 0) {
			mouseLoc /= WINDOW_WIDTH;
		}
		float paddleSpeed = mouseLoc * PADDLE_POWER;
		GAME->getPaddle()->setSpeed(paddleSpeed - PADDLE_POWER/2.0);

		// update paddle color
		GAME->getPaddle()->getColor()->setR(1.0 - mouseLoc);
		GAME->getPaddle()->getColor()->setG(mouseLoc);
	}
}

void processMouseEntry(int state) {
	MOUSE_IN = (state == GLUT_LEFT) ? false : true;
}


