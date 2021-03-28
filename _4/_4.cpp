#include <Windows.h>
#include <tchar.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glut32.lib")
#include "glut.h"

void init();
void display();
void set_pixels(int pixels[][2], int n);
void circleBrasenhem(int xc, int yc, int r);

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
	circleBrasenhem(2, 11, 10);
}

void set_pixels(int pixels[][2], int n)
{
	glBegin(GL_POINTS);

	for (int i = 0; i < n; i++)
		glVertex2iv(pixels[i]);

	glEnd();
	glFlush();
}

void circleBrasenhem(int xc, int yc, int r)
{
	int x = 0, y = r;
	int p = 1 - r;

	while (x <= y)
	{
		int pixels[][2] =
		{
			{x + xc, y + yc},
			{-x + xc, y + yc},
			{-x + xc, -y + yc},
			{x + xc, -y + yc},
			{y + xc, x + yc},
			{-y + xc, x + yc},
			{-y + xc, -x + yc},
			{y + xc, -x + yc}
		};
		
		set_pixels(pixels, 8);

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