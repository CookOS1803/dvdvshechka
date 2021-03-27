#include <Windows.h>
#include <tchar.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glut32.lib")
#include "glut.h"

void init();
void display();
void set_pixel(int x, int y);
void circleBrasenhem(int xc, int yc, int r);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("");

	init();
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 1000.0, 0.0, 1000.0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	circleBrasenhem(500, 500, 400);
}

void set_pixel(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void circleBrasenhem(int xc, int yc, int r)
{
	int x = 0, y = r;
	int p = 1 - r;

	while (x <= y)
	{
		set_pixel(x + xc, y + yc);
		set_pixel(-x + xc, y + yc);
		set_pixel(-x + xc, -y + yc);
		set_pixel(x + xc, -y + yc);
		set_pixel(y + xc, x + yc);
		set_pixel(-y + xc, x + yc);
		set_pixel(-y + xc, -x + yc);
		set_pixel(y + xc, -x + yc);

		if (p < 0)
			p += 2*x + 3;
		else
		{
			p += 2*x - 2*y + 5;
			y--;
		}
		x++;
	}
}