#include "line.h"
#include "paintwidget.h"

Line::Line()
{
	angle = 0; 
	scaleX = 1;
	scaleY = 1;
}

void Line::paint()
{
	GLint x1 = setScaleX(start.x());
	GLint y1 = setScaleY(start.y());
	GLint x2 = setScaleX(end.x());
	GLint y2 = setScaleY(end.y());
	
	glColor3f(currColor.Red,currColor.Green, currColor.Blue);
	glPointSize(2);

	int dx, dy;
	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	if (dx >= dy)
	{
		int dy2 = 2 * dy;
		int dyx2 = 2 * (dy - dx);
		int p = 2 * dy - dx;
		int sx, sy, ex, ey;
		if (x1 > x2)
		{
			sx = x2;
			sy = y2;
			ex = x1;
			ey = y1;
		}
		else
		{
			sx = x1;
			sy = y1;
			ex = x2;
			ey = y2;
		}
		glBegin(GL_POINTS);
		if (x2 > x1)
		{
			glVertex2i(rotateX(sx, sy), rotateY(sx, sy));
			while (sx < ex)
			{
				sx++;
				if (p < 0)
					p += dy2;
				else
				{
					if (y2 > y1)
						sy++;
					else sy--;
					p += dyx2;
				}
				glVertex2i(rotateX(sx, sy), rotateY(sx, sy));
			}
		}
		else
		{
			glVertex2i(rotateX(ex, ey), rotateY(ex, ey));
			while (ex > sx)
			{
				ex--;
				if (p < 0)
					p += dy2;
				else
				{
					if (y2 > y1)
						ey++;
					else ey--;
					p += dyx2;
				}
				glVertex2i(rotateX(ex, ey), rotateY(ex, ey));
			}
		}
		glEnd();
		glFlush();
	}
	else
	{
		int dx2 = 2 * dx;
		int dxy2 = 2 * (dx - dy);
		int p = dx2 - dy;
		int sx, sy, ex, ey;
		if (y1 > y2)
		{
			sx = x2;
			sy = y2;
			ex = x1;
			ey = y1;
		}
		else
		{
			sx = x1;
			sy = y1;
			ex = x2;
			ey = y2;
		}
		glBegin(GL_POINTS);
		if (y2 > y1)
		{
			glVertex2i(rotateX(sx, sy), rotateY(sx, sy));
			while (sy < ey)
			{
				sy++;
				if (p < 0)
					p += dx2;
				else
				{
					if (x2 > x1)
						sx++;
					else sx--;
					p += dxy2;
				}
				glVertex2i(rotateX(sx, sy), rotateY(sx, sy));
			}
		}
		else
		{
			glVertex2i(rotateX(ex, ey), rotateY(ex, ey));
			while (ey > sy)
			{
				ey--;
				if (p < 0)
					p += dx2;
				else
				{
					if (x2 > x1)
						ex++;
					else ex--;
					p += dxy2;
				}
				glVertex2i(rotateX(ex, ey), rotateY(ex, ey));
			}
		}
		glEnd();
		glFlush();
	}
}

bool Line::ifSelect()
{
	int maxx, minx, maxy, miny;
	GLint x1 = setScaleX(start.x());
	GLint y1 = setScaleY(start.y());
	GLint x2 = setScaleX(end.x());
	GLint y2 = setScaleY(end.y());

	if (x1<x2)
	{
		minx = x1;
		maxx = x2;
	}
	else
	{
		maxx = x1;
		minx = x2;
	}
	if (y1 < y2)
	{
		miny = y1;
		maxy = y2;
	}
	else
	{
		maxy = y1;
		miny = y2;
	}
	int x0, y0;
	x0 = curr.x();
	y0 = curr.y();
	if (x0< minx || y0 > maxy || x0 > maxx || y0 < miny)
	{
		return false;
	}
	else
	{
		k = (GLfloat)(y2 - y1) / (GLfloat)(x2 - x1);
		b = GLfloat((GLfloat)y1 - k*(GLfloat)x1);
		GLfloat d = abs((k*(GLfloat)x0 - (GLfloat)y0 + b) / sqrt(k*k + (GLfloat)1));
		if (d <= 50)
		{
			return true;
		}
		else return false;
	}
}

