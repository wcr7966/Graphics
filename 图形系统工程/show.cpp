#include "show.h"

void displayCube(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);//���������ɫ
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�õ�ǰ�����ɫ�������

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	{
		glRotatef(AngleX, 1.0f, 0.0f, 0.0f);
		glRotatef(AngleY, 0.0f, 1.0f, 0.0f);

		glBegin(GL_POLYGON); //ǰ����  
		glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
		glVertex3f(50.0f, 50.0f, 50.0f);

		glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
		glVertex3f(50.0f, -50.0f, 50.0f);

		glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
		glVertex3f(-50.0f, -50.0f, 50.0f);

		glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
		glVertex3f(-50.0f, 50.0f, 50.0f);
		glEnd();


		glBegin(GL_POLYGON); //�����  
		glColor3f(0.0f, 0.5f, 1.0f);
		glVertex3f(50.0f, 50.0f, -50.0f);

		glColor3f(0.0f, 0.5f, 1.0f);
		glVertex3f(50.0f, -50.0f, -50.0f);

		glColor3f(0.0f, 0.5f, 1.0f);
		glVertex3f(-50.0f, -50.0f, -50.0f);

		glColor3f(0.0f, 0.5f, 1.0f);
		glVertex3f(-50.0f, 50.0f, -50.0f);
		glEnd();

		glBegin(GL_POLYGON); //�ϱ���  
		glColor3d(1.0, 0.0, 0.5);
		glVertex3f(50.0f, 50.0f, -50.0f);

		glColor3d(1.0, 0.0, 0.5);
		glVertex3f(50.0f, 50.0f, 50.0f);

		glColor3d(1.0, 0.0, 0.5);
		glVertex3f(-50.0f, 50.0f, 50.0f);

		glColor3d(1.0, 0.0, 0.5);
		glVertex3f(-50.0f, 50.0f, -50.0f);
		glEnd();

		glBegin(GL_POLYGON); //�±���  
		glColor3ub(0u, 255u, 0u);//��ɫ����Ϊ��ɫ  
		glVertex3f(50.0f, -50.0f, -50.0f);

		glColor3ub(0u, 255u, 0u);//��ɫ����Ϊ��ɫ   
		glVertex3f(50.0f, -50.0f, 50.0f);

		glColor3ub(0u, 255u, 0u);//��ɫ����Ϊ��ɫ   
		glVertex3f(-50.0f, -50.0f, 50.0f);

		glColor3ub(0u, 255u, 0u);//��ɫ����Ϊ��ɫ   
		glVertex3f(-50.0f, -50.0f, -50.0f);
		glEnd();

		glBegin(GL_POLYGON); //�����  
		glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)255);
		glVertex3f(50.0f, 50.0f, 50.0f);

		glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)255);
		glVertex3f(50.0f, 50.0f, -50.0f);

		glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)255);
		glVertex3f(50.0f, -50.0f, -50.0f);

		glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)255);
		glVertex3f(50.0f, -50.0f, 50.0f);
		glEnd();

		glBegin(GL_POLYGON); //�ұ���  
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

	glMatrixMode(GL_PROJECTION); //����ǰ����ָ��ΪͶӰģʽ  
	glLoadIdentity();

	//������άͶӰ��
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
	if (button == GLUT_LEFT_BUTTON)//��С
	{
		//cout << "left" << endl;
		if (state == GLUT_DOWN) {
			if (nRange > 100)
				nRange -= 50;
		}
	}
	else if (button == GLUT_RIGHT_BUTTON)//�Ŵ�
	{
		//cout << "right" << endl;
		if (state == GLUT_DOWN) {
			nRange += 50;
		}
	}
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION); //����ǰ����ָ��ΪͶӰģʽ  
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
	glutCreateWindow("��ά��������ʾ�ͱ任");

	//glutCreateSubWindow(1,0,100,400,400);
	cubeInit();
	glutReshapeFunc(cubeReshape);
	glutSpecialFunc(cubeKeyboard);//��Ӧ����
	glutDisplayFunc(displayCube);
	glutMouseFunc(mouseClicked);//��Ӧ���

	glutMainLoop();
}
*/