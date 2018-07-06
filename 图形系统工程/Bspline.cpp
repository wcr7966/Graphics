#include "Bspline.h"



Bspline::Bspline()
{
	Shape::angle = 0;
	Shape::scaleX = 1;
	Shape::scaleY = 1;
}


Bspline::~Bspline()
{
}

void Bspline::paint()
{
	glLineWidth(2.0f);
	Line::currColor = Shape::currColor;

	int x1, y1, x2, y2, i;
	for (i = 0; i < points.size() - 1; i++)
	{
		x1 = Shape::setScaleX(points[i].x());
		y1 = Shape::setScaleY(points[i].y());
		x2 = Shape::setScaleX(points[i + 1].x());
		y2 = Shape::setScaleY(points[i + 1].y());

		int x3 = Shape::rotateX(x1, y1);
		int y3 = Shape::rotateY(x1, y1);
		int x4 = Shape::rotateX(x2, y2);
		int y4 = Shape::rotateY(x2, y2);
		Line *line = new Line;
		line->setColor(0.5, 0.5, 0.5);
		line->setStart(x3, y3);
		line->setEnd(x4, y4);
		line->paint();
	}

	if (Shape::hasFinish)
	{
		glColor3f(Shape::currColor.Red, Shape::currColor.Green, Shape::currColor.Blue);
		float f1, f2, f3, f4;
		float deltaT = 1.0 / 1000 / points.count();
		float T;
		glBegin(GL_POINTS);
		for (int num = 0; num < points.count() - 3; num++)
		{
			for (int i = 0; i < 1000 * points.count(); i++)
			{
				T = i*deltaT;
				f1 = (-pow(T, 3) + 3 * T*T - 3 * T + 1) / 6.0;
				f2 = (3 * pow(T, 3) - 6 * T*T + 4) / 6.0;
				f3 = (-3 * pow(T, 3) + 3 * T*T + 3 * T + 1) / 6.0;
				f4 = pow(T, 3) / 6.0;
				int x = Shape::setScaleX(f1*points[num].x() + f2*points[num + 1].x() + f3*points[num + 2].x() + f4*points[num + 3].x());
				int y = Shape::setScaleY(f1*points[num].y() + f2*points[num + 1].y() + f3*points[num + 2].y() + f4*points[num + 3].y());
				glVertex2i(Shape::rotateX(x, y), Shape::rotateY(x, y));
			}
		}
		glEnd();
	}
}

int Bspline::getMidX()
{
	find();
	return (minX + maxX) / 2;
}

int Bspline::getMidY()
{
	find();
	return (minY + maxY) / 2;
}

void Bspline::find()
{
	if (points.count() > 0)
	{
		int x0 = Shape::setScaleX(points[0].x());
		int y0 = Shape::setScaleY(points[0].y());
		minX = Shape::rotateX(x0, y0);
		minY = Shape::rotateY(x0, y0);
		maxX = Shape::rotateX(x0, y0);
		maxY = Shape::rotateY(x0, y0);
		for (int i = 1; i < points.count(); i++)
		{
			int x1 = Shape::setScaleX(points[i].x());
			int y1 = Shape::setScaleY(points[i].y());
			if (Shape::rotateX(x1, y1) >maxX)
				maxX = Shape::rotateX(x1, y1);
			if (Shape::rotateY(x1, y1) > maxY)
				maxY = Shape::rotateY(x1, y1);
			if (Shape::rotateX(x1, y1) < minX)
				minX = Shape::rotateX(x1, y1);
			if (Shape::rotateY(x1, y1) < minY)
				minY = Shape::rotateY(x1, y1);
		}
	}
	else
	{
		maxX = 0;
		maxY = 0;
		minX = 0;
		minX = 0;
	}
}

void Bspline ::findNormal()
{
	if (points.count() > 0)
	{
		minX = points[0].x();
		minY = points[0].y();
		maxX = points[0].x();
		maxY = points[0].y();

		for (int i = 1; i < points.count(); i++)
		{
			if (points[i].x() >maxX)
				maxX = points[i].x();
			if (points[i].y() > maxY)
				maxY = points[i].y();
			if (points[i].x() < minX)
				minX = points[i].x();
			if (points[i].y() < minY)
				minY = points[i].y();
		}
	}
	else
	{
		maxX = 0;
		maxY = 0;
		minX = 0;
		minX = 0;
	}
}

void Bspline::addPoint(int x, int y)
{
	QPoint a;
	a.setX(x);
	a.setY(y);
	points.push_back(a);
}

int Bspline::JieCheng(int n)
{
	if (n == 1 || n == 0)
		return 1;
	else return n*JieCheng(n - 1);
}

double Bspline::C(int n, int i)
{
	return (double)JieCheng(n) / (double)(JieCheng(i)*JieCheng(n - i));
}

void Bspline::translate(int dx, int dy)
{
	for (int i = 0; i < points.size(); i++)
	{
		points[i].setX(points[i].x() + dx);
		points[i].setY(points[i].y() + dy);
	}
	findNormal();
	Shape::setMid((minX + maxX) / 2, (minY + maxY) / 2);
	paint();
}

bool Bspline::ifSelect()
{
	find();
	int x0 = Shape::curr.x();
	int y0 = Shape::curr.y();
	if (x0 <= maxX&&x0 >= minX&&y0 <= maxY&&y0 >= minY)
	{
		return true;
	}
	else return false;
}

void Bspline::drawSelectArea()
{
	find();
	Rect *rect = new Rect;
	rect->Shape::setColor(0.5, 0.5, 0.5);
	rect->Shape::setStart(minX - 10, minY - 10);
	rect->Shape::setEnd(maxX + 10, maxY + 10);
	rect->paint();
}

int Bspline::getVecSize()
{
	return points.count();
}

void Bspline::showPoints()
{
	int x1, y1, x2, y2, i;
	for (i = 0; i < points.size(); i++)
	{
		x1 = Shape::setScaleX(points[i].x());
		y1 = Shape::setScaleY(points[i].y());

		int x3 = Shape::rotateX(x1, y1);
		int y3 = Shape::rotateY(x1, y1);
		glPointSize(5.0);
		glBegin(GL_POINTS);
		glVertex2i(x3, y3);
		glEnd();
	}
}

int Bspline::isNear(QPoint p)
{
	int x1, y1, x2, y2, i;
	for (i = 0; i < points.size(); i++)
	{
		x1 = Shape::setScaleX(points[i].x());
		y1 = Shape::setScaleY(points[i].y());
		int x3 = Shape::rotateX(x1, y1);
		int y3 = Shape::rotateY(x1, y1);
		if (p.x() < x3 + 10 && p.x() > x3 - 10 && p.y() < y3 + 10 && p.y() > y3 - 10)
			return i;
	}
	return -1;
}

void Bspline::modify(QPoint pre, QPoint curr)
{
	int r = isNear(pre);
	if (r == -1)
		return;
	else
	{
		int x = points[r].x();
		int y = points[r].y();
		points[r].setX(x + curr.x() - pre.x());
		points[r].setY(y + curr.y() - pre.y());
	}
}