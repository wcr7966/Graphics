#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QtGui>
#include <QDebug>
#include <QWidget>
#include "save.h"
#include "show.h"
#include "shape.h"
#include "line.h"
#include "rect.h"
#include "Circle.h"
#include "Oval.h"
#include "Polygon.h"
#include "Bezier.h"
#include "Bspline.h"
#include <QtOpenGL/QGLWidget>
#include <QDebug>
#include <fstream>


class PaintWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit PaintWidget(QWidget *parent = 0);

public slots:
    void setCurrentShape(Shape::shapeChoice s)
    {
        if(s != currShapeChoice) {
            currShapeChoice = s;
        }
    }

	void setCurrentColor(Shape::colorChoice colorchoice)
	{
		if (colorchoice != currColorChoice)
		{
			currColorChoice = colorchoice;
		}
		if (colorchoice != fillColorChoice)
			fillColorChoice = colorchoice;
	}

	void setCurrentSelectState(Select s)
	{
		currSelect = s;
		if (currSelect == DRAW)
		{
			release = true;
			ifShow = false;
			initializeGL();
			updateGL();
		}
		else if (currSelect == SELECT)
		{
			ifShow = false;
			initializeGL();
			updateGL();
		}
		else if (currSelect == SHOW)
		{
			ifShow = true;
			initializeGL();
			updateGL();
		}
	}

	void setCurrentConvState(Conv c)
	{
		currConv = c;
		if (c == FILL)
			isFill = true;
	}

	void clear();

	void save();

protected:
	void initializeGL();
	void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Shape::shapeChoice currShapeChoice; //��ǰѡ�е�ͼ������
	Shape::colorChoice currColorChoice; //��ǰѡ�е���ɫ
	Shape::colorChoice fillColorChoice;
    Shape *shape;
    bool release; //����Ƿ���
	QPoint first; 
	QPoint end;
	QPoint pre;
	QPoint curr;
    QList<Shape*> shapeList;
	Select currSelect; //��ǰѡ�е�״̬
	Conv currConv;
	int index; //ѡ�е�ͼ���±�
	bool isFill;
	bool ifShow;
	Shape *clipRect;
	bool ifClipFinish;
	GLfloat rTri;
	GLfloat rQuad;
};

#endif // PAINTWIDGET_H
