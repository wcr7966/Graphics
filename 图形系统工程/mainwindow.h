#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QOpenGLWidget>

#include "shape.h"
#include "paintwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

signals:
    void changeCurrentShape(Shape::shapeChoice newShape);
	void changeCurrentColor(Shape::colorChoice newColor);
	void changeSelectState(Select s);
	void changeConvState(Conv c);
	void savePicture();
	void clearPicture();
	void showRect();

private slots:
    void drawLineActionTriggered();
    void drawRectActionTriggered();
	void drawCircleActionTriggered();
	void drawOvalActionTriggered();
	void drawPolygonActionTriggered();
	void drawBezierActionTriggered();
	void drawBsplineActionTriggered();

	void drawBlackActionTriggered();
	void drawWhiteActionTriggered();
	void drawBlueActionTriggered();
	void drawGreenActionTriggered();
	void drawRedActionTriggered();

	void drawActionTriggered();
	void selectActionTriggered();

	void translateActionTriggered();
	void rotateActionTriggered();
	void scaleActionTriggered();
	void modifyActionTriggered();
	void fillActionTriggered();
	void clipActionTriggered();

	void saveActionTriggered();
	void clearActionTriggered();

	void showActionTriggered();
};

#endif // MAINWINDOW_H
