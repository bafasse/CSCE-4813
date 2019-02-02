//============================================================
//  File:       ray_trace.cpp
//  Purpose:    Uses ray tracing to generate image of scene.
//  Author:     John Gauch
//  Date:       Spring 2013
//============================================================
#include "Camera.h"
#include "Scene.h"
#include "Shape.h"

#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Global variables
int Xdim = 0;
int Ydim = 0;
string infile = "";

//============================================================
bool phong(Point3 light, Point3 surface, Vector3 normal, Vector3 viewer, double shine,
   double & distance, double & diffuse, double & specular, Vector3 & reflect)
{
   // Calculate diffuse term
   Vector3 vlight = light - surface;
   distance = vlight.length();
   vlight.normalize();
   diffuse = vlight * normal; 
   if (diffuse < 0) 
   {
      diffuse = 0;
      specular = 0;
      return false;
   }

   // Calculate specular term
   reflect = 2 * diffuse * normal - vlight;
   reflect.normalize();
   specular = viewer * reflect;  
   if (specular < 0) 
      specular = 0;
   else if (shine > 1)
      specular = pow(specular, shine);

   // Calculate reflected ray
   reflect = 2 * (viewer * normal) * normal - viewer;
   return true;
}

//============================================================
void ray_trace(string filename, int Xdim, int Ydim)
{
   // Read scene file
   Scene scene;
   scene.readScene(filename);

   // Define Camara to/from World transformations 
   Camera c = scene.camera;
   Matrix4 C2W = c.calculate_C2W();
   Matrix4 W2C = c.calculate_W2C();

   // Trace rays to create output image
   unsigned char image[Ydim][Xdim][3];
   for (int sy=0; sy<Ydim; sy++)
   for (int sx=0; sx<Xdim; sx++)
   {
      // Calculate pixel location in Camera and World coordinates
      image[sy][sx][0] = image[sy][sx][1] = image[sy][sx][2] = 0;
      Point3 camera_pixel(2*(sx+0.5)/Xdim-1, 2*(sy+0.5)/Ydim-1, -1);
      Point3 world_pixel = C2W * camera_pixel;
     
      // Define ray from eye to screen pixel
      Point3 ray_pt = c.get_eye();
      Vector3 ray_dir = world_pixel - ray_pt;
      ray_dir.normalize();

      // Intersect ray with all objects
      Point3 hit_pt;
      Vector3 hit_normal;
      Object hit_obj;
      if (scene.intersectObjects(ray_pt, ray_dir, 
         hit_pt, hit_normal, hit_obj))
      {
         // Initialize pixel color
         Vector3 ambient_color = hit_obj.get_ambient();
         Vector3 diffuse_color = hit_obj.get_diffuse();
         Vector3 specular_color = hit_obj.get_specular();
         double shine = hit_obj.get_shine();
         Vector3 color(0,0,0);

         // Loop over all lights
         for (unsigned int i=0; i<scene.vlight.size(); i++)
         {
            Light light = scene.vlight[i];
            Point3 light_pos = light.get_position();
            Vector3 light_color = light.get_color();
            Vector3 function = light.get_function();
            double distance = 0;
            double diffuse = 0;
            double specular = 0;
            Vector3 reflect(0,0,0);
   
            // Perform Phong shading
            if (phong(light_pos, hit_pt, hit_normal, -ray_dir, shine, 
               distance, diffuse, specular, reflect))
            {
               double attenuation = 1/(function[0] + 
                                       function[1] * distance + 
                                       function[2] * distance * distance);
               diffuse *= attenuation;
               specular *= attenuation;
               for (int c=0; c<3; c++)
                  color[c] += (light_color[c]
                           * (diffuse_color[c] * diffuse 
                           + specular_color[c] * specular));
            }
         }

         // Save pixel color in image
         for (int c=0; c<3; c++)
         {
            if (color[c] > 1) color[c] = 1;
            image[sy][sx][c] = (int)(255 * color[c]);
         }
      }
   }

   // Draw pixels on screen
   glClear(GL_COLOR_BUFFER_BIT);
   glDrawPixels(Xdim, Ydim, GL_RGB, GL_UNSIGNED_BYTE, image);
   glFlush();
}

//============================================================
void display()
{
   int deltaX = abs(Xdim - glutGet(GLUT_WINDOW_WIDTH));
   int deltaY = abs(Ydim - glutGet(GLUT_WINDOW_HEIGHT));
   if ((deltaX > 10) || (deltaY > 10))
   {
      Xdim = glutGet(GLUT_WINDOW_WIDTH);
      Ydim = glutGet(GLUT_WINDOW_HEIGHT);
      Xdim = Ydim = 500;
      ray_trace(infile, Xdim, Ydim);
   }
}

//============================================================
int main(int argc, char *argv[])
{
   // Create OpenGL window
   glutInit(&argc, argv);
   Xdim = glutGet(GLUT_SCREEN_WIDTH)/2;
   Ydim = glutGet(GLUT_SCREEN_HEIGHT)/2;
   Xdim = Ydim = 500;
   glutInitWindowSize(Xdim, Ydim);
   glutInitWindowPosition(Xdim/2, Ydim/2);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
   glutCreateWindow(argv[1]);
   infile = string(argv[1]);
   Xdim = Ydim = 0;

   // Specify callback function
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;
}
