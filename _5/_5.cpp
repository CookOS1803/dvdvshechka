#include <Windows.h>
#include <tchar.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glut32.lib")
#include "glut.h"

void init();
void display();
void set_pixels(int pixels[][2], int n);
void ellipseBrasenhem(int xc, int yc, int rx, int ry);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(100, 100);
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
	gluOrtho2D(25.0, -25.0, 25.0, -25.0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	ellipseBrasenhem(2, 11, 15, 10);
}

void set_pixels(int pixels[][2], int n)
{
	glBegin(GL_POINTS);

	for (int i = 0; i < n; i++)
		glVertex2iv(pixels[i]);

	glEnd();
	glFlush();
}

void ellipseBrasenhem(int xc, int yc, int rx, int ry)
{
	int x = 0, y = ry;
	int p = ry*ry - rx*rx*ry + rx*rx/4;
	int ry2 = ry*ry,
		rx2 = rx*rx;

	while (ry2*x < rx2*y)
	{
		int pixels[][2] = 
		{
			{xc + x, yc + y},
			{xc - x, yc + y},
			{xc - x, yc - y},
			{xc + x, yc - y}
		};

		set_pixels(pixels, 4);

		if (p < 0)
			p += ry2*(2*x + 3);
		else
		{
			p += ry2*(2*x + 3) - 2*rx2*y;
			y--;
		}
		x++;
	}

	p = ry2*x*x + ry2*x + ry2/4 + rx2*y*y - 2*rx2*y + rx2 - rx2*ry2;
	

	while (y != 0)
	{
		int pixels[][2] = 
		{
			{xc + x, yc + y},
			{xc - x, yc + y},
			{xc - x, yc - y},
			{xc + x, yc - y}
		};

		set_pixels(pixels, 4);

		if (p < 0)
			p += rx2*(3 - 2*y);
		else
		{
			p += rx2*(3 - 2*y) + 2*ry2*(x + 1);
			x++;
		}
		y--;
	}
}