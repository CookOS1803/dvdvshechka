#include <Windows.h>
#include <tchar.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glut32.lib")
#include "glut.h"

void init();
void display();

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(200, 100);
	glutCreateWindow("");

	init();
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}

void init()
{
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 200, 0, 100);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(5);
	glShadeModel(GL_FLAT);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0xF00F);


	glBegin(GL_LINE_STRIP);
		glColor3f(1, 1, 0);
		glVertex2i(10, 0);
		glColor3f(0, 0, 1);
		glVertex2i(60, 15);
		glColor3f(1, 0, 0);
		glVertex2i(90, 50);
		glColor3f(1, 1, 1);
		glVertex2i(50, 60);
	glEnd();

	glDisable(GL_LINE_STIPPLE);
	glShadeModel(GL_SMOOTH);

	glBegin(GL_QUADS);
	glColor3f(1, 1, 0);
	glVertex2i(10, 0);
	glColor3f(0, 0, 1);
	glVertex2i(60, 15);
	glColor3f(1, 0, 0);
	glVertex2i(90, 50);
	glColor3f(1, 1, 1);
	glVertex2i(50, 60);
	glEnd();

	glPointSize(25);
	glBegin(GL_POINTS);
		glColor3f(0, 1, 0);
		glVertex2i(60, 60);
	glEnd();

	glFlush();
}