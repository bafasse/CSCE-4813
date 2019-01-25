//---------------------------------------
// Program: terrain.cpp
// Purpose: To visualize terrain maps.
// Author:  John Gauch
// Date:    September 2014
//---------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "libim/im_color.h"

// Global variables 
#define ROTATE 1
#define TRANSLATE 2
#define SCALE 3
#define SIZE 1000
int xangle = 0;
int yangle = 0;
int zangle = 0;
int xpos = 0;
int ypos = 0;
int zpos = 0;
float scale = 1.0;
int mode = ROTATE;

// Terrain variables
int terrain_xdim = 0;
int terrain_ydim = 0;
float terrain_height[SIZE][SIZE];
float terrain_min = 0.0;
float terrain_max = 0.0;
float terrain_size = 0.0;
float terrain_scale = 0.0;
char txt_file[100] = "jakobshavn.txt";
char jpg_file[100] = "jakobshavn.jpg";

//---------------------------------------
// Initialize terrain data
//---------------------------------------
void init_terrain(char *name)
{
   // Open terrain elevations file
   FILE *fd = fopen(name, "r"); 
   if (feof(fd)) printf("Error:  Could not open terrain file\n");
   if (fscanf(fd, "%d %d", &terrain_xdim, &terrain_ydim) != 2)
      printf("Error: could not execute fscanf command\n");
   printf("terrain_xdim: %d, terrain_ydim: %d\n", terrain_xdim, terrain_ydim);
   terrain_size = (terrain_xdim + terrain_ydim) / 2.0;
   printf("terrain_size: %f\n", terrain_size);

   // Create output image
   im_float image(terrain_xdim, terrain_ydim);

   // Read terrain elevations
   for (int y = 0; y < terrain_ydim; y++)
   for (int x = 0; x < terrain_xdim; x++)
   {
      if (fscanf(fd, "%f", &(terrain_height[y][x])) != 1)
         printf("Error: could not execute fscanf command\n");
      image.Data2D[y][x] = terrain_height[y][x]; 
      if (terrain_min > terrain_height[y][x])
         terrain_min = terrain_height[y][x];
      if (terrain_max < terrain_height[y][x])
         terrain_max = terrain_height[y][x];
   }
   printf("terrain_min: %f, terrain_max: %f\n", terrain_min, terrain_max);
   terrain_scale = 1.0 / (terrain_max - terrain_min);
   printf("terrain_scale: %f\n", terrain_scale);
  
   // Close output image
   image.Window(-1300, 1300);
   image.Greymap(0, 255);
   image.WriteJpg((char *)"terrain.jpg");
}

//---------------------------------------
// Initialize texture image
//---------------------------------------
void init_texture(char *name, unsigned char *&texture, int &xdim, int &ydim)
{
   // Read jpg image
   im_color image;
   image.ReadJpg(name);
   printf("Reading image %s\n", name);
   xdim = 1; while (xdim < image.R.Xdim) xdim*=2; xdim /=2;
   ydim = 1; while (ydim < image.R.Ydim) ydim*=2; ydim /=2;
   image.Interpolate(xdim, ydim);
   printf("Interpolating to %d by %d\n", xdim, ydim);

   // Copy image into texture array
   texture = (unsigned char *)malloc((unsigned int)(xdim*ydim*3));
   int index = 0;
   for (int y = 0; y < ydim; y++)
      for (int x = 0; x < xdim; x++)
      {
         texture[index++] = (unsigned char)(image.R.Data2D[y][x]);
         texture[index++] = (unsigned char)(image.G.Data2D[y][x]);
         texture[index++] = (unsigned char)(image.B.Data2D[y][x]);
      }
}

