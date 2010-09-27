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
    printf("Drawing paddle: %f, %f, (%f, %f), speed: %f\n", w, h, xPos, yPos-h/2, paddle->getSpeed());
}


/**
 *	input process
 */

void processNormalKeys(unsigned char key, int x, int y) {
	switch(key) {
		case 'R':
		case 'r':
			// TODO configurar estado inicial do jogo
			GAME->getPaddle()->incSpeed(PADDLE_POWER);
			if(GAME->getPaddle()->getSpeed() > PADDLE_MAX_SPEED) {
				GAME->getPaddle()->setSpeed(PADDLE_MAX_SPEED);
			}
			printf("\nMUDOU VELOCIDADE: %f\n", GAME->getPaddle()->getSpeed());
			// TODO speed = mousex * power
			GAME->setMode(Game::RUNNING);
			break;
		case 'E':
		case 'e':
			GAME->getPaddle()->incSpeed(-PADDLE_POWER);
			if(GAME->getPaddle()->getSpeed() < -PADDLE_MAX_SPEED) {
				GAME->getPaddle()->setSpeed(-PADDLE_MAX_SPEED);
			}
			GAME->setMode(Game::RUNNING);
			break;
	}
	drawGame(0);
}


