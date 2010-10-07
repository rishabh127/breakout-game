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
    glutDisplayFunc(renderGame);
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
				 1.0f
	);
    glDisable(GL_DEPTH_TEST);
    
    // set global variables
    GAME = new Game();
    WINDOW_WIDTH = WINDOW_INIT_WIDTH;
    WINDOW_HEIGHT = WINDOW_INIT_HEIGHT;
}


void changeSize(GLsizei w, GLsizei h) {
	float windowHeight, windowWidth;

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
    if(GAME->getMode() != Game::PAUSED) {
    	GAME->updatePaddle();
    	GAME->updateBall();
        renderGame();
        glutTimerFunc(TIMER_MSECS, drawGame, 1);
    }
}

void renderGame(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    
    drawPaddle();
    drawBall();
    drawBricks();
    drawScore();

    glPopMatrix();
    glutSwapBuffers();
}

void drawPaddle() {
    Paddle *paddle = GAME->getPaddle();

    // set color
    glColor3f(paddle->getColor()->getR(), 
              paddle->getColor()->getG(),
              paddle->getColor()->getB()
    );

    // set position
    glRectf(paddle->getPos()->getX(),
    		paddle->getPos()->getY(),
    		paddle->getPos()->getX() + paddle->getW(),
    		paddle->getPos()->getY() + paddle->getH());
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
	glEnd();

	// set color
	glColor3f(ball->getColor()->getR()-0.3,
			ball->getColor()->getG()-0.3,
	        ball->getColor()->getB()-0.3
	);
	radius = ball->getRadius() - 0.0025;
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


void drawBricks() {
	std::list<Brick *> *bricks = GAME->getBricks();
	std::list<Brick *>::iterator itr;

	for (itr = bricks->begin(); itr != bricks->end(); itr++) {
		Brick *brick = (*itr);

		// set color
		//glColor3f(brick->getColor()->getR(), brick->getColor()->getG(),
		//		brick->getColor()->getB());


		// set position
		glColor3f(0.6,0.42,0.21);
		glRectf(brick->getPos()->getX(), brick->getPos()->getY(),
			brick->getPos()->getX() + brick->getW(),
			brick->getPos()->getY() + brick->getH());

		// set position
		glColor3f(0.5,0.0,0.0);
		glRectf(brick->getPos()->getX()+0.004, brick->getPos()->getY()+0.004,
				brick->getPos()->getX() + brick->getW() - 0.004,
				brick->getPos()->getY() + brick->getH() - 0.004);
	}
}

void drawScore() {

	// set line color
	glColor3f(SCORE_LINE_DEFAULT_COLOR_R,
			  SCORE_LINE_DEFAULT_COLOR_G,
			  SCORE_LINE_DEFAULT_COLOR_B
	);

	// draw line
	glBegin(GL_LINES);
		glVertex2f(0.0, SCORE_POSITION);
		glVertex2f(COORD_RANGE, SCORE_POSITION);
	glEnd();
}

/**
 *	input process
 */

void processNormalKeys(unsigned char key, int x, int y) {
	switch(key) {
		case 'R':
		case 'r':
			GAME->reset();
			renderGame();
			GAME->setMode(Game::PAUSED);
			break;
		case 'Q':
		case 'q':
			exit(0);
	}
	//drawGame(0);
	//TODO olhar porq outras teclas aceleram
}

void processMouse(int button, int state, int x, int y) {
	if(state == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
			printf("[ INFO ] left mouse button pressed\n");
			GAME->swapMode();
			if(GAME->getMode() == Game::RUNNING) {
				processMousePassiveMotion(x, y);
				drawGame(0);
			}
		}
		else if (button == GLUT_MIDDLE_BUTTON) {
			printf("[ INFO ] middle mouse button pressed\n");
		}
		else {
			printf("[ INFO ] right mouse button pressed\n");
			//TODO print info
			GAME->setMode(Game::RUNNING);
			processMousePassiveMotion(x, y);
			drawGame(0);
			GAME->setMode(Game::PAUSED);
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
		//printf("COLORS -> R: %f, G: %f\n", 1.0-mouseLoc, mouseLoc);
	}
}

void processMouseEntry(int state) {
	MOUSE_IN = (state == GLUT_LEFT) ? false : true;
}


