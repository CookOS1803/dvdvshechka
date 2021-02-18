#include <Windows.h>
#include <tchar.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glut32.lib")
#include "glut.h"

void diamond();

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(40, 70);
	glutCreateWindow("Вариант 12");

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 100.0, 0.0, 100.0);

	glutDisplayFunc(diamond);
	glutMainLoop();

	return 0;
}

void diamond()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2i(50, 0);
	glVertex2i(100, 50);
	glVertex2i(50, 100);
	glVertex2i(0, 50);
	glEnd();
	glFlush();
}