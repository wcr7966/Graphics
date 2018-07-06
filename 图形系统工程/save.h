#pragma once

#include <QtGui>
#include <QDebug>
#include <QWidget>
#include <QtOpenGL/QGLWidget>
#include <QDebug>
#include <fstream>


static BITMAPFILEHEADER header;
static BITMAPINFOHEADER bitmapInfoHeader;

bool screenshot(const char* filename);
bool writeBMP(const char filename[], unsigned char* data, unsigned int w, unsigned int h);
