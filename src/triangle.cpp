//---------------------------------------
// Program: triangle.cpp
// Purpose: To display triangles
// Author:  John Gauch
// Date:    Summer 2017
//---------------------------------------
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Global constants
#define MIN_X_VIEW -50
#define MAX_X_VIEW 50
#define MIN_Y_VIEW -50
#define MAX_Y_VIEW 50
#define MIN_Z_VIEW -50
#define MAX_Z_VIEW 50
#define MIN_X_SCREEN 0
#define MAX_X_SCREEN 500
#define MIN_Y_SCREEN 0
#define MAX_Y_SCREEN 500

// Array of points
const int POINT_COUNT = 1000;
float x[POINT_COUNT];
float y[POINT_COUNT];
float z[POINT_COUNT];
int point_count = 0;

// Array of triangles
const int TRIANGLE_COUNT = 1000;
int triangle[TRIANGLE_COUNT][3];
int triangle_count = 0;

// Array of colors
const int COLOR_COUNT = 12;
float color[COLOR_COUNT][3] = { 
   { 1.0, 0.0, 0.0 },
   { 0.0, 1.0, 0.0 },
   { 0.0, 0.0, 1.0 },
   { 0.0, 1.0, 1.0 },
   { 1.0, 0.0, 1.0 },
   { 1.0, 1.0, 0.0 },
   { 0.5, 0.0, 0.0 },
   { 0.0, 0.5, 0.0 },
   { 0.0, 0.0, 0.5 },
   { 0.0, 0.5, 0.5 },
   { 0.5, 0.0, 0.5 },
   { 0.5, 1.0, 0.0 } };

// Display mode
string mode = "";

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
// Read input files
//---------------------------------------
void read_files()
{
   // Open points.txt file
   ifstream din;
   din.open("points.txt");
   int index = 0;
   string junk = "";
   
   // Read 3D points
   if (mode.find('3') != string::npos)
      while ((index < POINT_COUNT) && 
         (din >> x[index] >> y[index] >> z[index]))
         index++;

   // Read 2D points
   else 
      while ((index < POINT_COUNT) && 
         (din >> x[index] >> y[index]))
         index++;

   // Close points.txt file
   point_count = index;
   din.close();

   // Find range of (x,y) coordinates
   float x_min = x[0];
   float x_max = x[0];
   float y_min = y[0];
   float y_max = y[0];
   for (int i=0; i<point_count; i++)
   {
      if (x_min > x[i]) x_min = x[i];
      if (x_max < x[i]) x_max = x[i];
      if (y_min > y[i]) y_min = y[i];
      if (y_max < y[i]) y_max = y[i];
   }

   // Center and scale (x,y) coordinates
   float border = 0.9;
   float x_mid = (x_max + x_min) / 2;
   float y_mid = (y_max + y_min) / 2;
   float x_scale = border * (MAX_X_VIEW - MIN_X_VIEW) / (x_max - x_min);
   float y_scale = border * (MAX_Y_VIEW - MIN_Y_VIEW) / (y_max - y_min);
   float scale = (x_scale < y_scale) ? x_scale : y_scale;
   for (int i=0; i<point_count; i++)
   {
      x[i] = (x[i] - x_mid) * scale;
      y[i] = (y[i] - y_mid) * scale;
   }

   // Read triangle.txt file
   din.open("triangles.txt");
   index = 0;
   while ((index < TRIANGLE_COUNT) && 
          (din >> triangle[index][0] 
               >> triangle[index][1] 
               >> triangle[index][2]))
      index++;
   triangle_count = index;
   din.close();

   // Print debug info
   cout << "point_count: " << point_count << endl;
   cout << "triangle_count: " << triangle_count << endl;
}

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(MIN_X_VIEW, MAX_X_VIEW, 
      MIN_Y_VIEW, MAX_Y_VIEW, 
      MIN_Z_VIEW, MAX_Z_VIEW);
   glEnable(GL_DEPTH_TEST);
}

//---------------------------------------
// Timer callback for OpenGL
//---------------------------------------
void timer(int value)
{
   // Read input files
   read_files();
   glutPostRedisplay();
   glutTimerFunc(100, timer, 0);
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
   // Clear screen
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glColor3f(1.0, 1.0, 1.0);

   // Display edges of triangles
   if (mode.find('e') != string::npos)
   {
      glLineWidth(2);
      for (int i=0; i<triangle_count; i++)
      {
         glBegin(GL_LINE_LOOP);
         glVertex2f(x[ triangle[i][0] ], y[ triangle[i][0] ]);
         glVertex2f(x[ triangle[i][1] ], y[ triangle[i][1] ]);
         glVertex2f(x[ triangle[i][2] ], y[ triangle[i][2] ]);
         glEnd();
      }
   }
   
   // Display points
   if (mode.find('p') != string::npos)
   {
      glPointSize(3);
      glBegin(GL_POINTS);
      for (int i=0; i<point_count; i++)
         glVertex2f(x[i], y[i]);
      glEnd();
   }

   // Display point numbers
   if (mode.find('n') != string::npos)
   {
      for (int i=0; i<point_count; i++)
      {
         glRasterPos3f(x[i]+1, y[i]+1, 0);
         if (mode.find('s') != string::npos)
            display_integer(i-3);
         else
            display_integer(i);
      }
   }

   // Display faces of triangles
   if (mode.find('f') != string::npos)
   {
      srandom(0);
      for (int i=0; i<triangle_count; i++)
      {
         int choice = random() % COLOR_COUNT;
         glColor3f(color[choice][0], color[choice][1], color[choice][2]);
         glBegin(GL_TRIANGLES);
         glVertex2f(x[ triangle[i][0] ], y[ triangle[i][0] ]);
         glVertex2f(x[ triangle[i][1] ], y[ triangle[i][1] ]);
         glVertex2f(x[ triangle[i][2] ], y[ triangle[i][2] ]);
         glEnd();
      }
   }

   glFlush();
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
   // Read program args
   if (argc > 1)
      mode = argv[1];

   // Start OpenGL code
   glutInit(&argc, argv);
   glutInitWindowSize(MAX_Y_SCREEN, MAX_X_SCREEN);
   glutInitWindowPosition(MAX_Y_SCREEN/2, MAX_X_SCREEN/2);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
   glutCreateWindow("Triangle");
   glutDisplayFunc(display);
   init();
   glutTimerFunc(100, timer, 0);
   glutMainLoop();
   return 0;
}
