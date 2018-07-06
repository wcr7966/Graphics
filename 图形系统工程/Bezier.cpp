#include "Bezier.h"



Bezier::Bezier()
{
	Shape::angle = 0;
	Shape::scaleX = 1;
	Shape::scaleY = 1;
}


Bezier::~Bezier()
{
}

void Bezier::paint()
{
	glLineWidth(2.0f);
	Line::currColor = Shape::currColor;

	//if (Shape::hasFinish == false)
	{
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
	}

	if (Shape::hasFinish)
	{
		glColor3f(Shape::currColor.Red, Shape::currColor.Green, Shape::currColor.Blue);
		QVector<QPoint>p1;
		GLfloat u = 0, x, y;
		int i = 1;
		int num = 1;
		QPoint p;
		int x1 = Shape::setScaleX(points[0].x());
		int y1 = Shape::setScaleX(points[0].y());
		p.setX(Shape::rotateX(x1, y1));
		p.setY(Shape::rotateY(x1, y1));
		glBegin(GL_POINTS);
		glVertex2i(p.x(), p.y());
		//p1.push_back(p);
		for (u = 0; u <= 1.0; u += 0.001)
		{
			x = 0;
			y = 0;
			for (int i = 0; i < points.count(); i++)
			{
				x += C(points.count() - 1, i)*pow(u, i)*pow((1 - u), (points.count() - 1 - i))*Shape::setScaleX(points[i].x());
				y += C(points.count() - 1, i)*pow(u, i)*pow((1 - u), (points.count() - 1 - i))*Shape::setScaleY(points[i].y());
			}
			p.setX(Shape::rotateX(x, y));
			p.setY(Shape::rotateY(x, y));
			glVertex2i(p.x(), p.y());
			//p1.push_back(p);
			//p1[num].setX(x);
			//p1[num].setY(y);
			num++;
		}
		//glBegin(GL_POINTS);
		//for (int k = 0; k < p1.count(); k++)
			//glVertex2i(p1[k].x(), p1[k].y());
		glEnd();
	}
}

int Bezier::getMidX()
{
	find();
	return (minX + maxX) / 2;
}

int Bezier::getMidY()
{
	find();
	return (minY + maxY) / 2;
}

void Bezier::find()
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

void Bezier::findNormal()
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

void Bezier::addPoint(int x, int y)
{
	QPoint a;
	a.setX(x);
	a.setY(y);
	points.push_back(a);
}

int Bezier::JieCheng(int n)
{
	if (n == 1 || n == 0)
		return 1;
	else return n*JieCheng(n - 1);
}

double Bezier::C(int n, int i)
{
	return (double)JieCheng(n) / (double)(JieCheng(i)*JieCheng(n - i));
}

void Bezier::translate(int dx, int dy)
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

bool Bezier::ifSelect()
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

void Bezier::drawSelectArea()
{
	find();
	Rect *rect = new Rect;
	rect->Shape::setColor(0.5, 0.5, 0.5);
	rect->Shape::setStart(minX - 10, minY - 10);
	rect->Shape::setEnd(maxX + 10, maxY + 10);
	rect->paint();
}

int Bezier::getVecSize()
{
	return points.count();
}

void Bezier::showPoints()
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

int Bezier::isNear(QPoint p)
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

void Bezier::modify(QPoint pre, QPoint curr)
{
	int r = isNear(pre);
	if (r == -1)
		return;
	else
	{
		int x = points[r].x();
		int y = points[r].y();
		points[r].setX(x + curr.x() - pre.x());
		points[r].setY(y+ curr.y() - pre.y());
	}
}