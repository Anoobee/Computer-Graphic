// mid point ellispe

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

int height = 1000, width = 1000;
void display();
void reshape(int, int);
void draw_ellipse();
void takeData();
void each_quadrant(float, float);
float Xc, Yc, R_X, R_Y;

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

void each_quadrant(float x, float y)
{
    glVertex2f(x + Xc, y + Yc);
    glVertex2f(x + Xc, -y + Yc);
    glVertex2f(-x + Xc, -y + Yc);
    glVertex2f(-x + Xc, y + Yc);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glBegin(GL_POINTS);
    draw_ellipse();
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
void draw_ellipse()
{
    glColor3f(1, 1, 1);

    float x1, y1, rx, ry, p1, p2, diff;
    x1 = 0;
    y1 = R_Y; // Assuming R_X and R_Y are initialized correctly
    rx = R_X;
    ry = R_Y;

    // Initialize parameters for the algorithm
    p1 = ry * ry - rx * rx * ry + 0.25 * rx * rx;
    diff = 2 * ry * ry * x1 + ry * ry - 2 * rx * rx * y1;

    // First region: x >= 0
    while (2 * ry * ry * x1 <= 2 * rx * rx * y1)
    {
        each_quadrant(x1, y1); // Plot points in all four quadrants

        x1++;
        if (p1 < 0)
        {
            p1 += 2 * ry * ry * x1 + ry * ry;
        }
        else
        {
            y1--;
            p1 += 2 * ry * ry * x1 - 2 * rx * rx * y1 + ry * ry;
        }
    }

    // Second region: x > 0
    p2 = ry * ry * (x1 + 0.5) * (x1 + 0.5) + rx * rx * (y1 - 1) * (y1 - 1) - rx * rx * ry * ry;
    while (y1 >= 0)
    {
        each_quadrant(x1, y1); // Plot points in all four quadrants

        y1--;
        if (p2 > 0)
        {
            p2 += -2 * rx * rx * y1 + rx * rx;
        }
        else
        {
            x1++;
            p2 += 2 * ry * ry * x1 - 2 * rx * rx * y1 + rx * rx;
        }
    }
}

void takeData()
{
    cout << "Enter the center (Xc, Yc): ";
    cin >> Xc >> Yc;
    cout << "Enter the major radius (Rx  ): ";
    cin >> R_X;
    cout << "Enter the minor radius (Ry): ";
    cin >> R_Y;
}
