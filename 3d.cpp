#include <iostream>
#include <glut.h>
#include <math.h>
using namespace std;
#define PI 3.14159

int w = 500, h = 500;
unsigned int Key = 9;

//Animation Variables
float XPosition = -10.0;
bool Right = true;
float Angle = 0.0;

// 2D Shapes
void DrawAxis(float left, float right, float top, float bot)
{
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
		glVertex2f(left, 0);
		glVertex2f(right, 0);
		glVertex2f(0, top);
		glVertex2f(0, bot);
	glEnd();
}

void DrawPoint(float x, float y)
{
	glPointSize(5.0);
	glBegin(GL_POINTS);
		glVertex2f(x, y);
	glEnd();
}

void DrawTriangles()
{
	glBegin(GL_TRIANGLES);
		glVertex2f(0.0, 0.0);
		glVertex2f(1.0, 0.0);
		glVertex2f(1.5, 1.5);
		glVertex2f(-1.0, -1.0);
		glVertex2f(-1.0, 1.0);
		glVertex2f(0.0, 0.0);
		glVertex2f(5.0, 5.0);
	glEnd();
}

void DrawSquares(float XPosition)
{
	glTranslatef(0, 0, XPosition);
	glBegin(GL_QUADS);
		//glShadeModel(GL_SMOOTH);
		glColor3f(1, 0, 0);
		glVertex3f(-1, 1.0, 0);
		glColor3f(1, 1, 0);
		glVertex3f(-1, -1.0, 0);
		glColor3f(0, 1, 1);
		glVertex3f(1, -1.0, 0);
		glColor3f(0, 0, 1);
		glVertex3f(1, 1.0, 0);
		// Bad Practice Transformation
		//glVertex2f(XPosition, 1.0);
		//glVertex2f(XPosition, -1.0);
		//glVertex2f(XPosition+2, -1.0);
	glEnd();
}

//void DrawPolygon()
//{
//	glBegin(GL_POLYGON);
//	glEnd();
//}

void DrawSine()
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
		for (float x = -20.0; x < 20.0; x += 0.01)
		{
			glVertex2f(x, sin(x));
		}
	glEnd();
}

void DrawCosine()
{
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_STRIP);
		for (float x = -20.0; x < 20.0; x += 0.01)
		{
			glVertex2f(x, cos(x));
		}
	glEnd();
}

void DrawOutlinedCircle()
{
	float i, x, y;

	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_STRIP);
		for (i = 0; i <= 2 * PI; i += 0.01)
		{
			x = 10 * cos(i);
			y = 10 * sin(i);
			glVertex2f(x, y);
		}
	glEnd();
}

void DrawFilledCircle()
{
	float i, x, y;

	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_TRIANGLE_FAN);
		for (i = 0; i <= 2 * PI; i += 0.1)
		{
			x = 5 * cos(i);
			y = 5 * sin(i);
			glVertex2f(x, y);
		}
	glEnd();
}

void Bresenham(int x1, int y1, int x2, int y2) {
	for (int octan = 1; octan <= 8; octan++) {
		int x = x1;
		int y = y1;
		int dx = x2 - x1;
		int dy = y2 - y1;
		int dT = 2 * (dy - dx);
		int dS = 2 * dy;
		int d = (2 * dy) - dx;
		DrawPoint(x, y);
		while (x < x2) {
			x++;
			if (d < 0) {
				d += dS;
			}
			else {
				y++;
				d += dT;
			}
			if (octan == 1) {
				DrawPoint(x, y);
			}
			else if (octan == 2) {
				DrawPoint(y, x);
			}
			else if (octan == 3) {
				DrawPoint(-y, x);
			}
			else if (octan == 4) {
				DrawPoint(-x, y);
			}
			else if (octan == 5) {
				DrawPoint(-x, -y);
			}
			else if (octan == 6) {
				DrawPoint(-y, -x);
			}
			else if (octan == 7) {
				DrawPoint(y, -x);
			}
			else if (octan == 8) {
				DrawPoint(x, -y);
			}
		}
	}
}

// 3D Shapes
void DrawCube()
{
	//Move Z Axis of the Cube to -8
	glTranslatef(0, 0, -8);
	//Rotate all Axis
	glRotatef(Angle, 1, 1, 1);
	// glRotatef(Angle, 1, 0, 0);
	// glRotatef(Angle, 0, 1, 0);
	// glRotatef(Angle, 0, 0, 1);
	glBegin(GL_QUADS);
		//front
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-1.0, 1.0, 1.0);
		glVertex3f(-1.0, -1.0, 1.0);
		glVertex3f(1.0, -1.0, 1.0);
		glVertex3f(1.0, 1.0, 1.0);
		//back
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(1.0, 1.0, -1.0);
		glVertex3f(1.0, -1.0, -1.0);
		glVertex3f(-1.0, -1.0, -1.0);
		glVertex3f(-1.0, 1.0, -1.0);
		//right
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(1.0, 1.0, 1.0);
		glVertex3f(1.0, -1.0, 1.0);
		glVertex3f(1.0, -1.0, -1.0);
		glVertex3f(1.0, 1.0, -1.0);
		//left
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(-1.0, 1.0, -1.0);
		glVertex3f(-1.0, -1.0, -1.0);
		glVertex3f(-1.0, -1.0, 1.0);
		glVertex3f(-1.0, 1.0, 1.0);
		//top
		glColor3f(0.0, 1.0, 1.0);
		glVertex3f(-1.0, 1.0, -1.0);
		glVertex3f(-1.0, 1.0, 1.0);
		glVertex3f(1.0, 1.0, 1.0);
		glVertex3f(1.0, 1.0, -1.0);
		//bottom
		glColor3f(1.0, 0.0, 1.0);
		glVertex3f(-1.0, -1.0, -1.0);
		glVertex3f(-1.0, -1.0, 1.0);
		glVertex3f(1.0, -1.0, 1.0);
		glVertex3f(1.0, -1.0, -1.0);
	glEnd();
}

