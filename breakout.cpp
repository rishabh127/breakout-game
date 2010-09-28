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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
        renderGame();
        glutTimerFunc(TIMER_MSECS, drawGame, 1);
    }
}

void renderGame(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    
    drawPaddle();
    
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
    // update paddle position
    float xPos = paddle->getPos()->getX() + paddle->getSpeed();
    float yPos = paddle->getPos()->getY();
    float w = paddle->getW();
    float h = paddle->getH();
    if(xPos < -COORD_RANGE) {
    	xPos = -COORD_RANGE;
    }
    else if(xPos + w > COORD_RANGE) {
    	xPos = COORD_RANGE - w;
    }
    paddle->getPos()->setX(xPos);
    glRectf(xPos, yPos, xPos+w, yPos+h);
    printf("Drawing paddle: %f, %f, (%f, %f), speed: %f COLOR: (%f, %f, %f)\n", w, h, xPos, yPos-h/2, paddle->getSpeed(),
    		paddle->getColor()->getR(),paddle->getColor()->getG(),paddle->getColor()->getB());
}


/**
 *	input process
 */

void processNormalKeys(unsigned char key, int x, int y) {
	switch(key) {
		case 'R':
		case 'r':
			// TODO configurar estado inicial do jogo
			GAME->setMode(Game::RUNNING);
			break;
		case 'Q':
		case 'q':
			exit(0);
	}
	drawGame(0);
}

void processMouse(int button, int state, int x, int y) {
	if(state == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
			printf("[ INFO ] left mouse button pressed\n");
			GAME->swapMode();
			if(GAME->getMode() == Game::RUNNING) {
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
			renderGame();
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






