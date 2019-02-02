//---------------------------------------
// Program: gasket2d.cpp
// Purpose: To display 2D Sierpenski gasket
// Author:  John Gauch
// Date:    September 2008
//---------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Global variables
#define MAX_LEVEL 7
int level = 0;

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

//---------------------------------------
// Function to draw 2D Sierpinski gasket
//---------------------------------------
void gasket(int n, float ax, float ay, float bx, float by, float cx, float cy)
{
   // Handle recursive case
   if (n > 0)
   {
      float dx = (ax + bx) / 2;
      float dy = (ay + by) / 2;
      float ex = (bx + cx) / 2;
      float ey = (by + cy) / 2;
      float fx = (cx + ax) / 2;
      float fy = (cy + ay) / 2;
      gasket(n - 1, ax, ay, dx, dy, fx, fy);
      gasket(n - 1, bx, by, ex, ey, dx, dy);
      gasket(n - 1, cx, cy, fx, fy, ex, ey);
   }

   // Draw single trangle
   else
   {
      glVertex2f(ax, ay);
      glVertex2f(bx, by);
      glVertex2f(cx, cy);
   }
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
   glClear(GL_COLOR_BUFFER_BIT);
   glBegin(GL_TRIANGLES);
   glColor3f(1.0, 0.0, 0.0);
   gasket(level, 0, 0.5, -0.5, -0.5, 0.5, -0.5);
   glEnd();
   glFlush();
}

//---------------------------------------
// Keyboard callback for OpenGL
//---------------------------------------
void keyboard(unsigned char key, int x, int y)
{
   if (key == '+')
      level = (level + 1) % MAX_LEVEL;
   else if (key == '-')
      level = (level + MAX_LEVEL - 1) % MAX_LEVEL;

   // Redraw objects
   glutPostRedisplay();
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(250, 250);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
   glutCreateWindow("Gasket2D");
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   init();
   glutMainLoop();
   return 0;
}

