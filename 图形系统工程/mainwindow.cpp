#include "mainwindow.h"
#include <QAction>
#include<QLabel>
#include <QToolBar>
#include <QStatusBar>
#include <QMenuBar>
#include <QComboBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
	//设置窗口
	PaintWidget *paintWidget = new PaintWidget(this);
	setGeometry(50, 50, 800, 600);
	setWindowTitle("My Graphic System");
	setCentralWidget(paintWidget);

	setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

	//颜色Bar
	QToolBar *color = this->addToolBar("Color");
	QActionGroup *group = new QActionGroup(color);
	//黑色
	QAction *drawBlackAction = new QAction("Black");
	drawBlackAction->setIcon(QIcon(":/Color/black.png"));
	drawBlackAction->setToolTip(tr("black."));
	drawBlackAction->setStatusTip(tr("black."));
	drawBlackAction->setCheckable(true);
	drawBlackAction->setChecked(true);
	group->addAction(drawBlackAction);
	color->addAction(drawBlackAction);

	//红色
	QAction *drawRedAction = new QAction("Red");
	drawRedAction->setIcon(QIcon(":/Color/red.png"));
	drawRedAction->setToolTip(tr("red."));
	drawRedAction->setStatusTip(tr("red."));
	drawRedAction->setCheckable(true);
	group->addAction(drawRedAction);
	color->addAction(drawRedAction);

	//绿色
	QAction *drawGreenAction = new QAction("Green");
	drawGreenAction->setIcon(QIcon(":/Color/green.png"));
	drawGreenAction->setToolTip(tr("green."));
	drawGreenAction->setStatusTip(tr("green."));
	drawGreenAction->setCheckable(true);
	group->addAction(drawGreenAction);
	color->addAction(drawGreenAction);

	//蓝色
	QAction *drawBlueAction = new QAction("Blue");
	drawBlueAction->setIcon(QIcon(":/Color/blue.png"));
	drawBlueAction->setToolTip(tr("blue."));
	drawBlueAction->setStatusTip(tr("blue."));
	drawBlueAction->setCheckable(true);
	group->addAction(drawBlueAction);
	color->addAction(drawBlueAction);

	//白色
	QAction *drawWhiteAction = new QAction("White");
	drawWhiteAction->setIcon(QIcon(":/Color/white.png"));
	drawWhiteAction->setToolTip(tr("white."));
	drawWhiteAction->setStatusTip(tr("white."));
	drawWhiteAction->setCheckable(true);
	group->addAction(drawWhiteAction);
	color->addAction(drawWhiteAction);

	//画线
    QAction *drawLineAction = new QAction("Line");
    drawLineAction->setIcon(QIcon(":/Shape/line.png"));
    drawLineAction->setToolTip(tr("Draw a line."));
    drawLineAction->setStatusTip(tr("Draw a line."));
    drawLineAction->setCheckable(true);
    drawLineAction->setChecked(true);

	//画矩形
    QAction *drawRectAction = new QAction("Rectangle");
    drawRectAction->setIcon(QIcon(":/Shape/rect.png"));
    drawRectAction->setToolTip(tr("Draw a rectangle."));
    drawRectAction->setStatusTip(tr("Draw a rectangle."));
    drawRectAction->setCheckable(true);

	//画圆
	QAction *drawCircleAction = new QAction("Circle");
	drawCircleAction->setIcon(QIcon(":/picture/circle.png"));
	drawCircleAction->setToolTip(tr("Draw a Circle."));
	drawCircleAction->setStatusTip(tr("Draw a Circle."));
	drawCircleAction->setCheckable(true);

	//椭圆
	QAction *drawOvalAction = new QAction("Oval");
	drawOvalAction->setIcon(QIcon(":/picture/oval.png"));
	drawOvalAction->setToolTip(tr("Draw a Oval."));
	drawOvalAction->setStatusTip(tr("Draw a Oval."));
	drawOvalAction->setCheckable(true);

	//多边形
	QAction *drawPolygonAction = new QAction("Polygon");
	drawPolygonAction->setIcon(QIcon(":/picture/polygon.png"));
	drawPolygonAction->setToolTip(tr("Draw a Polygon."));
	drawPolygonAction->setStatusTip(tr("Draw a Polygon."));
	drawPolygonAction->setCheckable(true);

	//Bezier曲线
	QAction *drawBezierAction = new QAction("Bezier");
	drawBezierAction->setIcon(QIcon(":/picture/bezier.png"));
	drawBezierAction->setToolTip(tr("Draw a Bezier."));
	drawBezierAction->setStatusTip(tr("Draw a Bezier."));
	drawBezierAction->setCheckable(true);

	//Bspline曲线
	QAction *drawBsplineAction = new QAction("Bspline");
	drawBsplineAction->setIcon(QIcon(":/picture/bs.png"));
	drawBsplineAction->setToolTip(tr("Draw a Bspline."));
	drawBsplineAction->setStatusTip(tr("Draw a Bspline."));
	drawBsplineAction->setCheckable(true);


	//Draw/Select Bar
	QToolBar * tool = this->addToolBar("Tool");
	QActionGroup *groupTool = new QActionGroup(tool);
	//画图
	QAction *drawAction = new QAction("Draw");
	drawAction->setIcon(QIcon(":/picture/draw.png"));
	drawAction->setCheckable(true);
	drawAction->setChecked(true);
	drawAction->setToolTip(tr("draw."));
	drawAction->setStatusTip(tr("draw."));
	tool->addAction(drawAction);
	groupTool->addAction(drawAction);


	//选择
	QAction *selectAction = new QAction("Select");
	selectAction->setCheckable(true);
	selectAction->setIcon(QIcon(":/picture/select.png"));
	selectAction->setToolTip(tr("select."));
	selectAction->setStatusTip(tr("select."));
	tool->addAction(selectAction);
	groupTool->addAction(selectAction);

	//显示
	QAction * showAction = new QAction("Show");
	showAction->setToolTip(tr("Show"));
	showAction->setStatusTip(tr("Show"));
	showAction->setIcon(QIcon(":/picture/cube.png"));
	showAction->setCheckable(true);
	tool->addAction(showAction);
	groupTool->addAction(showAction);


	//变换Bar
	QToolBar *conversion= this->addToolBar("Conversion");
	QActionGroup *groupConv = new QActionGroup(conversion);
	//平移
	QAction *translateAction = new QAction("Translate");
	translateAction->setIcon(QIcon(":/picture/translation.png"));
	translateAction->setToolTip(tr("Translate the graph"));
	translateAction->setStatusTip(tr("Translate the graph"));
	translateAction->setCheckable(true);
	translateAction->setChecked(true);
	conversion->addAction(translateAction);
	groupConv->addAction(translateAction);

	//旋转
	QAction *rotateAction = new QAction("Rotate");
	rotateAction->setIcon(QIcon(":/picture/rotation.png"));
	rotateAction->setToolTip(tr("Rotate the graph"));
	rotateAction->setStatusTip(tr("Rotate the graph"));
	rotateAction->setCheckable(true);
	conversion->addAction(rotateAction);
	groupConv->addAction(rotateAction);

	//缩放
	QAction *scaleAction = new QAction("Scale");
	scaleAction->setIcon(QIcon(":/picture/scale.png"));
	scaleAction->setToolTip(tr("Sscale the graph"));
	scaleAction->setStatusTip(tr("Sscale the graph"));
	scaleAction->setCheckable(true);
	conversion->addAction(scaleAction);
	groupConv->addAction(scaleAction);

	//调整
	QAction *modifyAction = new QAction("Modify");
	modifyAction->setIcon(QIcon(":/picture/modify.png"));
	modifyAction->setToolTip(tr("Modify the graph"));
	modifyAction->setStatusTip(tr("Modify the graph"));
	modifyAction->setCheckable(true);
	conversion->addAction(modifyAction);
	groupConv->addAction(modifyAction);

	//填充
	QAction * fillAction = new QAction("Fill");
	fillAction->setIcon(QIcon(":/picture/fill.png"));
	fillAction->setToolTip(tr("Fill the graph"));
	fillAction->setStatusTip(tr("Fill the graph"));
	fillAction->setCheckable(true);
	conversion->addAction(fillAction);
	groupConv->addAction(fillAction);

	//裁剪
	QAction *clipAction = new QAction("Clip");
	clipAction->setIcon(QIcon(":/picture/clip.png"));
	clipAction->setCheckable(true);
	clipAction->setToolTip(tr("clip the graph"));
	clipAction->setStatusTip(tr("clip the graph"));
	conversion->addAction(clipAction);
	groupConv->addAction(clipAction);



	//保存
	QAction *saveAction = new QAction("Save");
	saveAction->setIcon(QIcon(":/picture/save.png"));
	saveAction->setToolTip(tr("Save all graph"));
	saveAction->setStatusTip(tr("Save all graph"));

	//清屏
	QAction *clearAction = new QAction("Clear");
	clearAction->setIcon(QIcon(":/picture/clear.png"));
	clearAction ->setToolTip(tr("Clear all graph"));
	clearAction->setStatusTip(tr("Clear all graph"));


	//FILE菜单
	QMenu *file = menuBar()->addMenu(tr("File"));
	QActionGroup *groupFile = new QActionGroup(file);
	file->addAction(saveAction);
	file->addAction(clearAction);
	groupFile->addAction(saveAction);
	groupFile->addAction(clearAction);

	//shape菜单
	QMenu *shape = menuBar()->addMenu(tr("Shape"));
	QActionGroup *groupShape = new QActionGroup(shape);
	shape->addAction(drawLineAction);
	shape->addAction(drawRectAction);
	shape->addAction(drawCircleAction);
	shape->addAction(drawOvalAction);
	shape->addAction(drawPolygonAction);
	shape->addAction(drawBezierAction);
	shape->addAction(drawBsplineAction);
	groupShape->addAction(drawLineAction);
	groupShape->addAction(drawRectAction);
	groupShape->addAction(drawCircleAction);
	groupShape->addAction(drawOvalAction);
	groupShape->addAction(drawPolygonAction);
	groupShape->addAction(drawBezierAction);
	groupShape->addAction(drawBsplineAction);

    QLabel *statusMsg = new QLabel;
    statusBar()->addWidget(statusMsg);


	connect(drawLineAction, SIGNAL(triggered()),
		this, SLOT(drawLineActionTriggered()));
	connect(drawRectAction, SIGNAL(triggered()),
		this, SLOT(drawRectActionTriggered()));
	connect(drawCircleAction, SIGNAL(triggered()),
		this, SLOT(drawCircleActionTriggered()));
	connect(drawOvalAction, SIGNAL(triggered()),
		this, SLOT(drawOvalActionTriggered()));
	connect(drawPolygonAction, SIGNAL(triggered()),
		this, SLOT(drawPolygonActionTriggered()));
	connect(drawBezierAction, SIGNAL(triggered()),
		this, SLOT(drawBezierActionTriggered()));
	connect(drawBsplineAction, SIGNAL(triggered()),
		this, SLOT(drawBsplineActionTriggered()));

	connect(drawRedAction, SIGNAL(triggered()),
		this, SLOT(drawRedActionTriggered()));
	connect(drawBlackAction, SIGNAL(triggered()),
		this, SLOT(drawBlackActionTriggered()));
	connect(drawWhiteAction, SIGNAL(triggered()),
		this, SLOT(drawWhiteActionTriggered()));
	connect(drawGreenAction, SIGNAL(triggered()),
		this, SLOT(drawGreenActionTriggered()));
	connect(drawBlueAction, SIGNAL(triggered()),
		this, SLOT(drawBlueActionTriggered()));

	connect(drawAction, SIGNAL(triggered()),
		this, SLOT(drawActionTriggered()));
	connect(selectAction, SIGNAL(triggered()),
		this, SLOT(selectActionTriggered()));

	connect(translateAction, SIGNAL(triggered()),
		this, SLOT(translateActionTriggered()));
	connect(rotateAction, SIGNAL(triggered()),
		this, SLOT(rotateActionTriggered()));
	connect(scaleAction, SIGNAL(triggered()),
		this, SLOT(scaleActionTriggered()));
	connect(modifyAction, SIGNAL(triggered()),
		this, SLOT(modifyActionTriggered()));
	connect(fillAction, SIGNAL(triggered()),
		this, SLOT(fillActionTriggered()));
	connect(clipAction, SIGNAL(triggered()),
		this, SLOT(clipActionTriggered()));

	connect(saveAction, SIGNAL(triggered()),
		this, SLOT(saveActionTriggered()));
	connect(clearAction, SIGNAL(triggered()),
		this, SLOT(clearActionTriggered()));

	connect(showAction, SIGNAL(triggered()),
		this, SLOT(showActionTriggered()));

	connect(this, SIGNAL(changeCurrentShape(Shape::shapeChoice)),
		paintWidget, SLOT(setCurrentShape(Shape::shapeChoice)));

	connect(this, SIGNAL(changeCurrentColor(Shape::colorChoice)),
		paintWidget, SLOT(setCurrentColor(Shape::colorChoice)));

	connect(this, SIGNAL(changeSelectState(Select)),
		paintWidget, SLOT(setCurrentSelectState(Select)));

	connect(this, SIGNAL(changeConvState(Conv)),
		paintWidget, SLOT(setCurrentConvState(Conv)));

	connect(this, SIGNAL(clearPicture()),
		paintWidget, SLOT(clear()));
	connect(this, SIGNAL(savePicture()),
		paintWidget, SLOT(save()));

	connect(this, SIGNAL(showRect()),
		paintWidget, SLOT(show()));
}

