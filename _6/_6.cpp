#include <Windows.h>
#include <tchar.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glut32.lib")
#include "glut.h"

void init();
void display();
void set_pixel(int x, int y);
void set_pixels(int pixels[][2], int n);
void fill(int vertices[][2], int n);
void linesBrasenhem(int x0, int y0, int xend, int yend);

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
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 200, 0, 100);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	//int vertices[][2] =
	//{
	//	{10, 0}, {60, 15}, {40, 30}, {45, 5}, {30, 20}
	//};

	int vertices[][2] =
	{
		{10, 10}, {20, 0}, {30, 20}, {30, 30}, {30, 50}
	};

	for (int i = 0; i < 4; i++)
		linesBrasenhem(vertices[i][0], vertices[i][1], vertices[i + 1][0], vertices[i + 1][1]);
	linesBrasenhem(vertices[4][0], vertices[4][1], vertices[0][0], vertices[0][1]);

	fill(vertices, 5);
}

void set_pixel(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void set_pixels(int pixels[][2], int n)
{
	glBegin(GL_POINTS);

	for (int i = 0; i < n; i++)
		glVertex2iv(pixels[i]);

	glEnd();
	glFlush();
}

void fill(int vertices[][2], int n)
{
	int xmax = vertices[0][0],
		xmin = xmax,
		ymax = vertices[0][1],
	    ymin = ymax;
	bool inside = false, changed = false;

	for (int i = 1; i < n; i++)
	{
		if (vertices[i][0] > xmax) xmax = vertices[i][0];
		else if (vertices[i][0] < xmin) xmin = vertices[i][0];

		if (vertices[i][1] > ymax) ymax = vertices[i][1];
		else if (vertices[i][1] < ymin) ymin = vertices[i][1];
	}

	while (ymax > ymin)
	{
		for (int x = xmin; x < xmax; x++)
		{
			for (int i = 0; i < n - 1; i++)
			{
				if ((x - vertices[i][0]) * (vertices[i + 1][1] - vertices[i][1]) == (ymax - vertices[i][1]) * (vertices[i + 1][0] - vertices[i][0]))
				{
					inside = inside ? false : true;
					changed = true;
					break;
				}
			}
			if (not changed and (x - vertices[n - 1][0]) * (vertices[0][1] - vertices[n - 1][1]) == (ymax - vertices[n - 1][1]) * (vertices[0][0] - vertices[n - 1][0]))
			{
				inside = inside ? false : true;
			}

			if (inside) set_pixel(x, ymax);
			changed = false;
		}

		inside = false;

		ymax--;
	}
}

void linesBrasenhem(int x0, int y0, int xend, int yend)
{
	int dx = abs(xend - x0), dy = abs(yend - y0);
	int p;
	int	x = x0,	y = y0;
	int xInc = xend - x0 > 0 ? 1 : -1,
		yInc = yend - y0 > 0 ? 1 : -1;

	set_pixel(x, y);

	if (dx > dy)
	{
		p = 2*dy - dx;

		while (x != xend)
		{
			x += xInc;
			if (p < 0)
				p += 2*dy;
			else
			{
				y += yInc;
				p += 2*(dy - dx);
			}
			set_pixel(x, y);
		}
	}
	else
	{
		p = 2*dx - dy;

		while (y != yend)
		{
			y += yInc;
			if (p < 0)
				p += 2*dx;
			else
			{
				x += xInc;
				p += 2*(dx - dy);
			}
			set_pixel(x, y);
		}
	}

}

//вогнутость ряльно проблема из-за пересечения (а иногда и суко совпадения) прямых от сторон.
//надо сначала посчитать все точки пересечения, а потом рисовать между парами точек, пушо если точка имеет нецелый x, то всё, отчисление