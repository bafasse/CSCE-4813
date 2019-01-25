//---------------------------------------
// Program: model_view.cpp
// Purpose: To model made of blocks
// Author:  John Gauch
// Date:    Spring 2013
//---------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <fstream>
#include <iostream>
using namespace std;

// Model variables 
const int MAX_BLOCK = 1000;
int block_count = 0;
float wmin = 0.0;
float wmax = 0.0;
float xmin[MAX_BLOCK];
float ymin[MAX_BLOCK];
float zmin[MAX_BLOCK];
float xmax[MAX_BLOCK];
float ymax[MAX_BLOCK];
float zmax[MAX_BLOCK];

// Display variables
int xangle = 0;
int yangle = 0;
int zangle = 0;
GLenum mode = GL_LINE_LOOP;
// GLenum mode = GL_POLYGON;

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init(char *filename)
{
   // Read input file
   ifstream din;
   din.open(filename);
   while (!din.eof() && block_count < MAX_BLOCK) 
   {
      string object;
      din >> object;
      if (object == "block")
      {
         din >> xmin[block_count] >> ymin[block_count] >> zmin[block_count];
         if (wmin > xmin[block_count]) wmin = xmin[block_count];
         if (wmin > ymin[block_count]) wmin = ymin[block_count];
         if (wmin > zmin[block_count]) wmin = zmin[block_count];
         din >> xmax[block_count] >> ymax[block_count] >> zmax[block_count];
         if (wmax < xmax[block_count]) wmax = xmax[block_count];
         if (wmax < ymax[block_count]) wmax = ymax[block_count];
         if (wmax < zmax[block_count]) wmax = zmax[block_count];
         block_count++;
      }
   }
   din.close();

   // Initialize OpenGL
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   float delta = (wmax - wmin) / 2;
   wmin -= delta;
   wmax += delta;
   glOrtho(wmin, wmax, wmin, wmax, wmin, wmax);
   glEnable(GL_DEPTH_TEST);
}

//---------------------------------------
// Function to draw 3D block
//---------------------------------------
void block(float xmin, float ymin, float zmin,
           float xmax, float ymax, float zmax)
{
   // Define 8 vertices
   float ax = xmin, ay = ymin, az = zmax;
   float bx = xmax, by = ymin, bz = zmax;
   float cx = xmax, cy = ymax, cz = zmax;
   float dx = xmin, dy = ymax, dz = zmax;
   float ex = xmin, ey = ymin, ez = zmin;
   float fx = xmax, fy = ymin, fz = zmin;
   float gx = xmax, gy = ymax, gz = zmin;
   float hx = xmin, hy = ymax, hz = zmin;

   // Draw 6 faces
   glBegin(mode);
   glColor3f(1.0, 0.0, 0.0);
   glVertex3f(ax, ay, az);
   glVertex3f(bx, by, bz);
   glVertex3f(cx, cy, cz);
   glVertex3f(dx, dy, dz);
   glEnd();

   glBegin(mode);
   glColor3f(0.0, 1.0, 0.0);
   glVertex3f(ax, ay, az);
   glVertex3f(dx, dy, dz);
   glVertex3f(hx, hy, hz);
   glVertex3f(ex, ey, ez);
   glEnd();

   glBegin(mode);
   glColor3f(0.0, 0.0, 1.0);
   glVertex3f(ax, ay, az);
   glVertex3f(ex, ey, ez);
   glVertex3f(fx, fy, fz);
   glVertex3f(bx, by, bz);
   glEnd();

   glBegin(mode);
   glColor3f(0.0, 1.0, 1.0);
   glVertex3f(gx, gy, gz);
   glVertex3f(fx, fy, fz);
   glVertex3f(ex, ey, ez);
   glVertex3f(hx, hy, hz);
   glEnd();

   glBegin(mode);
   glColor3f(1.0, 0.0, 1.0);
   glVertex3f(gx, gy, gz);
   glVertex3f(cx, cy, cz);
   glVertex3f(bx, by, bz);
   glVertex3f(fx, fy, fz);
   glEnd();

   glBegin(mode);
   glColor3f(1.0, 1.0, 0.0);
   glVertex3f(gx, gy, gz);
   glVertex3f(hx, hy, hz);
   glVertex3f(dx, dy, dz);
   glVertex3f(cx, cy, cz);
   glEnd();
}

//---------------------------------------
// Keyboard callback for OpenGL
//---------------------------------------
void keyboard(unsigned char key, int x, int y)
{
   // Update angles
   if (key == 'x')
      xangle -= 5;
   else if (key == 'X')
      xangle += 5;
   else if (key == 'y')
      yangle -= 5;
   else if (key == 'Y')
      yangle += 5;
   else if (key == 'z')
      zangle -= 5;
   else if (key == 'Z')
      zangle += 5;

   // Redraw objects
   glutPostRedisplay();
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
   // Rotate objects
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glRotatef(xangle, 1.0, 0.0, 0.0);
   glRotatef(yangle, 0.0, 1.0, 0.0);
   glRotatef(zangle, 0.0, 0.0, 1.0);

   // Draw geometric object
   for (int i=0; i<block_count; i++)
      block(xmin[i], ymin[i], zmin[i], xmax[i], ymax[i], zmax[i]);
   glFlush();
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(250, 250);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
   glutCreateWindow("Model View");
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   init(argv[1]);
   glutMainLoop();
   return 0;
}
