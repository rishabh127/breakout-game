/**
*   breakout.h
*/

#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <GL/glut.h>
#include <string.h>
#include <stdio.h>

#include "game.h"

// constants
#define WINDOW_INIT_POSITION_X      10
#define WINDOW_INIT_POSITION_Y      10
#define WINDOW_INIT_WIDTH           820
#define WINDOW_INIT_HEIGHT          640
#define WINDOW_TITLE                "Breakout"
#define TIMER_MSECS                 50
#define COORD_RANGE                 1.0

// variables
Game *GAME;
GLsizei WINDOW_WIDTH;
GLsizei WINDOW_HEIGHT;
bool MOUSE_IN = true;


// prototypes
int main(int argc, char** argv);
void init(void);
void changeSize(GLsizei w, GLsizei h);

void drawGame(int i);
void renderGame(void);
void drawPaddle();

void processNormalKeys(unsigned char key, int x, int y);
void processMouse(int button, int state, int x, int y);
void processMousePassiveMotion(int x, int y);
void processMouseEntry(int state);

#endif
