#include "Polygon.h"

Poly::Poly()
{
	Shape::angle = 0;
	Shape::scaleX = 1;
	Shape::scaleY = 1;
	size = 0;
	cap = 1024;
	NEdge = new QVector<Edge>[cap];
}

Poly::~Poly()
{
}

void Poly::paint()
{
	glColor3f(Shape::currColor.Red, Shape::currColor.Green, Shape::currColor.Blue);
	glLineWidth(2.0f);
	Line::currColor = Shape::currColor;

	int x1, y1, x2, y2, i;
	qDebug() << points.count();
	for (i = 0; i < points.size() - 1; i++)
	{
		qDebug() << "come";
		qDebug() << Shape::angle;
		qDebug() << Shape::scaleX;
		qDebug() << Shape::scaleY;
		x1 = Shape::setScaleX(points[i].x());
		y1 = Shape::setScaleY(points[i].y());
		x2 = Shape::setScaleX(points[i + 1].x());
		y2 = Shape::setScaleY(points[i + 1].y());


		int x3 = Shape::rotateX(x1, y1);
		int y3 = Shape::rotateY(x1, y1);
		int x4 = Shape::rotateX(x2, y2);
		int y4 = Shape::rotateY(x2, y2);
		Line *line = new Line;
		line->setColor(Shape::currColor.Red, Shape::currColor.Green, Shape::currColor.Blue);
		line->setStart(x3, y3);
		line->setEnd(x4, y4);
		line->paint();
	}
	if (Shape::hasFill)
	{
		fill();
	}
}

bool Poly::ifSelect()
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

void Poly::find()
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

void Poly::findNormal()
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

void Poly::addPoint(int x, int y)
{
	QPoint a;
	a.setX(x);
	a.setY(y);
	points.push_back(a);
}

void Poly::drawSelectArea()
{
	find();
	Rect *rect = new Rect;
	rect->Shape::setColor(0.5, 0.5, 0.5);
	rect->Shape::setStart(minX - 10, minY - 10);
	rect->Shape::setEnd(maxX + 10, maxY + 10);
	rect->paint();
}

void Poly::translate(int dx, int dy)
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

int Poly::getMidX()
{
	find();
	return (minX + maxX) / 2;
}

int Poly::getMidY()
{
	find();
	return (minY + maxY) / 2;
}

void Poly::initNewEdgeTable()
{
	findNormal();
	if (!AET.isEmpty())
		AET.clear();
	for (int i = 0; i < cap; i++)
		if (!NEdge[i].isEmpty())
			NEdge[i].clear();

	GLint psize = points.count();
	QPoint p1, p2;
	Edge e;
	for (GLint i = 0; i < psize ; i++)
	{
		int x1 = Shape::setScaleX(points[i].x());
		int y1 = Shape::setScaleY(points[i].y());
		int x2 = Shape::setScaleX(points[(i + 1) % psize].x());
		int y2 = Shape::setScaleY(points[(i + 1) % psize].y());

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
				e.ymax = p1.y()-minY - 1;
				e.xi = p2.x();
				//NEdge[p2.y()-minY].push_back(e);
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

void Poly::fill()
{
	qDebug() << "fill";
	initNewEdgeTable();
	glColor3f(Shape::fillColor.Red, Shape::fillColor.Green, Shape::fillColor.Blue);
	glBegin(GL_LINES);
	for (int i = minY-minY; i <= maxY-minY; i++)
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
			glVertex2d((*edgeiter).xi, i+minY);
			++edgeiter;
			glVertex2d((*edgeiter).xi, i+minY);
			++edgeiter;
		}
	}
	glEnd();
}

void Poly::showPoints()
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

int Poly::isNear(QPoint p)
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

void Poly::modify(QPoint pre, QPoint curr)
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

