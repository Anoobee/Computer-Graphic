// Bresenham’s Line algorithm

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

int height = 1000, width = 1000;
void display();
void reshape(int, int);
void b_draw();
void takeData();
float X1, X2, Y1, Y2;
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

    glutCreateWindow("Bresenham’"); // title of the window
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    init();

    glutMainLoop();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glBegin(GL_POINTS);
    b_draw();
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

void b_draw()
{

    glColor3f(1, 1, 1);
    float x1, x2, y1, y2, p, mx, my, dx, dy;
    x1 = X1;
    x2 = X2;
    y1 = Y1;
    y2 = Y2;
    dx = x2 - x1;
    dy = y2 - y1;

    if (dx > dy) // case 1
    {
        p = 2 * dy - dx;
        while (x1 <= x2)
        {
            glVertex2f(x1, y1);
            x1++;
            if (p < 0)
            {
                p = p + 2 * dy;
            }
            else
            {
                p = p + 2 * dy - 2 * dx;
                y1++;
            }
        }
    }
    else // case 2
    {
        p = 2 * dy - dx;

        while (y1 <= y2)
        {
            glVertex2f(x1, y1);
            y1++;
            if (p < 0)
            {
                p = p + 2 * dx;
            }
            else
            {
                p = p + 2 * dx - 2 * dy;
                x1++;
            }
        }
    }
}

void takeData()
{

    cout << "enter initial point: ";
    cin >> X1 >> Y1;
    cout << "enter final point: ";
    cin >> X2 >> Y2;
}
