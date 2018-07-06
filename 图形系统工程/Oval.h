#pragma once
#include "Shape.h"
#include "rect.h"

class Oval:public Shape, public Rect
{
public:
	Oval();
	~Oval();

	void paint();
	bool ifSelect();
	void drawSelectArea();
	void translate(int dx, int dy);
	int getMidX();
	int getMidY();
};

