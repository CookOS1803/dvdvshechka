#include <Windows.h>
#include <tchar.h>
#include <iostream>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glut32.lib")
#include "glut.h"
#include "stack.h"

using namespace std;

struct vector
{
	int x, y;
};

void init();
void display();
void set_pixel(int x, int y);
void set_pixels(vector* pixels, int n);
vector* get_vectors(vector* vertices, int n);
bool is_convex(vector* vertices, int n);
//void fill(vector* vertices, int n);
void fill_triangle(vector v1, vector v2, vector v3);
void fillsgood(vector* vertices, int n);
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
	int n;

	cout << "Enter n: ";
	cin >> n;

	vector* vertices = new vector[n];

	for (int i = 0; i < n; i++)
	{
		cout << "Enter " << i + 1 << "st: ";
		cin >> vertices[i].x >> vertices[i].y;
	}	
	
	if (is_convex(vertices, n)) cout << "Convex";
	else						cout << "NonConvex";

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);

	for (int i = 0; i < n - 1; i++)
		linesBrasenhem(vertices[i].x, vertices[i].y, vertices[i + 1].x, vertices[i + 1].y);
	linesBrasenhem(vertices[n - 1].x, vertices[n - 1].y, vertices[0].x, vertices[0].y);

	glColor3f(1, 1, 1);

	fillsgood(vertices, n);
	delete[] vertices;
}

void set_pixel(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void set_pixels(vector* pixels, int n)
{
	glBegin(GL_POINTS);

	for (int i = 0; i < n; i++)
		glVertex2i(pixels[i].x, pixels[i].y);

	glEnd();
	glFlush();
}

vector* get_vectors(vector* vertices, int n)
{
	vector* vectors = new vector[n];

	for (int i = 0; i < n - 1; i++)
	{
		vectors[i].x = vertices[i + 1].x - vertices[i].x;
		vectors[i].y = vertices[i + 1].y - vertices[i].y;
	}
	vectors[n - 1].x = vertices[0].x - vertices[n - 1].x;
	vectors[n - 1].y = vertices[0].y - vertices[n - 1].y;

	return vectors;
}

bool is_convex(vector* vertices, int n)
{
	vector* vectors = get_vectors(vertices, n);

	int t = vectors[n - 1].x*vectors[0].y - vectors[n - 1].y*vectors[0].x;

	for (int i = 0; i < n - 1; i++)
	{
		if (t*(vectors[i].x*vectors[i + 1].y - vectors[i].y*vectors[i + 1].x) < 0)
		{
			delete[] vectors;
			return false;
		}
	}

	delete[] vectors;
	return true;
}

//void fill(vector* vertices, int n)
//{
//	int xmin = vertices[0].x,
//		m = 0,
//		ymax = vertices[0].y,
//	    ymin = ymax;
//	vector* vectors = get_vectors(vertices, n);
//	stack<int>* xs = nullptr;
//	
//	for (int i = 1; i < n; i++)
//	{
//		if (vertices[i].x <= xmin)
//		{
//			xmin = vertices[i].x;
//			m = i;
//		}
//
//		if (vertices[i].y > ymax) ymax = vertices[i].y;
//		else if (vertices[i].y < ymin) ymin = vertices[i].y;
//	}
//
//	while (ymax != ymin - 1)
//	{
//		int x1 = 0, x2 = 0;
//		int x = 0;
//
//		for (int i = m; i < n; i++)
//		{
//			if (ymax < min(vertices[i].y, vertices[i].y + vectors[i].y) or
//				ymax > max(vertices[i].y, vertices[i].y + vectors[i].y)) continue;
//
//			x = round((ymax - vertices[i].y)*((float)vectors[i].x/vectors[i].y) + vertices[i].x);
//			if (x >= min(vertices[i].x, vertices[i].x + vectors[i].x) and
//				x <= max(vertices[i].x, vertices[i].x + vectors[i].x)) xs = in_stack(xs, x);
//		}
//
//		for (int i = 0; i < m; i++)
//		{
//			if (ymax < min(vertices[i].y, vertices[i].y + vectors[i].y) or
//				ymax > max(vertices[i].y, vertices[i].y + vectors[i].y)) continue;
//
//			x = round((ymax - vertices[i].y)*((float)vectors[i].x/vectors[i].y) + vertices[i].x);
//			if (x >= min(vertices[i].x, vertices[i].x + vectors[i].x) and
//				x <= max(vertices[i].x, vertices[i].x + vectors[i].x)) xs = in_stack(xs, x);
//		}
//
//		while (xs)
//		{
//			xs = out_stack(xs, &x1);
//			//if (xs)
//			//{
//			//	if (x1 == x2) xs = out_stack(xs, &x1);
//			//}
//			if (not xs) break;
//			xs = out_stack(xs, &x2);
//
//			linesBrasenhem(x1, ymax, x2, ymax);
//		}
//
//		ymax--;
//	}
//
//	delete[] vectors;
//}

void fill_triangle(vector v1, vector v2, vector v3)
{
	int xmin = v1.x,
		xmax = xmin,
		ymax = v1.y,
		ymin = ymax,
		y;
	stack<int>* xs = nullptr;

	if (v2.x > xmax) xmax = v2.x;
	else if (v2.x < xmin) xmin = v2.x;

	if (v2.y > ymax) ymax = v2.y;
	else if (v2.y < ymin) ymin = v2.y;

	if (v3.x > xmax) xmax = v3.x;
	else if (v2.x < xmin) xmin = v2.x;

	if (v3.y > ymax) ymax = v3.y;
	else if (v3.y < ymin) ymin = v3.y;

	y = ymax;

	while (y != ymin - 1)
	{
		int x1 = 0, x2 = 0;
		int x = 0;
		
		if (y >= min(v1.y, v2.y) and y <= max(v1.y, v2.y))
		{
			x = round((y - v1.y) * ((float)(v2.x - v1.x) / (v2.y - v1.y)) + v1.x);
			if (x >= xmin and x <= xmax) xs = in_stack(xs, x);
		}

		if (y >= min(v2.y, v3.y) and y <= max(v2.y, v3.y))
		{
			x = round((y - v2.y) * ((float)(v3.x - v2.x) / (v3.y - v2.y)) + v2.x);
			if (x >= xmin and x <= xmax) xs = in_stack(xs, x);
		}

		if (y >= min(v3.y, v1.y) and y <= max(v3.y, v1.y))
		{
			x = round((y - v3.y) * ((float)(v1.x - v3.x) / (v1.y - v3.y)) + v3.x);
			if (x >= xmin and x <= xmax) xs = in_stack(xs, x);
		}

		while (xs)
		{
			xs = out_stack(xs, &x1);
			//if (xs)
			//{
			//	if (x1 == x2) xs = out_stack(xs, &x1);
			//}
			if (not xs) break;
			xs = out_stack(xs, &x2);

			linesBrasenhem(x1, y, x2, y);
		}

		y--;
	}
}

void fillsgood(vector* vertices, int n)
{
	for (int i = 2; i < n; i++) //lol
	{
		fill_triangle(vertices[0], vertices[i - 1], vertices[i]); 
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


//10 10
//20 20
//30 10
//40 20
//50 10
//60 20
//70 10
//70 20
//60 30
//50 20
//40 30
//30 20
//20 30
//10 20 *


//10 0
//60 15
//40 30
//45 5
//30 20

//10 10
//60 10
//60 60
//30 20
//10 60



//10 10
//50 10
//50 50
//30 70
//10 50