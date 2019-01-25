//---------------------------------------
// Program: bitmap.cpp
// Purpose: To display several bitmaps
// Author:  John Gauch
// Date:    April 2010
//---------------------------------------
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
using namespace std;

#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Global variables
int step = 0;

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
// Display message on screen
//---------------------------------------
void display_message(string message)
{
   for (int i=0; i<int(message.length()); i++)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, message[i]);
}

//---------------------------------------
// Display integer on screen
//---------------------------------------
void display_integer(int num)
{
   stringstream s;
   s << num;
   display_message(s.str());
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
   // Define checker board bitmap
   glClear(GL_COLOR_BUFFER_BIT);
   GLubyte wb[2] = {0x00, 0xff};
   GLubyte check[512];
   int i, j;
   for (i=0;i<64;i++)
   for (j=0;j<8;j++)
      check[i*8+j] = wb[(i/8+j)%2];

   // Display checker board bitmap 
   glColor3f(1.0, 0.0, 0.0);
   glRasterPos3f(-0.1, -0.3, 0.0);
   glBitmap(64, 64, 0.0, 0.0, 0.0, 0.0, check);

   glColor3f(0.0, 1.0, 0.0);
   glRasterPos3f(0.3, 0.2, 0.0);
   glBitmap(64, 64, 0.0, 0.0, 64.0, 64.0, check);

   glColor3f(0.0, 0.0, 1.0);
   glRasterPos3f(0.6, 0.0, 0.0);
   glBitmap(64, 64, 0.0, 0.0, 0.0, 0.0, check);

   // Draw font bitmap
   glColor3f(1.0, 1.0, 0.0);
   glRasterPos3f(-0.6, -0.2, 0.0);
   glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '1');
   glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '2');
   glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '3');
   glColor3f(0.0, 1.0, 1.0);
   glRasterPos3f(-0.6, -0.3, 0.0);
   display_integer(234);

   // Draw message
   glColor3f(1.0, 1.0, 1.0);
   glRasterPos3f(-0.8, -0.5, 0.0);
   display_message("Help Me");
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
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
   glutCreateWindow("Bitmap");
   glutDisplayFunc(display);
   init();
   glutMainLoop();
   return 0;
}
