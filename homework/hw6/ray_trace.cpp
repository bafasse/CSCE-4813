//---------------------------------------
// Program: ray_trace.cpp
// Purpose: Demonstrate ray tracing.
// Author:  John Gauch
// Date:    Spring 2019
//---------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <array>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Include ray tracing and phong shading code
#include "ray_classes.h"

// Global variables
#define XDIM 800
#define YDIM 800
unsigned char image[YDIM][XDIM][3];
float position = 2;
int nspheres = 5;
string mode = "phong";


float myrand(float R)
{
   return (2 * R * rand()) / RAND_MAX - R;
}

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void ray_trace()
{
   // Define Phong shader
   Phong shader;

   // Define camera point
   Point3D camera;
   camera.set(0,0,-position);
   shader.SetCamera(camera);

   // Define light source
   ColorRGB color;
   color.set(200,200,200);
   Vector3D dir;
   dir.set(-1,-1,-1);
   dir.normalize();
   shader.SetLight(color, dir);

   // Set object properties
   ColorRGB colors[nspheres];
   
   
   
   // Define test sphere
   Sphere3D sphere[nspheres];
   for (int i = 0; i < nspheres; i++)
   {
      Point3D center;
      float x_rand = myrand(1);
      float y_rand = myrand(1);
      float z_rand = 1 + rand() % 2;
      center.set(x_rand, y_rand, z_rand);
      float radius = 1 + rand() % 1;
      sphere[i].set(center, radius);
      colors[i].set(rand() % 256, rand() % 256, rand() % 256);
   }
   

   // Perform ray tracing
   for (int y = 0; y < YDIM; y++)
   {
      bool intersected = false;
      for (int x = 0; x < XDIM; x++)
      {
         // Clear image
         image[y][x][0] = 0;
         image[y][x][1] = 0;
         image[y][x][2] = 0;

         // Define sample point on image plane
         float xpos = (x - XDIM/2) * 2.0 / XDIM;
         float ypos = (y - YDIM/2) * 2.0 / YDIM;
         Point3D point;
         point.set(xpos, ypos, 0);
      
         // Define ray from camera through image
         Ray3D ray;
         ray.set(camera, point);

         // Perform sphere intersection
         Point3D p;
         Point3D intersect; //p2
         Point3D tempPoint;
         Vector3D n;
         Vector3D vector; //n2
         for(int i = 0; i < nspheres; i++) 
         {
            if(sphere[i].get_intersection(ray, p, n))
            {
               // Display surface normal
               if (mode == "normal")
               {
                  image[y][x][0] = 127 + n.vx * 127;
                  image[y][x][1] = 127 + n.vy * 127;
                  image[y][x][2] = 127 + n.vz * 127;
               }

               // Calculate Phong shade
               if (mode == "phong")
               {
                  shader.SetObject(colors[i], 0.3, 0.4, 0.4, 10);
                  for (int j = 0; j < nspheres; j++)
                  {
                     Ray3D ray2;
                     ray2.set(p, dir);
                     // check if point p coming off front sphere intersects with other sphere
                     if(i != j && sphere[j].get_intersection(ray2, intersect, vector))
                     {
                        shader.SetObject(colors[i], 0.3, 0.0, 0.0, 10);
                     }
                  }
                  
                  shader.GetShade(p, n, color);
                  image[y][x][0] = color.R;
                  image[y][x][1] = color.G;
                  image[y][x][2] = color.B;
               }
            }
         }
      }
   }
}
 
//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
   // Initialize OpenGL
   glClearColor(0.0, 0.0, 0.0, 1.0);

   // Print command menu
   cout << "Program commands:\n"
        << "   '+' - increase camera distance\n"
        << "   '-' - decrease camera distance\n"
        << "   'p' - show Phong shading\n"
        << "   'n' - show surface normals\n"
        << "   'q' - quit program\n";

   // Perform ray tracing

   // for (int i = 0; i < num_sphere; ++i) 
   //    ray_trace();
   ray_trace();
   // ray_trace();
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
   // Display image
   glClear(GL_COLOR_BUFFER_BIT);
   glDrawPixels(XDIM, YDIM, GL_RGB, GL_UNSIGNED_BYTE, image);
   glFlush();
}

//---------------------------------------
// Keyboard callback for OpenGL
//---------------------------------------
void keyboard(unsigned char key, int x, int y)
{
   // End program
   if (key == 'q')
      exit(0);

   // Move camera position
   else if (key == '+' && position < 5)
      position = position * 1.1;
   else if (key == '-' && position > 1)
      position = position / 1.1;

   // Change display mode
   else if (key == 'n')
      mode = "normal";
   else if (key == 'p')
      mode = "phong";

   // Perform ray tracing
   ray_trace();
   glutPostRedisplay();
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
   // Create OpenGL window
   glutInit(&argc, argv);
   glutInitWindowSize(XDIM, YDIM);
   glutInitWindowPosition(0, 0);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
   glutCreateWindow("Ray Trace");
   init();

   // Specify callback function
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