//图形
void MainWindow::drawLineActionTriggered()
{
    emit changeCurrentShape(Shape::LINE);
}
void MainWindow::drawRectActionTriggered()
{
    emit changeCurrentShape(Shape::RECT);
}
void MainWindow::drawCircleActionTriggered()
{
	emit changeCurrentShape(Shape::CIRCLE);
}
void MainWindow::drawOvalActionTriggered()
{
	emit changeCurrentShape(Shape::OVAL);
}
void MainWindow::drawPolygonActionTriggered()
{
	emit changeCurrentShape(Shape::POLYGON);
}

void MainWindow::drawBezierActionTriggered()
{
	emit changeCurrentShape(Shape::BEZIER);
}

void MainWindow::drawBsplineActionTriggered()
{
	emit changeCurrentShape(Shape::BSPLINE);
}



//颜色
void MainWindow::drawRedActionTriggered()
{
	emit changeCurrentColor(Shape::Red);
}
void MainWindow::drawBlackActionTriggered()
{
	emit changeCurrentColor(Shape::Black);
}
void MainWindow::drawWhiteActionTriggered()
{
	emit changeCurrentColor(Shape::White);
}
void MainWindow::drawBlueActionTriggered()
{
	emit changeCurrentColor(Shape::Blue);
}
void MainWindow::drawGreenActionTriggered()
{
	emit changeCurrentColor(Shape::Green);
}


//画图
void MainWindow::drawActionTriggered()
{
	emit changeSelectState(DRAW);
}
//选择
void MainWindow::selectActionTriggered()
{
	emit changeSelectState(SELECT);
}

void MainWindow::showActionTriggered()
{
	emit changeSelectState(SHOW);
}

void MainWindow::translateActionTriggered()
{
	emit changeConvState(TRANSLATE);
}

void MainWindow::rotateActionTriggered()
{
	emit changeConvState(ROTATE);
}

void MainWindow::scaleActionTriggered()
{
	emit changeConvState(SCALE);
}

void MainWindow::modifyActionTriggered()
{
	emit changeConvState(MODIFY);
}

void MainWindow::fillActionTriggered()
{
	emit changeConvState(FILL);
}

void MainWindow::clipActionTriggered()
{
	emit changeConvState(CLIP);
}

void MainWindow::saveActionTriggered()
{
	emit savePicture();
}

void MainWindow::clearActionTriggered()
{
	emit clearPicture();
}
