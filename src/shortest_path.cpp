//---------------------------------------
// Program: shortest_path.cpp
// Purpose: To calculate and display the
//          shortest path between points.
// Author:  John Gauch
// Date:    April 2014
//---------------------------------------
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "graph3.h"
using namespace std;

// Global variables
#define SCREEN_MIN 0
#define SCREEN_MAX 499
#define SCREEN_SIZE 500
#define WORLD_MIN -1.0
#define WORLD_MAX 1.0
#define WORLD_SIZE 2.0
int x_start = 0;
int y_start = 0;
int x_end = 0;
int y_end = 0;

// Map variables
#define MAP_SIZE 100
int map_rows = 0;
int map_cols = 0;
char map_value[MAP_SIZE][MAP_SIZE];
Graph graph;
string path = "";
int path_length = 0;

//---------------------------------------
// Convert from screen to world coords
//---------------------------------------
void screen_to_world(int sx, int sy, float &wx, float &wy)
{
   sy = SCREEN_SIZE - 1 - sy;
   wx = float(WORLD_SIZE * sx) / SCREEN_SIZE + WORLD_MIN;
   wy = float(WORLD_SIZE * sy) / SCREEN_SIZE + WORLD_MIN;
}

//---------------------------------------
// Convert from world to screen coords
//---------------------------------------
void world_to_screen(float wx, float wy, int &sx, int &sy)
{
   sx = round((wx - WORLD_MIN) * SCREEN_SIZE / WORLD_SIZE);
   sy = round((wy - WORLD_MIN) * SCREEN_SIZE / WORLD_SIZE);
   sy = SCREEN_SIZE - 1 - sy; 
}

//---------------------------------------
// Convert from map to world coords
//---------------------------------------
void map_to_world(int mx, int my, float &wx, float &wy)
{
   my = map_rows - 1 - my; 
   wx = float(WORLD_SIZE * mx) / map_cols + WORLD_MIN;
   wy = float(WORLD_SIZE * my) / map_rows + WORLD_MIN;
}

//---------------------------------------
// Convert from world to map coords
//---------------------------------------
void world_to_map(float wx, float wy, int &mx, int &my)
{
   mx = round((wx - WORLD_MIN) * map_cols / WORLD_SIZE);
   my = round((wy - WORLD_MIN) * map_rows / WORLD_SIZE);
   my = map_rows - 1 - my; 
}

//---------------------------------------
// Convert from screen to map coords
//---------------------------------------
void screen_to_map(int sx, int sy, int &mx, int &my)
{
   mx = (sx * map_cols) / SCREEN_SIZE;
   my = (sy * map_rows) / SCREEN_SIZE;
}

//---------------------------------------
// Convert from map to world coords
//---------------------------------------
void map_to_screen(int mx, int my, int &sx, int &sy)
{
   sx = (mx * SCREEN_SIZE) / map_cols;
   sy = (my * SCREEN_SIZE) / map_rows;
}

//---------------------------------------
// Read map file
//---------------------------------------
void read_map(string filename)
{
   // Read map file
   ifstream din;
   din.open(filename.c_str());
   din >> map_rows >> map_cols;
   for (int r=0; r<map_rows; r++)
   for (int c=0; c<map_cols; c++)
      din >> map_value[r][c];
   din.close();

   // Initialize map graph
   for (int r=0; r<map_rows; r++)
   for (int c=0; c<map_cols; c++)
   if (map_value[r][c] == 'O')
   {
      // Add N S E W edges
      int current = r * map_cols + c; 
      if ((r-1 >= 0) && (map_value[r-1][c] == 'O'))
         graph.SetWeight(current, current-map_cols, 10);
      if ((r+1 < map_rows) && (map_value[r+1][c] == 'O'))
         graph.SetWeight(current, current+map_cols, 10);
      if ((c+1 < map_cols) && (map_value[r][c+1] == 'O'))
         graph.SetWeight(current, current+1, 10);
      if ((c-1 >= 0) && (map_value[r][c-1] == 'O'))
         graph.SetWeight(current, current-1, 10);

      // Add NE SE NW SW edges
      if ((r-1 >= 0) && (c+1 < map_cols) && (map_value[r-1][c+1] == 'O'))
         graph.SetWeight(current, current-map_cols+1, 15);
      if ((r+1 < map_rows) && (c+1 < map_cols) && (map_value[r+1][c+1] == 'O'))
         graph.SetWeight(current, current+map_cols+1, 15);
      if ((r-1 >= 0) && (c-1 >= 0) && (map_value[r-1][c-1] == 'O'))
         graph.SetWeight(current, current-map_cols-1, 15);
      if ((r+1 < map_rows) && (c-1 >= 0) && (map_value[r+1][c-1] == 'O'))
         graph.SetWeight(current, current+map_cols-1, 15);
   }
}

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(WORLD_MIN, WORLD_MAX, WORLD_MIN, WORLD_MAX, WORLD_MIN, WORLD_MAX);
}

