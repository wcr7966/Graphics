#include "rect.h"

Rect::Rect()
{
	Shape::angle = 0; 
	Shape::scaleX = 1;
	Shape::scaleY = 1;
	size = 0;
	cap = 1024;
	NEdge = new QVector<Edge>[cap];
}

void Rect::find()
{
	int x0 = Shape::setScaleX(vec[0].x());
	int y0 = Shape::setScaleY(vec[0].y());
	minX = Shape::rotateX(x0, y0);
	minY = Shape::rotateY(x0, y0);
	maxX = Shape::rotateX(x0, y0);
	maxY = Shape::rotateY(x0, y0);
	for (int i = 1; i < vec.count(); i++)
	{
		int x1 = Shape::setScaleX(vec[i].x());
		int y1 = Shape::setScaleY(vec[i].y());
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

void Rect::findNormal()
{
	int x1 = Shape:: start.x();
	int y1 = Shape::start.y();
	int x2 = Shape::end.x();
	int y2 = Shape::end.y();
	if (x1 < x2)
	{
		minX = x1;
		maxX = x2;
	}
	else
	{
		minX = x2;
		maxX = x1;
	}
	if (y1 < y2)
	{
		minY = y1;
		maxY = y2;
	}
	else
	{
		minY = y2;
		maxY = y1;
	}
}

void Rect::setPoint()
{
	QPoint p;
	p.setX(Shape::start.x());
	p.setY(Shape::start.y());
	vec.push_back(p);
	p.setX(Shape::end.x());
	p.setY(Shape::start.y());
	vec.push_back(p);
	p.setX(Shape::end.x());
	p.setY(Shape::end.y());
	vec.push_back(p);
	p.setX(Shape::start.x());
	p.setY(Shape::end.y());
	vec.push_back(p);
}

void Rect::changePoint()
{
	int x1 = Shape::start.x();
	int y1 = Shape::start.y();
	int x2 = Shape::end.x();
	int y2 = Shape::end.y();
	vec[0].setX(x1);
	vec[0].setY(y1);
	vec[1].setX(x2);
	vec[1].setY(y1);
	vec[2].setX(x2);
	vec[2].setY(y2);
	vec[3].setX(x1);
	vec[3].setY(y2);
}

void Rect::paint()
{
	glColor3f(Shape::currColor.Red, Shape::currColor.Green, Shape::currColor.Blue);

	int x1 = Shape::setScaleX(Shape::start.x());
	int y1 = Shape::setScaleY(Shape::start.y());
	int x2 = Shape::setScaleX(Shape::end.x());
	int y2 = Shape::setScaleY(Shape::end.y());

	int x3 = Shape::rotateX(x1, y1);
	int y3 = Shape::rotateY(x1, y1);
	int x4 = Shape::rotateX(x2, y2);
	int y4 = Shape::rotateY(x2, y2);
	int x5 = Shape::rotateX(x2, y1);
	int y5 = Shape::rotateY(x2, y1);
	int x6 = Shape::rotateX(x1, y2);
	int y6 = Shape::rotateY(x1, y2);

	Line *line1 = new Line;
	line1->setColor(Shape::currColor.Red, Shape::currColor.Green, Shape::currColor.Blue);
	line1->setStart(x3, y3);
	line1->setEnd(x5, y5);
	line1->paint();

	Line *line2 = new Line;
	line2->setColor(Shape::currColor.Red, Shape::currColor.Green, Shape::currColor.Blue);
	line2->setStart(x3, y3);
	line2->setEnd(x6, y6);
	line2->paint();

	Line *line3 = new Line;
	line3->setColor(Shape::currColor.Red, Shape::currColor.Green, Shape::currColor.Blue);
	line3->setStart(x4, y4);
	line3->setEnd(x5, y5);/Users/apple/Desktop/屏幕快照 2018-01-05 02.43.14.png
	line3->paint();

	Line *line4 = new Line;
	line4->setColor(Shape::currColor.Red, Shape::currColor.Green, Shape::currColor.Blue);
	line4->setStart(x4, y4);
	line4->setEnd(x6, y6);
	line4->paint();


	if (Shape::hasFill)
	{
		fill();
	}
}

bool Rect::ifSelect()
{
	GLint x1 = Shape::start.x();
	GLint y1 = Shape::start.y();
	GLint x2 = Shape::end.x();
	GLint y2 = Shape::end.y();
	GLint x0 = Shape::curr.x();
	GLint y0 = Shape::curr.y();

	if (x0 >= x1&&x0 <= x2&&y0 >= y1&&y0 <= y2)
	{
		return true;
	}
	else return false;
}

void Rect::drawSelectArea()
{
	findNormal();
	int x1 = Shape::setScaleX(minX - 10);
	int y1 = Shape::setScaleY(minY - 10);
	int x2 = Shape::setScaleX(maxX + 10);
	int y2 = Shape::setScaleY(maxY + 10);

	int x3 = Shape::rotateX(x1, y1);
	int y3 = Shape::rotateY(x1, y1);
	int x4 = Shape::rotateX(x2, y2);
	int y4 = Shape::rotateY(x2, y2);
	int x5 = Shape::rotateX(x2, y1);
	int y5 = Shape::rotateY(x2, y1);
	int x6 = Shape::rotateX(x1, y2);
	int y6 = Shape::rotateY(x1, y2);

	Line *line1 = new Line;
	line1->setColor(0.5, 0.5, 0.5);
	line1->setStart(x3, y3);
	line1->setEnd(x5, y5);
	line1->paint();

	Line *line2 = new Line;
	line2->setColor(0.5, 0.5, 0.5);
	line2->setStart(x3, y3);
	line2->setEnd(x6, y6);
	line2->paint();


	Line *line3 = new Line;
	line3->setColor(0.5, 0.5, 0.5);
	line3->setStart(x4, y4);
	line3->setEnd(x5, y5);
	line3->paint();

	Line *line4 = new Line;
	line4->setColor(0.5, 0.5, 0.5);
	line4->setStart(x4, y4);
	line4->setEnd(x6, y6);
	line4->paint();
}

void Rect::translate(int dx, int dy)
{
	Shape::start.setX(Shape::start.x() + dx);
	Shape::start.setY(Shape::start.y() + dy);
	Shape::end.setX(Shape::end.x() + dx);
	Shape::end.setY(Shape::end.y() + dy);
	changePoint();
	Shape::setMid((Shape::start.x() + Shape::end.x()) / 2, (Shape::start.y() + Shape::end.y()) / 2);
	paint();
}

int Rect::getMidX()
{
	return Shape::mid.x();
}
int Rect::getMidY()
{
	return Shape::mid.y();
}

void Rect::initNewEdgeTable()
{
	findNormal();
	if (!AET.isEmpty())
		AET.clear();
	for (int i = 0; i < cap; i++)
		if (!NEdge[i].isEmpty())
			NEdge[i].clear();

	GLint psize = vec.count();
	QPoint p1, p2;
	Edge e;
	for (GLint i = 0; i < psize; i++)
	{
		int x1 = Shape::setScaleX(vec[i].x());
		int y1 = Shape::setScaleY(vec[i].y());
		int x2 = Shape::setScaleX(vec[(i + 1) % psize].x());
		int y2 = Shape::setScaleY(vec[(i + 1) % psize].y());

		int x3 = Shape::rotateX(x1, y1);
		int y3 = Shape::rotateY(x1, y1);
		int x4 = Shape::rotateX(x2, y2);
		int y4 = Shape::rotateY(x2, y2);
		p1.setX(x3);
		p1.setY(y3);
		p2.setX(x4);
		p2.setY(y4);

		find();
		if (p1.y() != p2.y())
		{
			e.dx = (double)(p2.x() - p1.x()) / (p2.y() - p1.y());
			if (p2.y() > p1.y())
			{
				e.ymax = p2.y() - minY - 1;
				e.xi = p1.x();
				if (p1.y() - minY < cap)
				{
					NEdge[p1.y() - minY].push_back(e);
					size++;
				}
				else
				{
					cap = p1.y() - minY + 1;
					QVector<Edge>*newNEdge = new QVector<Edge>[cap];
					for (int i = 0; i < cap; i++)
						newNEdge[i] = NEdge[i];
					NEdge = newNEdge;
				}
			}
			else
			{
				e.ymax = p1.y() - minY - 1;
				e.xi = p2.x();
				if (p2.y() - minY < cap)
				{
					NEdge[p2.y() - minY].push_back(e);
					size++;
				}
				else
				{
					cap = p2.y() - minY + 1;
					QVector<Edge>*newNEdge = new QVector<Edge>[cap];
					for (int i = 0; i < cap; i++)
						newNEdge[i] = NEdge[i];
					NEdge = newNEdge;
				}
			}
		}
	}
}

void Rect::fill()
{
	initNewEdgeTable();
	glColor3f(Shape::fillColor.Red, Shape::fillColor.Green, Shape::fillColor.Blue);
	glBegin(GL_LINES);
	for (int i = minY - minY; i <= maxY - minY; i++)
	{
		QVector<Edge>::iterator it1 = AET.begin();
		while (it1 != AET.end())
		{
			it1->xi += it1->dx;
			if (i > it1->ymax)
				it1 = AET.erase(it1);
			else
				it1++;
		}
		QVector<Edge>::iterator it2 = NEdge[i].begin();
		while (it2 != NEdge[i].end())
		{
			AET.push_back(*it2);
			it2++;
		}

		qSort(AET.begin(), AET.end());

		QVector<Edge>::iterator edgeiter = AET.begin();
		while (edgeiter != AET.end())
		{
			glVertex2d((*edgeiter).xi, i + minY);
			++edgeiter;
			glVertex2d((*edgeiter).xi, i + minY);
			++edgeiter;
		}
	}
	glEnd();
}

void Rect::showPoints()
{
	int x1 = Shape::setScaleX(Shape::start.x());
	int y1 = Shape::setScaleY(Shape::start.y());
	int x2 = Shape::setScaleX(Shape::end.x());
	int y2 = Shape::setScaleY(Shape::end.y());

	int x3 = Shape::rotateX(x1, y1);
	int y3 = Shape::rotateY(x1, y1);
	int x4 = Shape::rotateX(x2, y2);
	int y4 = Shape::rotateY(x2, y2);
	int x5 = Shape::rotateX(x2, y1);
	int y5 = Shape::rotateY(x2, y1);
	int x6 = Shape::rotateX(x1, y2);
	int y6 = Shape::rotateY(x1, y2);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glVertex2i(x3, y3);
	glVertex2i(x4, y4);
	glVertex2i(x5, y5);
	glVertex2i(x6, y6);
	glEnd();
}
