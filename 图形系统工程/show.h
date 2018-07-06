#pragma once

#include <QtGui>
#include <QDebug>
#include <QWidget>
#include <QtOpenGL/QGLWidget>
#include <QDebug>
#include <fstream>

static GLfloat aspect;
static GLfloat nRange = 200.0f;
static int width;
static int height;
static GLfloat AngleX;
static GLfloat AngleY;

void displayCubeMain();
void displayCube(void);
void cubeReshape(int w, int h);
void cubeKeyboard(GLint key, GLint x, GLint y);
void cubeInit();
static void mouseClicked(int button, int state, int x, int y);
void displayCubeMain();
