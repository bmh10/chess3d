#ifndef _HEADERS_H
#define _HEADERS_H

#define DEBUG 1

#define SQUARE_SIZE 0.02
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 1024

#define COL_WHITE(a) GLfloat white[] = { 1.0f, 1.0f, 1.0f, a };
#define COL_BLACK(a) GLfloat black[] = { 0.0f, 0.0f, 0.0f, a };
#define COL_RED(a) GLfloat red[] = { 1.0f, 0.0f, 0.0f, a };
#define COL_GREEN(a) GLfloat green[] = { 0.0f, 1.0f, 0.0f, a };
#define COL_BLUE(a) GLfloat blue[] = { 0.0f, 0.0f, 1.0f, a };
#define COL_YELLOW(a) GLfloat yellow[] = { 1.0f, 1.0f, 0.0f, a };
#define COL_CYAN(a) GLfloat cyan[] = { 0.0f, 1.0f, 1.0f, a };

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include  <vector>
#include <assert.h>

using namespace std;

#include <fstream>
#include <iostream>

// Static classes
#include "logger.h"
#include "openglUtil.h"

/*
#include "piece.h"
#include "board.h"


#include "menuManager.h"
#include "game.h"
*/

#endif
