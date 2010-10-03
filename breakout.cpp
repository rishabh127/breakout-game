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
	glViewport(0,0,w,h);
	glutReshapeWindow(WINDOW_WIDTH,WINDOW_HEIGHT);
	glutPostRedisplay();
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

    //printf("Drawing paddle: %f, %f, (%f, %f), speed: %f COLOR: (%f, %f, %f)\n", w, h, xPos, yPos-h/2, paddle->getSpeed(),
    //		paddle->getColor()->getR(),paddle->getColor()->getG(),paddle->getColor()->getB());
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

	printf("BALL: pos: (%f, %f), dir: (%f, %f), speed = %f\n",
			ball->getPos()->getX(), ball->getPos()->getY(),
			ball->getDir()->getX(), ball->getDir()->getY(),
			ball->getSpeed());
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
		printf("COLORS -> R: %f, G: %f\n", 1.0-mouseLoc, mouseLoc);
	}
}

void processMouseEntry(int state) {
	MOUSE_IN = (state == GLUT_LEFT) ? false : true;
}


