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
	ellipseBrasenhem(2, 11, 10, 5);
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
	int ry2 = ry*ry,
		rx2 = rx*rx;
	int p = 4*ry2 - 4*rx2*ry + rx2;

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

		x++;
		if (p < 0)
			p += 4*ry2*(2*x + 1);
		else
		{
			y--;
			p += 4*ry2*(2*x + 1) - 8*rx2*y;
		}
	}
		
	p = (2*x + 1)*(2*x + 1)*ry2 + 4*(y - 1)*(y - 1)*rx2 - 4*rx2*ry2;

	while (y != -1)
	{
		int pixels[][2] = 
		{
			{xc + x, yc + y},
			{xc - x, yc + y},
			{xc - x, yc - y},
			{xc + x, yc - y}
		};

		set_pixels(pixels, 4);

		y--;
		if (p < 0)
		{
			x++;
			p += 8*ry2*x - 4*rx2*(2*y - 1);
		}
		else
			p += 4*rx2*(1 - 2*y);
	}
}