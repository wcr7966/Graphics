#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent)
	: QGLWidget(parent), currShapeChoice(Shape::LINE), currColorChoice(Shape::Black), fillColorChoice(currColorChoice), currSelect(DRAW), shape(NULL),
	currConv(TRANSLATE), isFill(false), ifShow(false), clipRect(NULL), ifClipFinish(false), release(false), rTri(0.0), rQuad(15.0)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	setFixedSize(800, 520);
	index = -1;
}

void PaintWidget::clear()
{
	shapeList.clear();
	index = -1;
	updateGL();
}

void PaintWidget::save()
{
	screenshot("mySave.png");
}



void PaintWidget::initializeGL()
{
	// 启用阴影平滑
	glShadeModel(GL_SMOOTH);
	// 黑色背景
	glClearColor(1.0, 1.0, 1.0, 0.0);
	// 设置深度缓存
	glClearDepth(1.0);
	// 启用深度测试
	glEnable(GL_DEPTH_TEST);
	// 所作深度测试的类型
	glDepthFunc(GL_LEQUAL);
	// 告诉系统对透视进行修正
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	resizeGL(800, 520);
}

void PaintWidget::resizeGL(int w, int h)
{
	if (!ifShow)
	{
		qDebug() << w;
		qDebug() << h;
		GLfloat Sizew = size().width();
		GLfloat Sizeh = size().height();
		qDebug() << Sizew << " " << Sizeh << endl;
		GLfloat rate;
		// 防止窗口大小变为0
		if (h == 0 || w == 0)
		{
			rate = 1.0f;
		}
		else if (w < h)
		{
			rate = h / w;
			Sizew = w;
			Sizeh = h*rate;
		}
		else
		{
			rate = w / h;
			Sizew = rate*w;
			Sizeh = h;
		}
		// 重置当前的视口
		glViewport(0, 0, (GLint)w, (GLint)h);
		/*if (w < h)
			glOrtho(0.0, Sizew, Sizeh, 0.0, 1.0, -1.0);
		else
			glOrtho(0.0, Sizew, Sizeh, 0.0, 1.0, -1.0);*/
			// 选择投影矩阵

		glOrtho(0.0, size().width(), size().height(), 0.0, 1.0, -1.0);
		glMatrixMode(GL_PROJECTION);
		// 重置投影矩阵
		glLoadIdentity();
	}
	else
	{
		if (h == 0)
		{
			h = 1;
		}
		glViewport(0, 0, (GLint)w, (GLint)h);
		//glMatrixMode(GL_PROJECTION);
		//glLoadIdentity();
		glOrtho(-1.0, -1.0, -1.0, 1.0, -1.0, 1.0);
		gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	
}

void PaintWidget::paintGL()
{
	//glMatrixMode(GL_PROJECTION);
	// 清除屏幕和深度缓存
	if (!ifShow)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		if (clipRect&&ifClipFinish == false)
			clipRect->paint();
		if (index != -1)
		{
			if (clipRect && ifClipFinish)
			{
				qDebug() << ifClipFinish;
				shapeList[index]->clip(clipRect->startPoint().x(), clipRect->startPoint().y(),
					clipRect->endPoint().x(), clipRect->endPoint().y());
				ifClipFinish = false;
				clipRect = NULL;
			}
			if (shapeList[index]->getVecSize() != 0)
			{
				shapeList[index]->drawSelectArea();
				shapeList[index]->showPoints();
			}
		}
		foreach(Shape * shape, shapeList) {
			shape->paint();
		}
	}
	else
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		/*glTranslatef(-1.5, 0.0, -6.0);
		glRotatef(rTri, 0.0, 1.0, 0.0);
		glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(-1.0, -1.0, 1.0);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(1.0, -1.0, 1.0);

		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(1.0, -1.0, 1.0);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(1.0, -1.0, -1.0);

		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(1.0, -1.0, -1.0);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(-1.0, -1.0, -1.0);

		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(-1.0, -1.0, -1.0);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(-1.0, -1.0, 1.0);
		glEnd();*/

		glLoadIdentity();
		glTranslatef(0.0, 0.0, -7.0);
		glRotatef(rQuad, 1.0, 1.0, 1.0);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_QUADS);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(1.0, 1.0, -1.0);//
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-1.0, 1.0, -1.0);//
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(-1.0, 1.0, 1.0);//
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(1.0, 1.0, 1.0);//

		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(1.0, -1.0, 1.0);//
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(-1.0, -1.0, 1.0);//
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(-1.0, -1.0, -1.0);//
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(1.0, -1.0, -1.0);//

		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(1.0, 1.0, 1.0);//
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(-1.0, 1.0, 1.0);//
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(-1.0, -1.0, 1.0);//
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(1.0, -1.0, 1.0);//

		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(1.0, -1.0, -1.0);//
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(-1.0, -1.0, -1.0);//
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-1.0, 1.0, -1.0);//
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(1.0, 1.0, -1.0);//

		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(-1.0, 1.0, 1.0);//
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-1.0, 1.0, -1.0);//
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(-1.0, -1.0, -1.0);//
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(-1.0, -1.0, 1.0);//

		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(1.0, 1.0, -1.0);//
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(1.0, 1.0, 1.0);//
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(1.0, -1.0, 1.0);//
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(1.0, -1.0, -1.0);//
		glEnd();

	}
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
	if (currSelect ==DRAW)
	{
		if (index != -1)
		{
			index = -1;
			updateGL();
		}
		if (release == true)
		{
			isFill = false;
			switch (currShapeChoice)
			{
			case Shape::LINE:
			{
				shape = new Line;
				break;
			}
			case Shape::RECT:
			{
				shape = new Rect;
				break;
			}
			case Shape::CIRCLE:
			{
				shape = new Circle;
				break;
			}
			case Shape::OVAL:
			{
				shape = new Oval;
				break;
			}
			case Shape::POLYGON:
			{
				shape = new Poly;
				break;
			}
			case Shape::BEZIER:
				shape = new Bezier;
				break;
			case Shape::BSPLINE:
				shape = new Bspline;
				break;
			}
			switch (currColorChoice)
			{
			case Shape::Red:
			{
				shape->setColor(1.0, 0.0, 0.0);
				break;
			}
			case Shape::Blue:
			{
				shape->setColor(0.0, 0.0, 1.0);
				break;
			}
			case Shape::Green:
			{
				shape->setColor(0.0, 1.0, 0.0);
				break;
			}
			case Shape::White:
			{
				shape->setColor(1.0, 1.0, 1.0);
				break;
			}
			case Shape::Black:
			{
				shape->setColor(0.0, 0.0, 0.0);
				break;
			}
			}

			if (shape != NULL&&currShapeChoice != Shape::POLYGON && currShapeChoice != Shape::BEZIER && currShapeChoice != Shape::BSPLINE)
			{
				release = false;
				shapeList << shape;
				shape->setStart(event->pos().x(), event->pos().y());
				shape->setEnd(event->pos().x(), event->pos().y());
			}
			else if (shape != NULL&&currShapeChoice == Shape::POLYGON)
			{
				release = false;
				first = event->pos();
				shapeList << shape;
				shape->setStart(event->pos().x(), event->pos().y());
				shape->setEnd(event->pos().x(), event->pos().y());
				shape->addPoint(event->pos().x(), event->pos().y());
			}
			else if (shape != NULL && (currShapeChoice == Shape::BEZIER || currShapeChoice == Shape::BSPLINE))
			{
				release = false;
				shapeList << shape;
				shape->setStart(event->pos().x(), event->pos().y());
				shape->setEnd(event->pos().x(), event->pos().y());
				shape->addPoint(event->pos().x(), event->pos().y());
			}
		}

		else if (shape != NULL&&currShapeChoice == Shape::POLYGON)
		{
			shape->setStart(event->pos().x(), event->pos().y());
			shape->setEnd(event->pos().x(), event->pos().y());
			if (event->pos().x() < first.x() + 10 && event->pos().x() > first.x() - 10 && event->pos().y() < first.y() + 10 && event->pos().y() > first.y() - 10)
			{
				shape->addPoint(first.x(), first.y());
				shape->setMid(shape->getMidX(), shape->getMidY());
				shape->initNewEdgeTable();
				release = true;
			}
			else shape->addPoint(event->pos().x(), event->pos().y());
			updateGL();
		}
		else if (shape != NULL && (currShapeChoice == Shape::BEZIER || currShapeChoice == Shape::BSPLINE))
		{
			shape->setStart(event->pos().x(), event->pos().y());
			shape->setEnd(event->pos().x(), event->pos().y());
			shape->setMid(shape->getMidX(), shape->getMidY());
			if (event->button() == Qt::RightButton)
			{
				shape->addPoint(event->pos().x(), event->pos().y());
				shape->setMid(shape->getMidX(), shape->getMidY());
				release = true;
			}
			else shape->addPoint(event->pos().x(), event->pos().y());
			if (shape->getVecSize() >= 4)
				shape->setHasFinish();
			updateGL();
		}
	}
	else if (currSelect == SELECT)
	{
		release = false;
		pre = event->pos();
		curr = event->pos();
		for (int i = shapeList.count() - 1; i >= 0; i--)
		{
			shapeList[i]->setCurr(event->pos().x(), event->pos().y());
			if (shapeList[i]->ifSelect() == true)
			{
				index = i;
				updateGL();
				break;
			}
		}
		if (index != -1)
		{
			shapeList[index]->setPre(event->pos().x(), event->pos().y());
			shapeList[index]->setCurr(event->pos().x(), event->pos().y());
		}
		if (currConv == FILL)
		{
			switch (fillColorChoice)
			{
			case Shape::Red:
			{
				shapeList[index]->setFillColor(1.0, 0.0, 0.0);
				break;
			}
			case Shape::Blue:
			{
				shapeList[index]->setFillColor(0.0, 0.0, 1.0);
				break;
			}
			case Shape::Green:
			{
				shapeList[index]->setFillColor(0.0, 1.0, 0.0);
				break;
			}
			case Shape::White:
			{
				shapeList[index]->setFillColor(1.0, 1.0, 1.0);
				break;
			}
			case Shape::Black:
			{
				shapeList[index]->setFillColor(0.0, 0.0, 0.0);
				break;
			}
			}
			shapeList[index]->setHasFill();
			updateGL();
		}
		else if (currConv == MODIFY)
		{
			updateGL();
		}
		else if (currConv == CLIP)
		{
			clipRect = new Rect;
			clipRect->setColor(0.8, 0.8, 0.8);
			clipRect->setStart(event->pos().x(), event->pos().y());
			clipRect->setEnd(event->pos().x(), event->pos().y());
			//qDebug() << "start:"<<event->pos();
		}
	}
	else if (currSelect == SHOW)
	{
		rTri += 2;
		rQuad -= 15;
		updateGL();
	}
	else
	{
		qDebug() << "Has no select";
	}
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
	if (currSelect == DRAW)
	{
		if (shape && !release && currShapeChoice != Shape::POLYGON && currShapeChoice != Shape::BEZIER && currShapeChoice != Shape::BSPLINE)
		{
			shape->setEnd(event->pos().x(), event->pos().y());
			updateGL();
		}
	}
	else if (currSelect == SELECT&&currConv == TRANSLATE)
	{
		if (index != -1 && !release)
		{
			curr = event->pos();
			GLint dx, dy;
			dx = curr.x() - pre.x();
			dy = curr.y() - pre.y();
			pre = curr;
			shapeList[index]->translate(dx, dy);
			updateGL();
		}
	}
	else if (currSelect == SELECT && currConv == ROTATE)
	{
		if (index != -1 && !release)
		{
			curr = event->pos();
			shapeList[index]->setCurr(event->pos().x(), event->pos().y());
			shapeList[index]->setAngle();
			shapeList[index]->setPre(curr.x(), curr.y());
			pre = curr;
			updateGL();
		}
	}
	else if (currSelect == SELECT&&currConv == SCALE)
	{
		if (index != -1 && !release)
		{
			curr = event->pos();
			shapeList[index]->setCurr(event->pos().x(), event->pos().y());
			if (curr.x() != shapeList[index]->midPoint().x() && curr.y() != shapeList[index]->midPoint().y() && pre.x() != shapeList[index]->midPoint().x() && pre.y() != shapeList[index]->midPoint().y())
				shapeList[index]->setScale();
			shapeList[index]->setPre(curr.x(), curr.y());
			pre = curr;
			updateGL();
		}
	}
	else if (currSelect == SELECT&&currConv == MODIFY)
	{
		if (index != -1 && !release)
		{
			curr = event->pos();
			shapeList[index]->setCurr(event->pos().x(), event->pos().y());
			shapeList[index]->setPre(curr.x(), curr.y());
			shapeList[index]->modify(pre, curr);
			pre = curr;
			updateGL();
		}
	}
	else if (currSelect == SELECT&&currConv == FILL)
	{
		updateGL();
	}
	else if (currSelect == SELECT&&currConv == CLIP)
	{
		clipRect->setEnd(event->pos().x(), event->pos().y());
		updateGL();
	}
	else if(currSelect==SELECT)
	{ 
		qDebug() << "not translate";
	}
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
	curr = event->pos();
	if (currShapeChoice != Shape::POLYGON && currShapeChoice != Shape::BEZIER && currShapeChoice != Shape::BSPLINE)
	{
		if (shape != NULL)
		{
			shape->setMid((shape->startPoint().x() + shape->endPoint().x()) / 2, (shape->startPoint().y() + shape->endPoint().y()) / 2);
			if (currSelect == DRAW)
				shape->setPoint();
		}
		release = true;
	}
	if (clipRect != NULL&&currSelect == SELECT&&currConv == CLIP)
	{
		qDebug() << "end" << event->pos();
		if (event->pos().x() - clipRect->startPoint().x() < 10 || event->pos().y() - clipRect->startPoint().y() < 10)
		{
		}
		else
		{
			clipRect->setEnd(event->pos().x(), event->pos().y());
			clipRect->setPoint();
			ifClipFinish = true;
			updateGL();
		}
	}
}
