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
int is_convex(vector* vertices, int n);
void fill_convex(vector* vertices, int n);
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
	
	if (is_convex(vertices, n) == -1) cout << "Convex";
	else						cout << "NonConvex";

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);

	for (int i = 0; i < n - 1; i++)
		linesBrasenhem(vertices[i].x, vertices[i].y, vertices[i + 1].x, vertices[i + 1].y);
	linesBrasenhem(vertices[n - 1].x, vertices[n - 1].y, vertices[0].x, vertices[0].y);

	glColor3f(1, 1, 1);

	fillsgood(vertices, n);
	//fill_convex(vertices, n);
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

int is_convex(vector* vertices, int n)
{
	vector* vectors = get_vectors(vertices, n);

	int t = vectors[n - 1].x*vectors[0].y - vectors[n - 1].y*vectors[0].x;

	for (int i = 0; i < n - 1; i++)
	{
		if (t*(vectors[i].x*vectors[i + 1].y - vectors[i].y*vectors[i + 1].x) < 0)
		{
			delete[] vectors;
			return i;
		}
	}

	delete[] vectors;
	return -1;
}

void fill_convex(vector* vertices, int n)
{
	int ymax = vertices[0].y,
	    ymin = ymax;
	vector* vectors = get_vectors(vertices, n);
	stack<int>* xs = nullptr;
	
	for (int i = 1; i < n; i++)
	{
		if (vertices[i].y > ymax) ymax = vertices[i].y;
		else if (vertices[i].y < ymin) ymin = vertices[i].y;
	}

	while (ymax != ymin - 1)
	{
		int x1 = 0, x2 = 0;
		int x = 0;

		for (int i = 0; i < n; i++)
		{
			if (ymax < min(vertices[i].y, vertices[i].y + vectors[i].y) or
				ymax > max(vertices[i].y, vertices[i].y + vectors[i].y)) continue;

			x = round((ymax - vertices[i].y)*((float)vectors[i].x/vectors[i].y) + vertices[i].x);
			if (x >= min(vertices[i].x, vertices[i].x + vectors[i].x) and
				x <= max(vertices[i].x, vertices[i].x + vectors[i].x)) xs = in_stack(xs, x);
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

			linesBrasenhem(x1, ymax, x2, ymax);
		}

		ymax--;
	}

	delete[] vectors;
}

//void fillsgood(vector* vertices, int n)
//{
//	if (n == 3)
//	{
//		fill_convex(vertices, 3);
//		return;
//	}
//
//	int k;
//
//	while ((k = is_convex(vertices, n)) != -1)
//	{
//		vector* vectors = get_vectors(vertices, n);
//
//
//
//		//if (n - k == 2)
//		//{
//		//	vector temp[3] = {vertices[k], vertices[k + 1], vertices[0]};
//		//	fill_convex(temp, 3);
//		//}
//		//else if (n - k == 1)
//		//{
//		//	vector temp[3] = {vertices[k], vertices[0], vertices[1]};
//		//	fill_convex(temp, 3);
//		//
//		//	vertices++;
//		//	n--;
//		//	continue;
//		//}
//		//else fill_convex(vertices + k, 3);
//		//
//		//n--;
//		//for (int i = k + 1; i < n; i++)
//		//	vertices[i] = vertices[i + 1];		
//	}
//
//	fill_convex(vertices, n);
//	
//}

void fillsgood(vector* vertices, int n)
{
	int k;

	if ((k = is_convex(vertices, n)) != -1)
	{
		vector* vectors = get_vectors(vertices, n);
		int x, y, tx, ty, i = k + 2;

		while (i < n - 1)
		{
			x = round(vertices[i].x + vectors[i].x * ((float)vertices[i].x - vertices[k].x) / (vectors[k].x - vectors[i].x));
			y = round(vertices[i].y + vectors[i].y * ((float)vertices[i].x - vertices[k].x) / (vectors[k].x - vectors[i].x));
			
			if (x >= min(vertices[i].x, vertices[i].x + vectors[i].x) and
				x <= max(vertices[i].x, vertices[i].x + vectors[i].x) and
				y >= min(vertices[i].y, vertices[i].y + vectors[i].y) and
				y <= max(vertices[i].y, vertices[i].y + vectors[i].y)) break;

			i++;
		}


		while (i < n - 1)
		{
			tx = round(vertices[i].x + vectors[i].x * ((float)vectors[k].x*(vertices[i].y - vertices[k].y) - vectors[k].y*(vertices[i].x - vertices[k].x)) / (vectors[i].x*vectors[k].y - vectors[k].x*vectors[i].y));
			ty = round(vertices[i].y + vectors[i].y * ((float)vectors[k].x*(vertices[i].y - vertices[k].y) - vectors[k].y*(vertices[i].x - vertices[k].x)) / (vectors[i].x*vectors[k].y - vectors[k].x*vectors[i].y));

			if (tx >= min(vertices[i].x, vertices[i].x + vectors[i].x) and
				tx <= max(vertices[i].x, vertices[i].x + vectors[i].x) and
				ty >= min(vertices[i].y, vertices[i].y + vectors[i].y) and
				ty <= max(vertices[i].y, vertices[i].y + vectors[i].y) and
				(tx - vertices[k].x)*(tx - vertices[k].x) + (ty - vertices[k].y)*(ty - vertices[k].y) < (x - vertices[k].x)*(x - vertices[k].x) + (y - vertices[k].y)*(y - vertices[k].y))
			{
				x = tx;
				y = ty;
			}

			i++;
		}

		delete[] vectors;

		linesBrasenhem(vertices[k].x, vertices[k].y, x, y);



	}
	else fill_convex(vertices, n);
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

//���������� ������ �������� ��-�� ����������� (� ������ � ���� ����������) ������ �� ������.
//���� ������� ��������� ��� ����� �����������, � ����� �������� ����� ������ �����, ���� ���� ����� ����� ������� x, �� ��, ����������


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
//20 50
//30 70
//10 50