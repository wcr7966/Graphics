#ifndef LINE_H
#define LINE_H

#include "shape.h"

class Line : public Shape
{
public:
    Line();

    void paint();
	bool ifSelect();
	void drawSelectArea();
	void translate(int dx, int dy);
	int getMidX();
	int getMidY();
	void showPoints();
	void modify(QPoint pre, QPoint curr);
	int isNear(QPoint p);

private:
	GLfloat k;
	GLfloat b;
};

#endif // LINE_H
