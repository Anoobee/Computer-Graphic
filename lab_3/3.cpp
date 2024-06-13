// mid point circle
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

int height = 1000, width = 1000;
void display();
void reshape(int, int);
void circle_draw();
void takeData();
void each_octant(float, float);
float Xc, Yc, R;
void init() // (background color) to black
{
    glClearColor(0, 0, 0, 1.0);
}

int main(int argc, char **argv)
{
    takeData();
    glutInit(&argc, argv);         // initializes the GLUT library.
    glutInitDisplayMode(GLUT_RGB); //  sets the initial display mode to RGB.

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(width, height);

    glutCreateWindow("Ellipse"); // title of the window
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    init();

    glutMainLoop();
}

void each_octant(float x, float y)
{
    glVertex2f(x + Xc, y + Yc);
    glVertex2f(y + Xc, x + Yc);

    glVertex2f(x + Xc, -y + Yc);
    glVertex2f(y + Xc, -x + Yc);

    glVertex2f(-x + Xc, -y + Yc);
    glVertex2f(-y + Xc, -x + Yc);

    glVertex2f(-x + Xc, y + Yc);
    glVertex2f(-y + Xc, x + Yc);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glBegin(GL_POINTS);
    circle_draw();
    glEnd();

    glFlush();
}

void reshape(int w, int h) // width and height
{
    glViewport(0, 0, w, h); // two points for window
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-width / 2, width / 2, -height / 2, height / 2);
    glMatrixMode(GL_MODELVIEW);
}

// function

void circle_draw()
{

    glColor3f(1, 1, 1);
    float x1, y1, r, p;
    x1 = 0;
    y1 = R;
    r = R;
    p = 5 / 4 - r;

    while (x1 < y1)
    {
        if (p < 0)
        {
            x1++;
            p = p + 2 * x1 + 1;
        }
        else
        {
            x1++;
            y1--;
            p = p + 2 * x1 + 1 - 2 * y1;
        }

        each_octant(x1, y1);
    }
}

void takeData()
{

    cout << "enter the center";
    cin >> Xc >> Yc;
    cout << "enter the radius";
    cin >> R;
}