void Poly::clip(int x1, int y1, int x2, int y2)
{
	qDebug() << "Poly clip";
	QVector<QPoint> p1, p2, p3, p4;
	int i, x, y;
	QPoint p;
	int tempx, tempy;
	QVector<QPoint> temp;
	for (i = 0; i < points.count(); i++)
	{
		int x1 = Shape::setScaleX(points[i].x());
		int y1 = Shape::setScaleY(points[i].y());
		int x2 = Shape::rotateX(x1, y1);
		int y2 = Shape::rotateY(x1, y1);
		p.setX(x2);
		p.setY(y2);
		temp.push_back(p);
	}
	for (i = 0; i < temp.count() - 1; i++)
	{
		double k = 0, b = 0;
		if (temp[i + 1].x() - temp[i].x() != 0)
		{
			k = (double)(temp[i + 1].y() - temp[i].y()) / (double)(temp[i + 1].x() - temp[i].x());
			b = temp[i].y() - k*temp[i].x();
		}
		if (temp[i].x() < x1&&temp[i + 1].x() > x1)
		{
			p.setX(x1);
			p.setY(k*x1 + b);
			p1.push_back(p);
			p.setX(temp[i + 1].x());
			p.setY(temp[i + 1].y());
			p1.push_back(p);
		}
		else if (temp[i].x()>x1&&temp[i + 1].x() > x1)
		{
			p.setX(temp[i + 1].x());
			p.setY(temp[i + 1].y());
			p1.push_back(p);
		}
		else if (temp[i].x() > x1&&temp[i + 1].x() < x1)
		{
			p.setX(x1);
			p.setY(k*x1 + b);
			p1.push_back(p);
		}
	}
	if (!p1.isEmpty())
	{
		x = p1[0].x();
		y = p1[0].y();
		p.setX(x);
		p.setY(y);
		p1.push_back(p);
	}
	for (i = 0; i < p1.count() - 1; i++)
	{
		double k = 0, b = 0;
		if (p1[i + 1].x() - p1[i].x() != 0)
		{
			k = (double)(p1[i + 1].y() - p1[i].y()) / (double)(p1[i + 1].x() - p1[i].x());
			b = p1[i].y() - k*p1[i].x();
		}
		if (p1[i].x() > x2&&p1[i + 1].x() < x2)//初始点在外面
		{
			p.setX(x2);
			p.setY(k*x2 + b);
			p2.push_back(p);
			p.setX(p1[i + 1].x());
			p.setY(p1[i + 1].y());
			p2.push_back(p);
		}
		else if (p1[i].x() < x2&&p1[i + 1].x() < x2)//两个点都在里面
		{
			p.setX(p1[i + 1].x());
			p.setY(p1[i + 1].y());
			p2.push_back(p);
		}
		else if (p1[i].x() < x2&&p1[i + 1].x() > x2)//初始点在里面
		{
			p.setX(x2);
			p.setY(k*x2 + b);
			p2.push_back(p);
		}
	}
	if (!p2.isEmpty())
	{
		p.setX(p2[0].x());
		p.setY(p2[0].y());
		p2.push_back(p);
	}
	for (i = 0; i < p2.count() - 1; i++)
	{
		double k = 0, b = 0;
		if (p2[i + 1].x() - p2[i].x() != 0)
		{
			k = (double)(p2[i + 1].y() - p2[i].y()) / (double)(p2[i + 1].x() - p2[i].x());
			b = p2[i].y() - k*p2[i].x();
		}
		if (p2[i].y() < y1&&p2[i + 1].y() > y1)//初始点在外面
		{
			if(k!=0)
				p.setX((y1 - b) / k);
			else p.setX(p2[i].x());
			p.setY(y1);
			p3.push_back(p);
			p.setX(p2[i + 1].x());
			p.setY(p2[i + 1].y());
			p3.push_back(p);
		}
		else if (p2[i].y() > y1&&p2[i + 1].y() > y1)//两个点都在里面
		{
			p.setX(p2[i + 1].x());
			p.setY(p2[i + 1].y());
			p3.push_back(p);
		}
		else if (p2[i].y() > y1&&p2[i + 1].y() < y1)//初始点在里面
		{
			if(k!=0)
				p.setX((y1 - b) / k);
			else p.setX(p2[i].x());
			p.setY(y1);
			p3.push_back(p);
		}
	}
	if (!p3.isEmpty())
	{
		p.setX(p3[0].x());
		p.setY(p3[0].y());
		p3.push_back(p);
	}
	for (i = 0; i < p3.count() - 1; i++)
	{
		double k = 0, b = 0;
		if (p3[i + 1].x() - p3[i].x() != 0)
		{
			k = (double)(p3[i + 1].y() - p3[i].y()) / (double)(p3[i + 1].x() - p3[i].x());
			b = p3[i].y() - k*p3[i].x();
		}
		if (p3[i].y() > y2&&p3[i + 1].y() < y2)//初始点在外面
		{
			if(k!=0)
				p.setX((y2 - b) / k);
			else p.setX(p3[i].x());
			p.setY(y2);
			p4.push_back(p);
			p.setX(p3[i + 1].x());
			p.setY(p3[i + 1].y());
			p4.push_back(p);
		}
		else if (p3[i].y() < y2&&p3[i + 1].y() < y2)//两个点都在里面
		{
			p.setX(p3[i + 1].x());
			p.setY(p3[i + 1].y());
			p4.push_back(p);
		}
		else if (p3[i].y() < y2&&p3[i + 1].y() > y2)//初始点在里面
		{
			if(k!=0)
				p.setX((y2 - b) / k);
			else p.setX(p3[i].x());
			p.setY(y2);
			p4.push_back(p);
		}
	}
	if (!p4.isEmpty())
	{
		p.setX(p4[0].x());
		p.setY(p4[0].y());
		p4.push_back(p);
	}
	points.clear();
	for (i = 0; i < p4.count(); i++)
		points.push_back(p4[i]);
	findNormal();
	Shape::setMid((maxX + minX) / 2, (maxY + minY) / 2);
	Shape::angle = 0;
	Shape::scaleX = 1;
	Shape::scaleY = 1;
	paint();
}

int Poly::getVecSize()
{
	return points.count();
}