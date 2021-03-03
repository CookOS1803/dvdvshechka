#include <Windows.h>
#include <tchar.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glut32.lib")
#include "glut.h"

void init();
void set_pixel(int x, int y);
void line(int x0, int y0, int x1, int y1);
void display();
inline int round_k(const float a);

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(760, 300);
	glutInitWindowSize(100, 100);
	glutCreateWindow("Вариант 12");

	init();
	glutDisplayFunc(display);
	glutMainLoop();
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-20, 20, -20, 20);
}

void set_pixel(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void line(int x0, int y0, int x1, int y1)
{
	int dx = x1 - x0, dy = y1 - y0, step;
	float xInc, yInc, x = x0, y = y0;
	step = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
	xInc = float(dx) / float(step);
	yInc = float(dy) / float(step);

	set_pixel(round_k(x), round_k(y));
	for (int k = 0; k < step; k++)
	{
		x += xInc;
		y += yInc;
		set_pixel(round_k(x), round_k(y));
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	line(2, 11, 6, 6);
}

inline int round_k(const float a)
{
	return int(a + 0.5);
}