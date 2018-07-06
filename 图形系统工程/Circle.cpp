#include "Circle.h"



Circle::Circle()
{
	Shape::angle = 0;
	Shape::scaleX = 1;
	Shape::scaleY = 1;
}


Circle::~Circle()
{
}

void Circle::paint()
{
	GLint x1 = Shape::setScaleX(Shape::start.x());
	GLint y1 = Shape::setScaleY(Shape::start.y());
	GLint x2 = Shape::setScaleX(Shape::end.x());
	GLint y2 = Shape::setScaleY(Shape::end.y());

	glColor3f(Shape::currColor.Red, Shape::currColor.Green, Shape::currColor.Blue);
	glLineWidth(2.0f);

	GLfloat X = (x1 + x2) / 2;
	GLfloat Y = (y1 + y2) / 2;
	GLfloat R = sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)) / 2;
	GLfloat d = 1.25 - R;

	glPointSize(2);
	glBegin(GL_POINTS);
	int x = 0, y = R;
	glVertex2i(Shape::rotateX(x + X, y + Y), Shape::rotateY(x + X, y + Y));
	while (x<y)
	{
		if (d < 0)
			d += 2 * x + 3;
		else
		{
			d += 2 * (x + 1 - y) + 1;
			y--;
		}
		x++;
		glColor3f(Shape::currColor.Red, Shape::currColor.Green, Shape::currColor.Blue);
		glVertex2i(Shape::rotateX(x + X, y + Y), Shape::rotateY(x + X, y + Y));
		glVertex2i(Shape::rotateX(-x + X, y + Y), Shape::rotateY(-x + X, y + Y));
		glVertex2i(Shape::rotateX(-x + X, -y + Y), Shape::rotateY(-x + X, -y + Y));
		glVertex2i(Shape::rotateX(x + X, -y + Y), Shape::rotateY(x + X, -y + Y));
		glVertex2i(Shape::rotateX(y + X, x + Y), Shape::rotateY(y + X, x + Y));
		glVertex2i(Shape::rotateX(-y + X, x + Y), Shape::rotateY(-y + X, x + Y));
		glVertex2i(Shape::rotateX(-y + X, -x + Y), Shape::rotateY(-y + X, -x + Y));
		glVertex2i(Shape::rotateX(y + X, -x + Y), Shape::rotateY(y + X, -x + Y));
		if (Shape::hasFill)
		{
			Line *line1 = new Line;
			line1->setColor(Shape::fillColor.Red, Shape::fillColor.Green, Shape::fillColor.Blue);
			line1->setStart(Shape::rotateX(x + X - 2, y + Y), Shape::rotateY(x + X - 2, y + Y));
			line1->setEnd(Shape::rotateX(-x + X + 2, y + Y), Shape::rotateY(-x + X + 2, y + Y));
			line1->paint();

			Line *line2 = new Line;
			line2->setColor(Shape::fillColor.Red, Shape::fillColor.Green, Shape::fillColor.Blue);
			line2->setStart(Shape::rotateX(x + X -2, -y + Y ), Shape::rotateY(x + X - 2, -y + Y));
			line2->setEnd(Shape::rotateX(-x + X + 2, -y + Y), Shape::rotateY(-x + X + 2, -y + Y));
			line2->paint();

			Line *line3 = new Line;
			line3->setColor(Shape::fillColor.Red, Shape::fillColor.Green, Shape::fillColor.Blue);
			line3->setStart(Shape::rotateX(y + X - 2, x + Y), Shape::rotateY(y + X - 2, x + Y));
			line3->setEnd(Shape::rotateX(-y + X + 2, x + Y), Shape::rotateY(-y + X + 2, x + Y));
			line3->paint();

			Line *line4 = new Line;
			line4->setColor(Shape::fillColor.Red, Shape::fillColor.Green, Shape::fillColor.Blue);
			line4->setStart(Shape::rotateX(y + X - 2, -x + Y), Shape::rotateY(y + X - 2, -x + Y));
			line4->setEnd(Shape::rotateX(-y + X + 2, -x + Y), Shape::rotateY(-y + X + 2, -x + Y));
			line4->paint();
		}

	}
	glEnd();
	glFlush();
} 

bool Circle::ifSelect()
{
	GLint x1 = Shape::start.x();
	GLint y1 = Shape::start.y();
	GLint x2 = Shape::end.x();
	GLint y2 = Shape::end.y();
	GLint x0 = Shape::curr.x();
	GLint y0 = Shape::curr.y();

	GLfloat X = (x1 + x2) / 2;
	GLfloat Y = (y1 + y2) / 2;
	GLfloat R = sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)) / 2;
	GLfloat d = sqrt((x0 - X)*(x0 - X) + (y0 - Y)*(y0 - Y));
	if (d <= R)
	{
		qDebug() << "circle is choosed";
		return true;
	}
	else return false;
}

void Circle::drawSelectArea()
{
	int x1 = Shape::start.x();
	int y1 = Shape::start.y();
	int x2 = Shape::end.x();
	int y2 = Shape::end.y();

	Rect *rect = new Rect;
	rect->Shape::setColor(1, 0.5, 0.5);
	GLfloat X = (x1 + x2) / 2;
	GLfloat Y = (y1 + y2) / 2;
	GLfloat R = sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)) / 2;

	int minx = int(X - R - 10);
	int miny = int(Y - R - 10);
	int maxx = int(X + R + 10);
	int maxy = int(Y + R + 10);

	int x3 = rotateX(minx, miny);
	int y3 = rotateY(minx, miny);
	int x4 = rotateX(maxx, maxy);
	int y4 = rotateY(maxx, maxy);
	rect->Shape::setColor(0.5, 0.5, 0.5);
	rect->Shape::setStart(x3,y3);
	rect->Shape::setEnd(x4, y4);
	rect->paint();
}

void Circle::translate(int dx, int dy)
{	
	Shape::start.setX(Shape::start.x() + dx);
	Shape::start.setY(Shape::start.y() + dy);
	Shape::end.setX(Shape::end.x() + dx);
	Shape::end.setY(Shape::end.y() + dy);
	Shape::setMid((Shape::start.x() + Shape::end.x()) / 2, (Shape::start.y() + Shape::end.y()) / 2);
	paint();
}

int Circle::getMidX()
{
	return Shape::mid.x();
}

int Circle::getMidY()
{
	return Shape::mid.y();
}

void Circle::setScale()
{
	double x1 = Shape::pre.x();
	double x2 = Shape::curr.x();
	double x0 = Shape::mid.x();
	Shape::scaleX *=(x2 - x0) / (x1 - x0);
	Shape:: scaleY *= (x2 - x0) / (x1 - x0);
}

int Circle::rotateX(int x, int y)
{
	int x0 = Shape::mid.x();
	int y0 = Shape::mid.y();
	int r;
	r = x*Shape::scaleX + x0*(1 - Shape::scaleX);
	return r;
}

int Circle::rotateY(int x, int y)
{
	int x0 = Shape::mid.x();
	int y0 = Shape::mid.y();
	int r;
	r = y*Shape::scaleY + y0*(1 - Shape::scaleY);
	return r;
}

void Circle::fill()
{
	int x1 = Shape::start.x();
	int y1 = Shape::start.y();
	int x2 = Shape::end.x();
	int y2 = Shape::end.y();

	GLfloat X = (x1 + x2) / 2;
	GLfloat Y = (y1 + y2) / 2;
	GLfloat R = sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)) / 2;

	int minY = Shape::mid.y() - R;
	int maxY = Shape::mid.y() + R;
}
