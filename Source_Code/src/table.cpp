//---------------------------------------
// Program: table.cpp
// Purpose: To display a table
// Author:  John Gauch
// Date:    January 2010
//---------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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
   printf("polygon\n");
   printf("%4.1f %4.1f %4.1f\n", ax, ay, az);
   printf("%4.1f %4.1f %4.1f\n", bx, by, bz);
   printf("%4.1f %4.1f %4.1f\n", cx, cy, cz);
   printf("%4.1f %4.1f %4.1f\n", dx, dy, dz);
   printf("end\n");

   printf("polygon\n");
   printf("%4.1f %4.1f %4.1f\n", ax, ay, az);
   printf("%4.1f %4.1f %4.1f\n", dx, dy, dz);
   printf("%4.1f %4.1f %4.1f\n", hx, hy, hz);
   printf("%4.1f %4.1f %4.1f\n", ex, ey, ez);
   printf("end\n");

   printf("polygon\n");
   printf("%4.1f %4.1f %4.1f\n", ax, ay, az);
   printf("%4.1f %4.1f %4.1f\n", ex, ey, ez);
   printf("%4.1f %4.1f %4.1f\n", fx, fy, fz);
   printf("%4.1f %4.1f %4.1f\n", bx, by, bz);
   printf("end\n");

   printf("polygon\n");
   printf("%4.1f %4.1f %4.1f\n", gx, gy, gz);
   printf("%4.1f %4.1f %4.1f\n", fx, fy, fz);
   printf("%4.1f %4.1f %4.1f\n", ex, ey, ez);
   printf("%4.1f %4.1f %4.1f\n", hx, hy, hz);
   printf("end\n");

   printf("polygon\n");
   printf("%4.1f %4.1f %4.1f\n", gx, gy, gz);
   printf("%4.1f %4.1f %4.1f\n", cx, cy, cz);
   printf("%4.1f %4.1f %4.1f\n", bx, by, bz);
   printf("%4.1f %4.1f %4.1f\n", fx, fy, fz);
   printf("end\n");

   printf("polygon\n");
   printf("%4.1f %4.1f %4.1f\n", gx, gy, gz);
   printf("%4.1f %4.1f %4.1f\n", hx, hy, hz);
   printf("%4.1f %4.1f %4.1f\n", dx, dy, dz);
   printf("%4.1f %4.1f %4.1f\n", cx, cy, cz);
   printf("end\n");
}

//---------------------------------------
// Function to draw 3D table
//---------------------------------------
void table(float xpos, float ypos, float zpos,
	   float xsize, float ysize, float zsize)
{
   // Define six corners of table
   float xmin = xpos - xsize / 2;
   float xmax = xpos + xsize / 2;
   float ymin = ypos - ysize / 2;
   float ymax = ypos + ysize / 2;
   float zmin = zpos - zsize / 2;
   float zmax = zpos + zsize / 2;
   float leg = (xsize + ysize) / 20;

   // Draw top
   block(xmin, ymax - leg, zmin, xmax, ymax, zmax);

   // Draw legs
   block(xmin, ymin, zmin, xmin + leg, ymax - leg, zmin + leg);
   block(xmin, ymin, zmax - leg, xmin + leg, ymax - leg, zmax);
   block(xmax - leg, ymin, zmin, xmax, ymax - leg, zmin + leg);
   block(xmax - leg, ymin, zmax - leg, xmax, ymax - leg, zmax);
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
   float xpos = 0, ypos = 0, zpos = 0;
   float xsize = 1, ysize = 1, zsize = 1;
   if (argc == 7)
   {
      xpos = atof(argv[1]);
      ypos = atof(argv[2]);
      zpos = atof(argv[3]);
      xsize = atof(argv[4]);
      ysize = atof(argv[5]);
      zsize = atof(argv[6]);
   }
   
   table(xpos, ypos, zpos, xsize, ysize, zsize);
   return 0;
}
