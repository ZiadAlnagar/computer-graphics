#include <iostream>
#include <glut.h>
#include <math.h>

using namespace std;

#define PI 3.14159

const float RAD2DEG = 180 / 3.141592653;

int Width, Height,
    MouseX, MouseY,
    Clear = 1;

float Angle = 0.0,
      XPosition = -75;
bool IsRight = true;

char Key;

void DrawAxis(float left, float right, float top, float down)
{
    glBegin(GL_LINES);
    glVertex2f(left, 0.0);
    glVertex2f(right, 0.0);
    glVertex2f(0.0, top);
    glVertex2f(0.0, down);
    glEnd();
}

void DrawPoint(float x, float y)
{
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void DrawTriangle()
{
    glBegin(GL_TRIANGLES);
    glVertex2f(-50.0, 0.0);
    glVertex2f(-30.0, 0.0);
    glVertex2f(-40.0, 20.0);
    glVertex2f(10.0, 0);
    glVertex2f(30.0, 0.0);
    glVertex2f(20.0, -10.0);
    glEnd();
}

void DrawSquare()
{
    glTranslatef(XPosition, 0, 0);
    glRotatef(Angle, 0, 0, 1);
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glVertex2f(-25, -25);
    glVertex2f(25, -25);
    glVertex2f(25, 25);
    glVertex2f(-25, 25);
    glEnd();
}

void DrawPolygon()
{
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);

    glEnd();
}

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

void Bresenham(int x1, int y1, int x2, int y2)
{
    for (int octan = 1; octan <= 8; octan++)
    {
        int x = x1;
        int y = y1;
        int dx = x2 - x1;
        int dy = y2 - y1;
        int dT = 2 * (dy - dx);
        int dS = 2 * dy;
        int d = (2 * dy) - dx;
        DrawPoint(x, y);
        while (x < x2)
        {
            x++;
            if (d < 0)
            {
                d += dS;
            }
            else
            {
                y++;
                d += dT;
            }
            if (octan == 1)
            {
                DrawPoint(x, y);
            }
            else if (octan == 2)
            {
                DrawPoint(y, x);
            }
            else if (octan == 3)
            {
                DrawPoint(-y, x);
            }
            else if (octan == 4)
            {
                DrawPoint(-x, y);
            }
            else if (octan == 5)
            {
                DrawPoint(-x, -y);
            }
            else if (octan == 6)
            {
                DrawPoint(-y, -x);
            }
            else if (octan == 7)
            {
                DrawPoint(y, -x);
            }
            else if (octan == 8)
            {
                DrawPoint(x, -y);
            }
        }
    }
}

void Mouse(int button, int state, int x, int y)
{
    x = (x / (Width / 200)) - 100;
    y = 100 - (y / (Height / 200));

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        cout << x << " " << y << endl;
        MouseX = x;
        MouseY = y;
        Clear = 0;
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        Clear = 1;
}

void Keyboard(unsigned char keyPressed, int xMouse, int yMouse)
{
    Key = keyPressed;
    cout << "Key: " << Key << endl;
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0.0, 0.0, 0.0);

    //DRAW
    DrawAxis(-100.0, 100.0, 100.0, -100.0);
    // DrawPoint(-5.0, -5.0);
    DrawTriangle();
    //DrawSquare();

    float angle = atan(2.0) * RAD2DEG; // 63.43;
    // glPushMatrix();
    // glScaled(1, -1, 1);
    // DrawTriangle();
    // glPopMatrix();
    glPushMatrix();
    glTranslated(0, 40, 0);
    glScaled(1, -1, 1);
    glTranslated(0, -40, 0);
    DrawTriangle();
    glPopMatrix();
    // DrawSine();
    // DrawCos();
    //Bresenham(0, 0, 60, 20);

    glutMouseFunc(Mouse);
    if (Clear == 0)
        DrawPoint(MouseX, MouseY);

    glutKeyboardFunc(Keyboard);
    switch (Key)
    {
    case '0':
    case '5':
        DrawSine();
        break;

    case '1':
        DrawTriangle();
        break;

    case '2':
        //DrawFilledCircle();
        break;

    case 'r':
    case 'R':
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        DrawAxis(-100.0, 100.0, 100.0, -100.0);
        glFlush();
        break;

    default:
        break;
    }

    Angle < 360 ? Angle += .8 : Angle -= 360;

    Angle < 360 ? Angle += 0.8 : Angle -= 360;
    switch (IsRight)
    {
    case true:
        if (XPosition < 75)
            XPosition += 1;
        else
            IsRight = false;
        break;

    case false:
        if (XPosition > -75)
            XPosition -= 1;
        else
            IsRight = true;
        break;
    }

    // glFlush();
    glutSwapBuffers();
}

void Timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, Timer, 0);
}

void SetTransformations(int w, int h)
{
    Width = w;
    Height = h;
    glClearColor(1.0, 1.0, 1.0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void Initialize(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_RGBA | GL_DOUBLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(450, 125);
    glutCreateWindow("2D Computer Graphics");
    glutReshapeFunc(SetTransformations);
    glutDisplayFunc(Display);
    glutTimerFunc(0, Timer, 0);
    glutMainLoop();
}

void main(int argc, char *argv[])
{
    Initialize(argc, argv);
}