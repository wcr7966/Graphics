#include "show.h"

void displayCube(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);//设置清除颜色
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//用当前清除颜色清除窗口

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	{
		glRotatef(AngleX, 1.0f, 0.0f, 0.0f);
		glRotatef(AngleY, 0.0f, 1.0f, 0.0f);

		glBegin(GL_POLYGON); //前表面  
		glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
		glVertex3f(50.0f, 50.0f, 50.0f);

		glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
		glVertex3f(50.0f, -50.0f, 50.0f);

		glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
		glVertex3f(-50.0f, -50.0f, 50.0f);

		glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
		glVertex3f(-50.0f, 50.0f, 50.0f);
		glEnd();


		glBegin(GL_POLYGON); //后表面  
		glColor3f(0.0f, 0.5f, 1.0f);
		glVertex3f(50.0f, 50.0f, -50.0f);

		glColor3f(0.0f, 0.5f, 1.0f);
		glVertex3f(50.0f, -50.0f, -50.0f);

		glColor3f(0.0f, 0.5f, 1.0f);
		glVertex3f(-50.0f, -50.0f, -50.0f);

		glColor3f(0.0f, 0.5f, 1.0f);
		glVertex3f(-50.0f, 50.0f, -50.0f);
		glEnd();

		glBegin(GL_POLYGON); //上表面  
		glColor3d(1.0, 0.0, 0.5);
		glVertex3f(50.0f, 50.0f, -50.0f);

		glColor3d(1.0, 0.0, 0.5);
		glVertex3f(50.0f, 50.0f, 50.0f);

		glColor3d(1.0, 0.0, 0.5);
		glVertex3f(-50.0f, 50.0f, 50.0f);

		glColor3d(1.0, 0.0, 0.5);
		glVertex3f(-50.0f, 50.0f, -50.0f);
		glEnd();

		glBegin(GL_POLYGON); //下表面  
		glColor3ub(0u, 255u, 0u);//颜色设置为绿色  
		glVertex3f(50.0f, -50.0f, -50.0f);

		glColor3ub(0u, 255u, 0u);//颜色设置为绿色   
		glVertex3f(50.0f, -50.0f, 50.0f);

		glColor3ub(0u, 255u, 0u);//颜色设置为绿色   
		glVertex3f(-50.0f, -50.0f, 50.0f);

		glColor3ub(0u, 255u, 0u);//颜色设置为绿色   
		glVertex3f(-50.0f, -50.0f, -50.0f);
		glEnd();

		glBegin(GL_POLYGON); //左表面  
		glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)255);
		glVertex3f(50.0f, 50.0f, 50.0f);

		glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)255);
		glVertex3f(50.0f, 50.0f, -50.0f);

		glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)255);
		glVertex3f(50.0f, -50.0f, -50.0f);

		glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)255);
		glVertex3f(50.0f, -50.0f, 50.0f);
		glEnd();

		glBegin(GL_POLYGON); //右表面  
		glColor3f(1.0f, 0.5f, 0.0f);
		glVertex3f(-50.0f, 50.0f, 50.0f);

		glColor3f(1.0f, 0.5f, 0.0f);
		glVertex3f(-50.0f, 50.0f, -50.0f);

		glColor3f(1.0f, 0.5f, 0.0f);
		glVertex3f(-50.0f, -50.0f, -50.0f);

		glColor3f(1.0f, 0.5f, 0.0f);
		glVertex3f(-50.0f, -50.0f, 50.0f);
		glEnd();
	}
	glPopMatrix();

	glFlush();
	//glutSwapBuffers();
}

void cubeReshape(int w, int h)
{
	//cout << "AA" << endl;
	width = w;
	height = h;
	aspect = (GLfloat)w / (GLfloat)h;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION); //将当前矩阵指定为投影模式  
	glLoadIdentity();

	//设置三维投影区
	if (w <= h)
		glOrtho(-nRange, nRange, -nRange * aspect, nRange * aspect, -nRange, nRange);
	else
		glOrtho(-nRange, nRange, -nRange / aspect, nRange / aspect, -nRange, nRange);
}

/*void cubeKeyboard(GLint key, GLint x, GLint y)
{
	//cout << "BB" << endl;
	if (key == GLUT_KEY_UP)
		AngleX -= 5.0f;
	if (key == GLUT_KEY_DOWN)
		AngleX += 5.0f;
	if (key == GLUT_KEY_LEFT)
		AngleY -= 5.0f;
	if (key == GLUT_KEY_RIGHT)
		AngleY += 5.0f;
	if (AngleX > 355.0f)
		AngleX = 0.0f;
	if (AngleX < 0.0f)
		AngleX = 355.0f;
	if (AngleY > 355.0f)
		AngleY = 0.0f;
	if (AngleY < 0.0f)
		AngleY = 355.0f;
	glutPostRedisplay();
}*/

void cubeInit()
{
	AngleX = 45.0f;
	AngleY = 315.0f;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DITHER);
	glShadeModel(GL_SMOOTH);
}

/*static void mouseClicked(int button, int state, int x, int y)
{
	//cout << "aaa" << endl;
	if (button == GLUT_LEFT_BUTTON)//缩小
	{
		//cout << "left" << endl;
		if (state == GLUT_DOWN) {
			if (nRange > 100)
				nRange -= 50;
		}
	}
	else if (button == GLUT_RIGHT_BUTTON)//放大
	{
		//cout << "right" << endl;
		if (state == GLUT_DOWN) {
			nRange += 50;
		}
	}
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION); //将当前矩阵指定为投影模式  
	glLoadIdentity();
	if (width <= height)
		glOrtho(-nRange, nRange, -nRange * aspect, nRange * aspect, -nRange, nRange);
	else
		glOrtho(-nRange, nRange, -nRange / aspect, nRange / aspect, -nRange, nRange);
	glutPostRedisplay();
}

void displayCubeMain()
{
	//glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("三维六面体显示和变换");

	//glutCreateSubWindow(1,0,100,400,400);
	cubeInit();
	glutReshapeFunc(cubeReshape);
	glutSpecialFunc(cubeKeyboard);//响应键盘
	glutDisplayFunc(displayCube);
	glutMouseFunc(mouseClicked);//响应鼠标

	glutMainLoop();
}
*/