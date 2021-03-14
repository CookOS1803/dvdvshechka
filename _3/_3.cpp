#include <Windows.h>
#include <tchar.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glut32.lib")
#include "glut.h"

//
int _x = 0, _y = 1;

void set_pixel(int x, int y);
void linesBrasenhem(int x0, int y0, int xend, int yend);
void display();
void playerController(unsigned char key, int x, int y);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(100, 100);
	glutCreateWindow("Вариант 12");

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 20, 0, 20);

	glutDisplayFunc(display);
	glutKeyboardFunc(playerController);
	glutMainLoop();

	return 0;
}

void set_pixel(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void linesBrasenhem(int x0, int y0, int xend, int yend)
{
	int dx = abs(xend - x0), dy = abs(yend - y0);
	int p;
	int	x = x0,	y = y0;
	int xInc = xend - x0 > 0 ? 1 : -1,
		yInc = yend - y0 > 0 ? 1 : -1;

	set_pixel(x, y);

	if (dx >= dy)
	{
		p = 2 * dy + dx;

		while (x != xend)
		{
			x += xInc;
			set_pixel(x, y0);
			if (p < 0)
				p += 2 * dy;
			else
			{
				y += yInc;
				set_pixel(x0, y);
				p += 2 * (dy - dx);
			}
			set_pixel(x, y);
		}
	}
	else
	{
		p = 2 * dx - dy;

		while (y != xend)
		{
			y += yInc;
			if (p < 0)
				p += 2 * dx;
			else
			{
				x += xInc;
				p += 2 * (dx - dy);
			}
			set_pixel(x, y);
		}
	}
	
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	//linesBrasenhem(2, 11, 6, 6);
	linesBrasenhem(_x, _y, 10, 10);
	glutSwapBuffers();
}

//
void playerController(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w': case'W':
			_y +=1;
			break;
		case 's': case 'S':
			_y -=1;
			break;
		case 'a': case 'A':
			_x -=1;
			break;
		case 'd': case 'D':
			_x +=1;
			break;
	}
	glutPostRedisplay();
}