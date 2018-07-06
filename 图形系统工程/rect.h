#ifndef RECT_H
#define RECT_H

#include "shape.h"
#include "line.h"

class Rect : public Shape, public Line
{
public:
    Rect();

    void paint();
	bool ifSelect();
	void drawSelectArea();
	void translate(int dx, int dy);
	void find();
	void findNormal();
	int getMidX();
	int getMidY();
	void fill();
	void initNewEdgeTable();
	void setPoint();
	void changePoint();
	void showPoints();

private:
	int minX, minY, maxX, maxY;
	QVector<QPoint> vec;
	QVector <Edge> AET;
	QVector <Edge> *NEdge;
	int size;
	int cap;
};

#endif // RECT_H
