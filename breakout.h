/**
*   breakout.h
*/

#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <GL/glut.h>
#include <string.h>
#include <stdio.h>

#include "game.h"
#include "glTexture.h"

// constants
#define NUM_TRIANGLES_IN_CIRCLE		720
#define TRIANGLE_ANGLE_IN_CIRCLE	57.29577957795135


// variables
Game *GAME;

GLsizei WINDOW_WIDTH;
GLsizei WINDOW_HEIGHT;

bool MOUSE_IN = true;

Game::GameMode LAST_MODE;

bool CHEAT[4];

GLTexture *BACKGROUND[11];


// prototypes
int main(int argc, char** argv);
void init(void);
void changeSize(GLsizei w, GLsizei h);

void drawGame(int i);
void renderGame(void);
void drawPaddle();
void drawBall();
void drawBricks();

void processNormalKeys(unsigned char key, int x, int y);
void processMouse(int button, int state, int x, int y);
void processMousePassiveMotion(int x, int y);
void processMouseEntry(int state);

void drawScore();
void drawText(float x, float y, char *string, void *font);
void drawPaused();
void drawStateInfo();
void drawGameOver();
void drawWin();
void drawFinish();
void drawBackground();

#endif
