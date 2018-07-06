#pragma once

#include "shape.h"
#include "rect.h"
#include "line.h"

class Circle : public Shape, public Rect, public Line
{
public:
	Circle();
	~Circle();
	void paint();
	bool ifSelect();
	void drawSelectArea();
	void translate(int dx, int dy);
	int getMidX();
	int getMidY();
	void setScale();
	int rotateX(int x, int y);
	int rotateY(int x, int y);
	void fill();
};

