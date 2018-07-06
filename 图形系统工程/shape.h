#ifndef SHAPE_H
#define SHAPE_H

#define PI 3.14159


#include <QtGui>
#include <QVector>
#include <QtOpenGL\glut.h>
#include <cmath>
#include <math.h>

struct Color
{
	GLfloat Red;
	GLfloat Green;
	GLfloat Blue;
};

struct Edge
{
	double xi;
	double dx;
	int ymax;
	bool operator<(const Edge &e) const
	{
		return xi < e.xi;
	}
};

enum Select {
	DRAW, SELECT, SHOW
};

enum Conv {
	TRANSLATE, ROTATE, SCALE, MODIFY, FILL, CLIP
};

class Shape
{
public:

	enum shapeChoice {
		LINE, RECT, CIRCLE, OVAL, POLYGON, BEZIER, BSPLINE
	};

	enum colorChoice {
		Red, Green, Blue, Black, White
	};


    Shape();
	void setStart(int x, int y);
	void setEnd(int x, int y);
	void setCurr(int x, int y);
	void setPre(int x, int y);
	void setMid(int x, int y);
	QPoint startPoint();
	QPoint endPoint();
	QPoint currPoint();
	QPoint prePoint();
	QPoint midPoint();
	double getAngle()
	{
		return angle;
	}
	void setAngle();
	void setColor(GLfloat red, GLfloat green, GLfloat blue);
	void setFillColor(GLfloat red, GLfloat green, GLfloat blue);
	void setHasFill();
	void setHasFinish();
	bool ifFillFunc();
    void virtual paint() = 0;
	bool virtual ifSelect() = 0;
	void virtual drawSelectArea() = 0;
	void virtual translate(int dx, int dy) = 0;
	int virtual setScaleX(int x);
	int virtual setScaleY(int y);
	void virtual addPoint(int x, int y);
	int virtual getMidX() = 0;
	int virtual getMidY() = 0;
	int virtual rotateX(int x, int y);
	int virtual rotateY(int x, int y);
	void virtual setScale();
	void virtual fill();
	void virtual initNewEdgeTable();
	void virtual setPoint();
	int virtual getVecSize();
	void virtual showPoints();
	void virtual modify(QPoint pre, QPoint curr);
	void virtual clip(int x1, int y1, int x2, int y2);

protected:
    QPoint start;
    QPoint end;
	QPoint curr;
	QPoint pre;
	QPoint mid;
	Color currColor;
	Color fillColor;
	double angle;
	double scaleX;
	double scaleY;
	bool hasFill;
	bool hasFinish;
};

#endif // SHAPE_H

