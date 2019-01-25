//---------------------------------------
// Program: draw.cpp
// Purpose: To demonstrate line drawing algorithms
// Author:  John Gauch
// Date:    March 2010
//---------------------------------------
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

// Define global variables
#define SIZE 1000
int Image[SIZE][SIZE];

//------------------------------------------------------------
// Draw line in 2D image using simple DDA algorithm
//------------------------------------------------------------
void draw_line1(int x1, int y1, int x2, int y2, int value)
{
   // Calculate step size
   int adx = abs(x2 - x1);
   int ady = abs(y2 - y1);
   int length = (adx > ady) ? adx : ady;
   double dx = (x2 - x1) / (double)length;
   double dy = (y2 - y1) / (double)length;

   // Draw pixels on line
   double x = x1 + 0.5;
   double y = y1 + 0.5;
   int i;
   for (i = 0; i <= length; i++)
   {
      Image[(int)y][(int)x] = value;
      x += dx;
      y += dy;
   }
}

//------------------------------------------------------------
// Draw line in 2D image using fast DDA algorithm
//------------------------------------------------------------
void draw_line2(int x1, int y1, int x2, int y2, int value)
{
   // Calculate step size
   int dx = x2 - x1;
   int dy = y2 - y1;
   int adx = abs(dx);
   int ady = abs(dy);
   int x, y;

   // Handle slope (0..1)
   if (ady < adx)
   {
      double step = (double)dy / (double)dx;
      double y = y1 + 0.5;
  
      if (dx > 0)
         for (x=x1; x<=x2; x++, y += step)
            Image[(int)y][x] = value;
      else
         for (x=x1; x>=x2; x--, y -= step)
            Image[(int)y][x] = value;
   }

   // Handle slope [1..inf)
   else 
   {
      double step = (double)dx / (double)dy;
      double x = x1 + 0.5;

      if (dy > 0)
         for (y=y1; y<=y2; y++, x += step)
            Image[y][(int)x] = value;
      else
         for (y=y1; y>=y2; y--, x -= step)
            Image[y][(int)x] = value;
   }
}

//------------------------------------------------------------
// Draw line in 2D image using Bresenham's algorithm
//------------------------------------------------------------
void draw_line3(int x1, int y1, int x2, int y2, int value)
{
   // Calculate step size
   int dx = x2 - x1;
   int dy = y2 - y1;
   int adx = abs(dx);
   int ady = abs(dy);
   int x, y;

   // Handle slope (0..1)
   if (ady < adx)
   {
      // Draw line with dx > 0
      if (dx > 0)
      {
         int error = dx/2;
         int step = (dy > 0) ? 1 : -1;
         for (x=x1, y=y1; x<=x2; x++)
         {
            Image[y][x] = value;
            error -= ady;
            if (error < 0)
            {
               error += dx;
               y += step;
            }
         }
      }
      
      // Draw line with dx < 0
      else 
      {
         int error = -dx/2;
         int step = (dy > 0) ? 1 : -1;
         for (x=x1, y=y1; x>=x2; x--)
         {
            Image[y][x] = value;
            error -= ady;
            if (error < 0)
            {
               error -= dx;
               y += step;
            }
         }
      }
   }

   // Handle slope [1..inf)
   else 
   {
      // Draw line with dy > 0
      if (dy > 0)
      {
         int error = dy/2;
         int step = (dx > 0) ? 1 : -1;
         for (x=x1, y=y1; y<=y2; y++)
         {
            Image[y][x] = value;
            error -= adx;
            if (error < 0)
            {
               error += dy;
               x += step;
            }
         }
      }

      // Draw line with dy < 0
      if (dy < 0)
      {
         int error = -dy/2;
         int step = (dx > 0) ? 1 : -1;
         for (x=x1, y=y1; y>=y2; y--)
         {
            Image[y][x] = value;
            error -= adx;
            if (error < 0)
            {
               error -= dy;
               x += step;
            }
         }
      }
   }
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
   // Test line drawing function
   Timer t;
   t.start_timer();
   for (int j = 0; j < SIZE; j++)
   for (int i = 0; i < SIZE; i++)
   {
      int x1 = rand() % SIZE;
      int y1 = rand() % SIZE;
      int x2 = rand() % SIZE;
      int y2 = rand() % SIZE;
      draw_line1(x1, y1, x2, y2, i);
   }
   t.end_timer();
   printf("draw_line1 run time: %f sec\n", t.elapsed_cpu());
   
   // Test line drawing function
   t.start_timer();
   for (int j = 0; j < SIZE; j++)
   for (int i = 0; i < SIZE; i++)
   {
      int x1 = rand() % SIZE;
      int y1 = rand() % SIZE;
      int x2 = rand() % SIZE;
      int y2 = rand() % SIZE;
      draw_line2(x1, y1, x2, y2, i);
   }
   t.end_timer();
   printf("draw_line2 run time: %f sec\n", t.elapsed_cpu());
   
   // Test line drawing function
   t.start_timer();
   for (int j = 0; j < SIZE; j++)
   for (int i = 0; i < SIZE; i++)
   {
      int x1 = rand() % SIZE;
      int y1 = rand() % SIZE;
      int x2 = rand() % SIZE;
      int y2 = rand() % SIZE;
      draw_line3(x1, y1, x2, y2, i);
   }
   t.end_timer();
   printf("draw_line3 run time: %f sec\n", t.elapsed_cpu());
   return 0;
}