//---------------------------------------
// Draw solid color circle
//---------------------------------------
void draw_circle(float cx, float cy, float radius)
{
   // Generate vertices on circle
   glBegin(GL_POLYGON);
   for (int angle = 0; angle < 360; angle++)
   {
      // Specify vertex
      float radians = M_PI * angle / 180.0;
      float x = cx + radius * cos(radians);
      float y = cy + radius * sin(radians);
      glVertex2f(x, y);
   }
   glEnd();
}

//---------------------------------------
// Mouse callback for OpenGL
//---------------------------------------
void mouse(int button, int state, int x, int y)
{
   // Handle mouse down
   if (state == GLUT_DOWN)
   {
      path = "";
      path_length = 0;
      x_start = x_end = x;
      y_start = y_end = y;
   }
   glutPostRedisplay();
}

//---------------------------------------
// Motion callback for OpenGL
//---------------------------------------
void motion(int x, int y)
{
   x_end = x;
   y_end = y;

   // Find shortest path
   int mx_start, my_start, node_start;
   int mx_end, my_end, node_end;
   screen_to_map(x_start, y_start, mx_start, my_start);
   screen_to_map(x_end, y_end, mx_end, my_end);
   node_start = my_start * map_cols + mx_start; 
   node_end = my_end * map_cols + mx_end; 
   graph.FindPath(node_start, node_end, path, path_length);
   glutPostRedisplay();
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
   // Draw background
   glClear(GL_COLOR_BUFFER_BIT);

   // Draw map information
   float x, y;
   float dx = WORLD_SIZE / map_cols;
   float dy = WORLD_SIZE / map_rows;
   for (int r=0; r<map_rows; r++)
   for (int c=0; c<map_cols; c++)
   {
      // Calculate world coordinates of map point
      map_to_world(c, r, x, y);
      if (map_value[r][c] == 'X')
         glColor3f(0.5, 0.0, 0.0);
      if (map_value[r][c] == 'O')
         glColor3f(0.0, 0.5, 0.0);

      // Draw map polygon
      glBegin(GL_POLYGON);
      glVertex2f(x, y);
      glVertex2f(x+dx, y);
      glVertex2f(x+dx, y+dy);
      glVertex2f(x, y+dy);
      glEnd();
   }

   // Draw path
   int node;
   stringstream sin;
   sin << path;
   while (sin >> node)
   {
      int mx = node % map_cols;
      int my = node / map_cols;
      map_to_world(mx, my, x, y);
      glColor3f(0.0, 0.0, 0.5);
      draw_circle(x+dx/2, y+dy/2, dx/2);
   }

   // Draw start circle
   screen_to_world(x_start, y_start, x, y);
   glColor3f(0.0, 0.0, 0.0);
   draw_circle(x, y, dx/2);
   
   // Draw end circle
   screen_to_world(x_end, y_end, x, y);
   glColor3f(1.0, 1.0, 1.0);
   draw_circle(x, y, dx/2);
   glFlush();
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   glutInitWindowSize(SCREEN_SIZE, SCREEN_SIZE);
   glutInitWindowPosition(SCREEN_SIZE/2, SCREEN_SIZE/2);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
   glutCreateWindow("Shortest Path");
   glutMouseFunc(mouse);
   glutMotionFunc(motion);
   glutDisplayFunc(display);
   read_map("map2.txt");
   init();
   glutMainLoop();
   return 0;
}

