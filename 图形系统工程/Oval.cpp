#include "Oval.h"



Oval::Oval()
{
	Shape::angle = 0;
	Shape::scaleX = 1;
	Shape::scaleY = 1;
}


Oval::~Oval()
{
}

void Oval::paint()
{
	GLint x1 = Shape::setScaleX(Shape::start.x());
	GLint y1 = Shape::setScaleY(Shape::start.y());
	GLint x2 = Shape::setScaleX(Shape::end.x());
	GLint y2 = Shape::setScaleY(Shape::end.y());

	glColor3f(Shape::currColor.Red, Shape::currColor.Green, Shape::currColor.Blue);
	glLineWidth(2.0f);

	GLint xc = (x1 + x2) / 2;
	GLint yc = (y1 + y2) / 2;
	GLint rx = abs(x2 - x1) / 2;
	GLint ry = abs(y2 - y1) / 2;
	int sqrx = rx*rx;
	int sqry = ry*ry;
	int x = 0, y = ry;
	int d = 4 * sqry - 4 * sqrx*ry + sqrx;

	glPointSize(2);
	glBegin(GL_POINTS);
	glVertex2i(Shape::rotateX(x + xc, y + yc), Shape::rotateY(x + xc, y + yc));
	glVertex2i(Shape::rotateX(x + xc, -y + yc), Shape::rotateY(x + xc, -y + yc));
	glVertex2i(Shape::rotateX(-x + xc, -y + yc), Shape::rotateY(-x + xc, -y + yc));
	glVertex2i(Shape::rotateX(-x + xc, y + yc), Shape::rotateY(-x + xc, y + yc));
	int dx = (int)((double)sqrx / sqrt((double)(sqrx + sqry)));

	while (x<=dx)
	{
		x++;
		if (d < 0)
			d += sqry*(8 * x + 4);
		else
		{
			y--;
			d += sqry*(8 * x + 4) + sqrx*(-8 * y);
		}
		glVertex2i(Shape::rotateX(x + xc, y + yc), Shape::rotateY(x + xc, y + yc));
		glVertex2i(Shape::rotateX(x + xc, -y + yc), Shape::rotateY(x + xc, -y + yc));
		glVertex2i(Shape::rotateX(-x + xc, -y + yc), Shape::rotateY(-x + xc, -y + yc));
		glVertex2i(Shape::rotateX(-x + xc, y + yc), Shape::rotateY(-x + xc, y + yc));
		if (Shape::hasFill)
		{
			Line *line1 = new Line;
			line1->setColor(Shape::fillColor.Red, Shape::fillColor.Green, Shape::fillColor.Blue);
			line1->setStart(Shape::rotateX(x + xc, y + yc), Shape::rotateY(x + xc, y + yc));
			line1->setEnd(Shape::rotateX(-x + xc, y + yc), Shape::rotateY(-x + xc, y + yc));
			line1->paint();

			Line *line2 = new Line;
			line2->setColor(Shape::fillColor.Red, Shape::fillColor.Green, Shape::fillColor.Blue);
			line2->setStart(Shape::rotateX(x + xc, -y + yc), Shape::rotateY(x + xc, -y + yc));
			line2->setEnd(Shape::rotateX(-x + xc, -y + yc), Shape::rotateY(-x + xc, -y + yc));
			line2->paint();
		}
	}
	d = sqry*(2 * x + 1)*(2 * x + 1) + 4* sqrx*(y - 1)*(y - 1) - 4* sqrx*sqry;
	while (y >= 0)
	{
		y--;
		if (d <= 0)
		{
			x++;
			d += sqry*(8 * x) + sqrx*(-8 * y + 4);
		}
		else
			d += sqrx*(-8 * y + 4);
		glVertex2i(Shape::rotateX(x + xc, y + yc), Shape::rotateY(x + xc, y + yc));
		glVertex2i(Shape::rotateX(x + xc, -y + yc), Shape::rotateY(x + xc, -y + yc));
		glVertex2i(Shape::rotateX(-x + xc, -y + yc), Shape::rotateY(-x + xc, -y + yc));
		glVertex2i(Shape::rotateX(-x + xc, y + yc), Shape::rotateY(-x + xc, y + yc));
		if (Shape::hasFill)
		{
			Line *line1 = new Line;
			line1->setColor(Shape::fillColor.Red, Shape::fillColor.Green, Shape::fillColor.Blue);
			line1->setStart(Shape::rotateX(x + xc, y + yc), Shape::rotateY(x + xc, y + yc));
			line1->setEnd(Shape::rotateX(-x + xc, y + yc), Shape::rotateY(-x + xc, y + yc));
			line1->paint();

			Line *line2 = new Line;
			line2->setColor(Shape::fillColor.Red, Shape::fillColor.Green, Shape::fillColor.Blue);
			line2->setStart(Shape::rotateX(x + xc, -y + yc), Shape::rotateY(x + xc, -y + yc));
			line2->setEnd(Shape::rotateX(-x + xc, -y + yc), Shape::rotateY(-x + xc, -y + yc));
			line2->paint();
		}
	}
	glEnd();
	glFlush();
}

bool Oval::ifSelect()
{
	GLint x1 = Shape::start.x();
	GLint y1 = Shape::start.y();
	GLint x2 = Shape::end.x();
	GLint y2 = Shape::end.y();
	GLint x0 = Shape::curr.x();
	GLint y0 = Shape::curr.y();

	GLint xc = (x1 + x2) / 2;
	GLint yc = (y1 + y2) / 2;
	GLint rx = abs(x2 - x1) / 2;
	GLint ry = abs(y2 - y1) / 2;

	int sqrx = rx*rx;
	int sqry = ry*ry;

	int d = sqry*(x0 - xc)*(x0 - xc) + sqrx*(y0 - yc)*(y0 - yc);
	if (d < sqry*sqrx)
	{
		qDebug() << "oval is choosed";
		return true;
	}
	else return false;
}

void Oval::drawSelectArea()
{
	Rect *rect = new Rect;
	int x1 = Shape::setScaleX(Shape::start.x() - 10);
	int y1 = Shape::setScaleY(Shape::start.y() - 10);
	int x2 = Shape::setScaleX(Shape::end.x() + 10);
	int y2 = Shape::setScaleY(Shape::end.y() + 10);

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

void Oval::translate(int dx, int dy)
{
	Shape::start.setX(Shape::start.x() + dx);
	Shape::start.setY(Shape::start.y() + dy);
	Shape::end.setX(Shape::end.x() + dx);
	Shape::end.setY(Shape::end.y() + dy);
	Shape::setMid((Shape::start.x() + Shape::end.x()) / 2, (Shape::start.y() + Shape::end.y()) / 2);
	paint();
}

int Oval::getMidX()
{
	return Shape::mid.x();
}
int Oval::getMidY()
{
	return Shape::mid.y();
}