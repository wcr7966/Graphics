#pragma once
#include "shape.h"
#include "rect.h"
#include "line.h"

class Bspline :public Shape, public Rect, public Line
{
public:
	Bspline();
	~Bspline();
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

