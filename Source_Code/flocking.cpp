//---------------------------------------
// Program: flocking.cpp
// Purpose: To demonstrate flocking.
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
#include <cfloat>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "graph3.h"
using namespace std;

// Global variables
#define SLEEP_TIME 20
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

// Minion variables
#define MINION_COUNT 10
int minion_diameter = 20;
float minion_x[MINION_COUNT];
float minion_y[MINION_COUNT];

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
      // Save start position
      path = "";
      path_length = 0;
      x_start = x_end = x;
      y_start = y_end = y;

      // Initialize minions
      for (int m = 0; m < MINION_COUNT; m++)
      {
         minion_x[m] = x_start + random() % minion_diameter - minion_diameter/2;
         minion_y[m] = y_start + random() % minion_diameter - minion_diameter/2;
      }
   }
   glutPostRedisplay();
}

//---------------------------------------
// Motion callback for OpenGL
//---------------------------------------
void motion(int x, int y)
{
   // Save end position
   x_end = x;
   y_end = y;
   glutPostRedisplay();
}

//---------------------------------------
// Idle callback for OpenGL
//---------------------------------------
void timer(int value)
{
   // Apply forces to all minions
   float step = 1.0;
   for (int m = 0; m < MINION_COUNT; m++)
   {
      // Calculate start node
      int mx_start, my_start, node_start;
      screen_to_map(minion_x[m], minion_y[m], mx_start, my_start);
      node_start = my_start * map_cols + mx_start; 

      // Calculate end node
      int mx_end, my_end, node_end;
      screen_to_map(x_end, y_end, mx_end, my_end);
      node_end = my_end * map_cols + mx_end; 

      // Find shortest path for minion
      graph.FindPath(node_start, node_end, path, path_length);

      // Take step along shortest path
      int node1, node2;
      stringstream sin;
      sin << path;
      if (sin >> node1 >> node2)
      {
         // Get first node on path
         int sx1, sy1, mx1, my1;
         mx1 = node1 % map_cols;
         my1 = node1 / map_cols;
         map_to_screen(mx1, my1, sx1, sy1);

         // Get second node on path
         int sx2, sy2, mx2, my2;
         mx2 = node2 % map_cols;
         my2 = node2 / map_cols;
         map_to_screen(mx2, my2, sx2, sy2);

         // Apply motion
         float dx = sx2 - sx1;
         float dy = sy2 - sy1;
         float dist = sqrt(dx*dx + dy*dy);
         minion_x[m] += 2 * step * dx / dist; 
         minion_y[m] += 2 * step * dy / dist; 

         // Find location of closest minion
         float closest_dx = 0;
         float closest_dy = 0;
         float closest_dist = FLT_MAX;
         for (int i = 0; i < MINION_COUNT; i++)
         if (i != m)
         {
            // Calculate distance
            float dx = minion_x[m] - minion_x[i];
            float dy = minion_y[m] - minion_y[i];
            float dist = sqrt(dx*dx + dy*dy);
   
            // Save closest distance
            if (closest_dist > dist)
            {
               closest_dx = dx;
               closest_dy = dy;
               closest_dist = dist;
            }
         }

         // Move away from closest minion
         if (closest_dist < minion_diameter)
         {
            minion_x[m] += step * closest_dx / closest_dist; 
            minion_y[m] += step * closest_dy / closest_dist; 
         }
      }
   }
   glutTimerFunc(SLEEP_TIME, timer, 0);
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

   // Draw end circle
   screen_to_world(x_end, y_end, x, y);
   glColor3f(1.0, 1.0, 1.0);
   draw_circle(x, y, dx/2);

   // Draw all minion
   for (int m = 0; m < MINION_COUNT; m++)
   {
      screen_to_world(minion_x[m], minion_y[m], x, y);
      glColor3f(0.0, 1.0, 0.0);
      draw_circle(x, y, dx/3);
   } 
   glFlush();
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
   read_map("map.txt");
   glutInit(&argc, argv);
   glutInitWindowSize(SCREEN_SIZE, SCREEN_SIZE);
   glutInitWindowPosition(SCREEN_SIZE/2, SCREEN_SIZE/2);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
   glutCreateWindow("Flocking");
   glutMouseFunc(mouse);
   glutMotionFunc(motion);
   glutTimerFunc(SLEEP_TIME, timer, 0);
   glutDisplayFunc(display);
   init();
   glutMainLoop();
   return 0;
}

