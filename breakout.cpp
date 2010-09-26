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
    float ratio = (h != 0) ? 1.0 * w / h : w;
    WINDOW_WIDTH = w;
    WINDOW_HEIGHT = h;
    
    // reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);
    
    // Set the correct perspective.
    gluPerspective(45,ratio,1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0,0.0,5.0, 
              0.0,0.0,-1.0,
              0.0f,1.0f,0.0f);
}

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

    // set position
    float xPos = paddle->getPos()->getX();
    float yPos = paddle->getPos()->getY();
    float w = ((float)paddle->getW()) * COORD_RANGE / WINDOW_WIDTH;
    float h = ((float)paddle->getH()) * COORD_RANGE / WINDOW_HEIGHT;
    
   // double ratio =  
    glRectf(xPos, yPos, xPos+w, yPos+h);
    printf("Drawing paddle: %f, %f, (%f, %f) \n", w, h, xPos-w/2, yPos-h/2);
}

