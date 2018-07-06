#include "shape.h"

Shape::Shape()
{
	hasFill = false;
	hasFinish = false;
}

void Shape::setStart(int x, int y)
{
	start.setX(x);
	start.setY(y);
}

void Shape::setEnd(int x, int y)
{
	end.setX(x);
	end.setY(y);
}

void Shape::setCurr(int x, int y)
{	
	curr.setX(x);
	curr.setY(y);
}

void Shape::setPre(int x, int y)
{
	pre.setX(x);
	pre.setY(y);
}

void Shape::setMid(int x, int y)
{
	mid.setX(x);
	mid.setY(y);
}

void Shape::setHasFill()
{
	hasFill = true;
}

void Shape::setHasFinish()
{
	hasFinish = true;
}

bool Shape::ifFillFunc()
{
	return hasFill;
}

QPoint Shape::startPoint()
{
	return start;
}

QPoint Shape::endPoint()
{
	return end;
}

QPoint Shape::currPoint()
{
	return curr;
}

QPoint Shape::prePoint()
{
	return pre;
}

QPoint Shape::midPoint()
{
	return mid;
}

void Shape::setColor(GLfloat red, GLfloat green, GLfloat blue)
{
	currColor.Red = red;
	currColor.Green = green;
	currColor.Blue = blue;
}

void Shape::setFillColor(GLfloat red, GLfloat green, GLfloat blue)
{
	fillColor.Red = red;
	fillColor.Green = green;
	fillColor.Blue = blue;
}

int Shape::rotateX(int x, int y)
{
	int x0 = mid.x();
	int y0 = mid.y();
	int r, xr, yr;
	r= x0 + (x - x0)*cos(angle) - (y - y0)*sin(angle);
	return r;
}

int Shape::rotateY(int x, int y)
{
	int x0 = mid.x();
	int y0 = mid.y();
	int r, xr, yr;
	r= y0 + (x - x0)*sin(angle) + (y - y0)*cos(angle);
	return r;
}

void Shape::setAngle()
{
	int x1 = pre.x();
	int y1 = pre.y();
	int x2 = curr.x();
	int y2 = curr.y();
	double angle1 = atan2(y1 - mid.y(), x1 - mid.x());
	double angle2 = atan2(y2 - mid.y(), x2 - mid.x());
	angle += angle2 - angle1;
}

void Shape::setScale()
{
	double x1 = pre.x();
	double x2 = curr.x();
	double x0 = mid.x();
	scaleX *= (x2 - x0) / (x1 - x0);
	double y1 = pre.y();
	double y2 = curr.y();
	double y0 = mid.y();
	scaleY *= (y2 - y0) / (y1 - y0);
}

int Shape::setScaleX(int x)
{
	int x0 = mid.x();
	int y0 = mid.y();
	int sx = x*scaleX + x0*(1 - scaleX);
	return sx;
}

int Shape::setScaleY(int y)
{
	int x0 = mid.x();
	int y0 = mid.y();
	int sy = y*scaleY + y0*(1 - scaleY);
	return sy;
}

void Shape::addPoint(int x, int y)
{
}

void Shape::fill()
{
}

void Shape::initNewEdgeTable()
{}

void Shape::setPoint()
{}

int Shape::getVecSize()
{
	return 1;
}

void Shape::showPoints()
{}

void Shape::modify(QPoint pre, QPoint curr)
{}

void Shape::clip(int x1, int y1, int x2, int y2)
{}