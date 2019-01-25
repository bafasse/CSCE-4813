//---------------------------------------
// Program: process.cpp
// Purpose: Interactive image processing
// Author:  John Gauch
// Date:    Spring 2014
//---------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "libim/im_float.h"

// Global constants
#define MIN_X 0
#define MAX_X 499
#define MIN_Y 0
#define MAX_Y 499
#define MIN_Z 0
#define MAX_Z 499
#define DISTANCE 10

// Global variables
float X_previous = 0;
float Y_previous = 0;
float X_current = 0;
float Y_current = 0;

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(MIN_X, MAX_X, MIN_Y, MAX_Y, MIN_Z, MAX_Z);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glEnable(GL_DEPTH_TEST);
}

//---------------------------------------
// Mouse callback for OpenGL
//---------------------------------------
void mouse(int button, int state, int x, int y)
{
   if ((x < MIN_X) || (x > MAX_X)|| (y < MIN_Y)|| (y > MAX_Y)) return;
   X_current = x;
   Y_current = y;
   if (fabs(X_current-X_previous) + fabs(Y_current-Y_previous) > DISTANCE)
   {
      X_previous = X_current;
      Y_previous = Y_current;
      glutPostRedisplay();
   }
}

//---------------------------------------
// Motion callback for OpenGL
//---------------------------------------
void motion(int x, int y)
{
   if ((x < MIN_X) || (x > MAX_X)|| (y < MIN_Y)|| (y > MAX_Y)) return;
   X_current = x;
   Y_current = y;
   if (fabs(X_current-X_previous) + fabs(Y_current-Y_previous) > DISTANCE)
   {
      X_previous = X_current;
      Y_previous = Y_current;
      glutPostRedisplay();
   }
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
   // Clear display window
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   printf("x=%f, y=%f\n", X_current, Y_current);
   glFlush();
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
   // Read input image
   im_float Image;
   Image.ReadJpg(argv[1]);

   // Initialize interface
   glutInit(&argc, argv);
   glutInitWindowSize(MAX_Y-MIN_Y+1, MAX_X-MIN_Y+1);
   glutInitWindowPosition(MAX_Y/2, MAX_X/2);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
   glutCreateWindow("Process");
   glutDisplayFunc(display);
   glutMouseFunc(mouse);
   glutMotionFunc(motion);
   init();
   glutMainLoop();
   return 0;
}
