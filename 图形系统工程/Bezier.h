#pragma once
#include "shape.h"
#include "line.h"
#include "rect.h"
class Bezier: public Shape, public Line, public Rect
{
public:
	Bezier();
	~Bezier();
	void paint();
	bool ifSelect();
	void drawSelectArea();
	void addPoint(int x, int y);
	void translate(int dx, int dy);
	int getMidX();
	int getMidY();
	void find();
	void findNormal();
	double C(int x, int i);
	int JieCheng(int n);
	int getVecSize();
	void showPoints();
	void modify(QPoint pre, QPoint curr);
	int isNear(QPoint p);

private:
	QVector <QPoint> points;
	int maxX, maxY, minX, minY;
};