void DrawPyramid()
{
	glTranslatef(0, 0, -4);
	glRotatef(Angle, 1, 1, 1);
	glBegin(GL_TRIANGLES);
		//front
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0, 1.0, 0);
		glVertex3f(-1.0, -1.0, 1.0);
		glVertex3f(1.0, -1.0, 1.0);
		//back
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0, 1.0, 0);
		glVertex3f(-1.0, -1.0, -1.0);
		glVertex3f(1.0, -1.0, -1.0);
		//right
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(1.0, -1.0, -1.0);
		glVertex3f(1.0, -1.0, 1.0);
		glVertex3f(0, 1.0, 0);
		//left
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(-1.0, -1.0, -1.0);
		glVertex3f(-1.0, -1.0, 1.0);
		glVertex3f(0, 1.0, 0);
	glEnd();
	glBegin(GL_QUADS);
		//bottom
		glColor3f(1.0, 0.0, 1.0);
		glVertex3f(-1.0, -1.0, -1.0);
		glVertex3f(-1.0, -1.0, 1.0);
		glVertex3f(1.0, -1.0, 1.0);
		glVertex3f(1.0, -1.0, -1.0);
	glEnd();
}
// Functionality Functions
void myMouse(int button, int state, int x, int y)
{
	cout << x << " " << y << endl;

	x = (x / (w / 200)) - 100;
	y = 100 - (y / (h / 200));
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		DrawPoint(x, y);
	}
}

void keyboard(unsigned char keyPressed, int xMouse, int yMouse)
{
	cout << "Key: " << keyPressed << endl ;
	Key = keyPressed;
}


void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	//Draw
	//DrawAxis(-10, 10, 10, -10);
	//DrawSine();
	//DrawCosine();
	//DrawOutlinedCircle();
	//DrawFilledCircle();
	//Bresenham(0, 0, 6, 2);
	//Points();
	//Triangles();
	//Square(XPosition);
	//DrawCube();
	DrawPyramid();
	
	glutMouseFunc(myMouse);
	glutKeyboardFunc(keyboard);
	switch (Key)
	{
	case '0': case '5':
		DrawSine();
		break;

	case '1':
		DrawOutlinedCircle();
		break;

	case '2':
		DrawFilledCircle();
		break;

	case 'r': case 'R':
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		glFlush();
		break;

	default:
		break;
	}

	//Animation
	Angle < 360 ? Angle += .8 : Angle -= 360;
	switch (Right)
	{
	case true:
		if (XPosition < -5)
			XPosition += .16;
		else
			Right = false;
		break;

	case false:
		if (XPosition > -25)
			XPosition -= .16;
		else
			Right = true;
		break;

	default:
		break;
	}

	//glFlush();
	glutSwapBuffers();
}


void Timer(int)
{
	glutPostRedisplay();	//Redisplay Window
	glutTimerFunc(1000 / 60, Timer, 0);	//Set FPS (60)
}

void Reshape(int width, int hieght)
{
	glViewport(0, 0, width, hieght);	//Specifies screen viewport
	glClearColor(1, 1, 1, 0);	//Background Color

	glMatrixMode(GL_PROJECTION);	//How 3D scene's projected on screen
	glLoadIdentity();	//Reset Transformations
	//gluOrtho2D(-10, 10, -10, 10);	//Creates two-dimensional volume
	gluPerspective(60, 1, 2.0, 50.0);	//Creates 3D volume, Defining FoV-Y Angle, W:H Ratio, zNear, zFar
	//Note: The Observer'd be on origin point; Z index availabe 0 -> -infinity. (-2, -50)

	//We Specified projection, then switched to model view again
	glMatrixMode(GL_MODELVIEW);	//Defines how objects r transformed
	w = width;
	h = hieght;
}

void Initialize(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);	//Display Modes: GLUT_DOUBLE - double buffered window, GLUT_DEPTH - Depth(Z) buffer

	//Program Window
	glutInitWindowPosition(400, 110);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Graphics");
	glutReshapeFunc(Reshape);	//Reshape callback for the current window

	glEnable(GL_DEPTH_TEST);	//Enable Z Buffer; Note: Didn't work when intialized b4 window init

	glutDisplayFunc(Display);	//Display callback Current window, rendering whenever the window needs to be drawn
	glutTimerFunc(0, Timer, 0);	//Redisplay - Callback function in a set amount of time; ms, func, value
	glutMainLoop();	//Put program on loop
}

int main(int argc, char** argv) 
{
	Initialize(argc, argv);
}