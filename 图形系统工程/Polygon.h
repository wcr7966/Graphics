#pragma once
#include "shape.h"
#include "line.h"
#include "rect.h"

class Poly: public Shape, public Line, public Rect
{
public:
	Poly();
	~Poly();
	void paint();
	bool ifSelect();
	void find();
	void findNormal();
	void drawSelectArea();
	void translate(int dx, int dy);
	int getMidX();
	int getMidY();
	void addPoint(int x, int y);
	void initNewEdgeTable();
	void fill();
	void showPoints();
	void modify(QPoint pre, QPoint curr);
	int isNear(QPoint p);
	void clip(int x1, int y1, int x2, int y2);
	int getVecSize();

private:
	QVector <QPoint> points;
	int maxX, maxY, minX, minY;
	QVector <Edge> AET;
	QVector <Edge> *NEdge;
	int size;
	int cap;
};