void Line::drawSelectArea()
{
	int x1 = setScaleX(start.x());
	int y1 = setScaleY(start.y());
	int x2 = setScaleX(end.x());
	int y2 = setScaleY(end.y());

	int x3 = rotateX(x1, y1);
	int y3 = rotateY(x1, y1);
	int x4 = rotateX(x2, y2);
	int y4 = rotateY(x2, y2);
	if (x3 < x4&&y3 < y4)
	{
		Line *line1 = new Line;
		line1->setColor(0.5, 0.5, 0.5);
		line1->setStart(x3 - 10, y3 - 10);
		line1->setEnd(x3 - 10, y4 + 10);
		line1->paint();
		Line *line2 = new Line;
		line2->setColor(0.5, 0.5, 0.5);
		line2->setStart(x3 - 10, y3 - 10);
		line2->setEnd(x4 + 10, y3 - 10);
		line2->paint();
		Line *line3 = new Line;
		line3->setColor(0.5, 0.5, 0.5);
		line3->setStart(x4 + 10, y3 - 10);
		line3->setEnd(x4 + 10, y4 + 10);
		line3->paint();
		Line *line4 = new Line;
		line4->setColor(0.5, 0.5, 0.5);
		line4->setStart(x4 + 10, y4 + 10);
		line4->setEnd(x3 - 10, y4 + 10);
		line4->paint();
	}
	else if (x3 < x4&&y3 >= y4)
	{
		Line *line1 = new Line;
		line1->setColor(0.5, 0.5, 0.5);
		line1->setStart(x3 - 10, y3 + 10);
		line1->setEnd(x3 - 10, y4 - 10);
		line1->paint();
		Line *line2 = new Line;
		line2->setColor(0.5, 0.5, 0.5);
		line2->setStart(x3 - 10, y3 +10);
		line2->setEnd(x4 + 10, y3 + 10);
		line2->paint();
		Line *line3 = new Line;
		line3->setColor(0.5, 0.5, 0.5);
		line3->setStart(x4 + 10, y3 + 10);
		line3->setEnd(x4 + 10, y4 - 10);
		line3->paint();
		Line *line4 = new Line;
		line4->setColor(0.5, 0.5, 0.5);
		line4->setStart(x4 + 10, y4 - 10);
		line4->setEnd(x3 - 10, y4 - 10);
		line4->paint();
	}
	else if (x3 >= x4&&y3 < y4)
	{
		Line *line1 = new Line;
		line1->setColor(0.5, 0.5, 0.5);
		line1->setStart(x3 + 10, y3 - 10);
		line1->setEnd(x3 + 10, y4 + 10);
		line1->paint();
		Line *line2 = new Line;
		line2->setColor(0.5, 0.5, 0.5);
		line2->setStart(x3 + 10, y3 - 10);
		line2->setEnd(x4 - 10, y3 - 10);
		line2->paint();
		Line *line3 = new Line;
		line3->setColor(0.5, 0.5, 0.5);
		line3->setStart(x4 - 10, y3 - 10);
		line3->setEnd(x4 - 10, y4 + 10);
		line3->paint();
		Line *line4 = new Line;
		line4->setColor(0.5, 0.5, 0.5);
		line4->setStart(x4 - 10, y4 + 10);
		line4->setEnd(x3 + 10, y4 + 10);
		line4->paint();
	}
	else
	{
		Line *line1 = new Line;
		line1->setColor(0.5, 0.5, 0.5);
		line1->setStart(x3 + 10, y3 + 10);
		line1->setEnd(x3 + 10, y4 - 10);
		line1->paint();
		Line *line2 = new Line;
		line2->setColor(0.5, 0.5, 0.5);
		line2->setStart(x3 + 10, y3 + 10);
		line2->setEnd(x4 - 10, y3 + 10);
		line2->paint();
		Line *line3 = new Line;
		line3->setColor(0.5, 0.5, 0.5);
		line3->setStart(x4 - 10, y3 + 10);
		line3->setEnd(x4 - 10, y4 - 10);
		line3->paint();
		Line *line4 = new Line;
		line4->setColor(0.5, 0.5, 0.5);
		line4->setStart(x4 - 10, y4 - 10);
		line4->setEnd(x3 + 10, y4 - 10);
		line4->paint();
	}
}

void Line::translate(int dx, int dy)
{
	int x1 = start.x() + dx;
	int y1 = start.y() + dy;
	int x2 = end.x() + dx;
	int y2 = end.y() + dy;
	start.setX(x1);
	start.setY(y1);
	end.setX(x2);
	end.setY(y2);
	setMid((start.x() + end.x()) / 2, (start.y() + end.y()) / 2);
	paint();
}

int Line::getMidX()
{
	return mid.x();
}
int Line::getMidY()
{
	return mid.y();
}

void Line::showPoints()
{
	int x1 = setScaleX(start.x());
	int y1 = setScaleY(start.y());
	int x2 = setScaleX(end.x());
	int y2 = setScaleY(end.y());
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glVertex2i(rotateX(x1, y1), rotateY(x1, y1));
	glVertex2i(rotateX(x2, y2), rotateY(x2, y2));
	glEnd();
}

int Line::isNear(QPoint p)
{
	int x1, y1, x2, y2, i;
	x1 = Shape::setScaleX(start.x());
	y1 = Shape::setScaleY(start.y());
	x2 = Shape::setScaleX(end.x());
	y2 = Shape::setScaleY(end.y());
	int x3 = Shape::rotateX(x1, y1);
	int y3 = Shape::rotateY(x1, y1);
	int x4 = Shape::rotateX(x2, y2);
	int y4 = Shape::rotateY(x2, y2);
	if (p.x() < x3 + 10 && p.x() > x3 - 10 && p.y() < y3 + 10 && p.y() > y3 - 10)
		return 0;
	else if (p.x() < x4 + 10 && p.x() > x4 - 10 && p.y() < y4 + 10 && p.y() > y4 - 10)
		return 1;
	else return -1;

}

void Line::modify(QPoint pre, QPoint curr)
{
	int r = isNear(pre);
	if (r == -1)
		return;
	else if(r==0)
	{
		int x1 = start.x();
		int y1 = start.y();
		start.setX(x1 + curr.x() - pre.x());
		start.setY(y1 + curr.y() - pre.y());
	}
	else if (r == 1)
	{
		int x1 = end.x();
		int y1 = end.y();
		end.setX(x1 + curr.x() - pre.x());
		end.setY(y1 + curr.y() - pre.y());
	}
}