//---------------------------------------
// Function to draw 3D terrain JOHN
// fix last row of terrain
//---------------------------------------
void terrain(float xmin, float ymin, float zmin,
             float xmax, float ymax, float zmax)
{
   // Draw grid of terrain polygons
   float texture_ystep = 1.0 / (terrain_ydim-1);
   float texture_xstep = 1.0 / (terrain_xdim-1);

   for (int y = 0; y < terrain_ydim-1; y++)
   for (int x = 0; x < terrain_xdim-1; x++)
   if ((terrain_height[y][x] > terrain_min) && 
       (terrain_height[y][x+1] > terrain_min) && 
       (terrain_height[y+1][x+1] > terrain_min) && 
       (terrain_height[y+1][x] > terrain_min))
   {
      float y_step = (ymax - ymin) / (terrain_ydim - 1);
      float x_step = (xmax - xmin) / (terrain_xdim - 1);
      float y_coord = y * y_step + ymin;
      float x_coord = x * x_step + xmin;

      glBegin(GL_POLYGON);  
      glTexCoord2f(x*texture_xstep, y*texture_ystep);
      glVertex3f(x_coord, y_coord, terrain_height[y][x]*terrain_scale);
      glTexCoord2f((x+1)*texture_xstep, y*texture_ystep);
      glVertex3f(x_coord+x_step, y_coord, terrain_height[y][x+1]*terrain_scale);
      glTexCoord2f((x+1)*texture_xstep, (y+1)*texture_ystep);
      glVertex3f(x_coord+x_step, y_coord+y_step, terrain_height[y+1][x+1]*terrain_scale);
      glTexCoord2f(x*texture_xstep, (y+1)*texture_ystep);
      glVertex3f(x_coord, y_coord+y_step, terrain_height[y+1][x]*terrain_scale);
      glEnd();
   }
}

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
   // Init view
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-2.0, 2.0, -2.0, 2.0, -12.0, 12.0);
   glEnable(GL_DEPTH_TEST);

   // Init terrain
   init_terrain(txt_file);

   // Init texture
   int xdim, ydim;
   unsigned char *texture;
   init_texture(jpg_file, texture, xdim, ydim);
   glEnable(GL_TEXTURE_2D);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
   // Incrementally rotate objects
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(1.0 * xpos / SIZE, 1.0 * ypos / SIZE, 1.0 * zpos / SIZE);
   glRotatef(xangle, 1.0, 0.0, 0.0);
   glRotatef(yangle, 0.0, 1.0, 0.0);
   glRotatef(zangle, 0.0, 0.0, 1.0);

   // Draw objects
   terrain(-scale*terrain_xdim/terrain_size, -scale*terrain_ydim/terrain_size, -1, 
            scale*terrain_xdim/terrain_size,  scale*terrain_ydim/terrain_size, 1);
   glFlush();
}

//---------------------------------------
// Keyboard callback for OpenGL
//---------------------------------------
void keyboard(unsigned char key, int x, int y)
{
   // Determine if we are in ROTATE, TRANSLATE or SCALE mode
   if ((key == 'r') || (key == 'R'))
   {
      printf("Type x y z to decrease or X Y Z to increase ROTATION angles.\n");
      mode = ROTATE;
   }
   if ((key == 't') || (key == 'T'))
   {
      printf("Type x y z to decrease or X Y Z to increase TRANSLATION distance.\n");
      mode = TRANSLATE;
   }
   if ((key == 's') || (key == 'S'))
   {
      printf("Type - to decrease SCALE or + to increase SCALE.\n");
      mode = SCALE;
   }

   // Handle ROTATE
   if (mode == ROTATE)
   {
      if (key == 'x')
	 xangle -= 5;
      else if (key == 'y')
	 yangle -= 5;
      else if (key == 'z')
	 zangle -= 5;
      else if (key == 'X')
	 xangle += 5;
      else if (key == 'Y')
	 yangle += 5;
      else if (key == 'Z')
	 zangle += 5;
      glutPostRedisplay();
   }

   // Handle TRANSLATE
   if (mode == TRANSLATE)
   {
      if (key == 'x')
	 xpos -= 5;
      else if (key == 'y')
	 ypos -= 5;
      else if (key == 'z')
	 zpos -= 5;
      else if (key == 'X')
	 xpos += 5;
      else if (key == 'Y')
	 ypos += 5;
      else if (key == 'Z')
	 zpos += 5;
      glutPostRedisplay();
   }

   // Handle SCALE
   if (mode == SCALE)
   {
      if (key == '-')
	 scale *= 0.9;
      else if (key == '+')
	 scale *= 1.1;
      // printf("scale: %f\n", scale);
      glutPostRedisplay();
   }
}

//---------------------------------------
// Mouse callback for OpenGL
//---------------------------------------
void mouse(int button, int state, int x, int y)
{
   // Handle mouse down
   static int xdown, ydown;
   if (state == GLUT_DOWN)
   {
      xdown = x;
      ydown = y;
   }

   // Handle ROTATE
   if ((mode == ROTATE) && (state == GLUT_UP))
   {
      xangle += (y - ydown);
      yangle -= (x - xdown);
      zangle = 0;
      glutPostRedisplay();
   }

   // Handle TRANSLATE
   if ((mode == TRANSLATE) && (state == GLUT_UP))
   {
      xpos += (x - xdown);
      ypos -= (y - ydown);
      glutPostRedisplay();
   }
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
   // Handle command args
   if (argc == 3)
   {
      strcpy(txt_file, argv[1]);
      strcpy(jpg_file, argv[2]);
   }
   else
   {
      printf("Enter name of txt file: ");
      if (scanf("%s", txt_file) != 1)
         printf("Error: could not execute fscanf command\n");
      printf("Enter name of jpg file: ");
      if (scanf("%s", jpg_file) != 1)
         printf("Error: could not execute fscanf command\n");
   }

   // Create OpenGL window
   glutInit(&argc, argv);
   glutInitWindowSize(SIZE, SIZE);
   glutInitWindowPosition(SIZE/2, SIZE/2);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
   glutCreateWindow("Texture");
   init();
   printf("Type r to enter ROTATE mode or t to enter TRANSLATE mode.\n");

   // Specify callback function
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   glutMouseFunc(mouse);
   glutMainLoop();
   return 0;
}
