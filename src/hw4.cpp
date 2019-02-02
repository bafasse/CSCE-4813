//---------------------------------------
// Program: hw4.cpp
// Purpose: Homework 4 solution.
// Author:  John Gauch
// Date:    March 2015
//---------------------------------------
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;

// Global variables
#define XDIM 500
#define YDIM 500
unsigned char image[YDIM][XDIM][3];

//---------------------------------------
// Simple class for Light information
//---------------------------------------
class Light
{
public:
   float R,G,B;
   float Lx,Ly,Lz;
   Light() { R=G=B=0; Lx=Ly=Lz=0; }
   ~Light() { }
   void read(ifstream &din) 
   { 
      din >> R >> G >> B;
      din >> Lx >> Ly >> Lz;
   }
   void write(ofstream &dout) 
   { 
      dout << R << " " << G << " " << B << " ";
      dout << Lx << " " << Ly << " " << Lz << endl;
   }
};

//---------------------------------------
// Simple class for Object information
//---------------------------------------
class Object
{
public:
   float R,G,B;
   float Ka,Kd,Ks,Kp;
   Object() { R=G=B=0; Ka=Kd=Ks=Kp=0; }
   ~Object() { }
   void read(ifstream &din) 
   { 
      din >> R >> G >> B;
      din >> Ka >> Kd >> Ks >> Kp;
   }
   void write(ofstream &dout) 
   { 
      dout << R << " " << G << " " << B << " ";
      dout << Ka << " " << Kd << " " << Ks << " " << Kp << endl;
   }
};

//---------------------------------------
// Simple class for Point information
//---------------------------------------
class Point
{
public:
   float Px,Py,Pz;
   float Nx,Ny,Nz;
   Point() { Px=Py=Pz=0; Nx=Ny=Nz=0; }
   ~Point() { }
   void read(ifstream &din) 
   { 
      din >> Px >> Py >> Pz;
      din >> Nx >> Ny >> Nz;
   }
   void write(ofstream &dout) 
   { 
      dout << Px << " " << Py << " " << Pz << " ";
      dout << Nx << " " << Ny << " " << Nz << endl;
   }
};

//---------------------------------------
// Simple class for Polygon information
//---------------------------------------
class Polygon
{
public:
   int object_id;
   int pt_count;
   Point *array;
   Polygon() { object_id=pt_count=0; array=NULL; }
   ~Polygon() { }
   void read(ifstream &din) 
   { 
      din >> object_id >> pt_count;
      array = new Point[pt_count];
      for (int index=0; index<pt_count; index++)
         array[index].read(din);
   }
   void write(ofstream &dout) 
   { 
      dout << object_id << " " << pt_count << endl;
      for (int index=0; index<pt_count; index++)
         array[index].write(dout);
   }
};

//---------------------------------------
// Class to store all Scene information
//---------------------------------------
class Scene
{
public:
   static const int MAX_LIGHT = 10;
   static const int MAX_OBJECT = 10;
   static const int MAX_POLYGON = 1000;
   Light light[MAX_LIGHT];
   Object object[MAX_OBJECT];
   Polygon polygon[MAX_POLYGON];
   int light_count;
   int object_count;
   int polygon_count;
   Scene() { light_count = object_count = polygon_count = 0; }
   ~Scene() { }
   void read(string filename);
   void write(string filename);
};

//---------------------------------------
// Read Scene information from input file
//---------------------------------------
void Scene::read(string filename)
{
   // Open file
   ifstream din;
   din.open(filename.c_str());

   // Read lights, objects and polygons
   if (!din.fail())
   {
      string token;
      din >> token;

      // Read lights
      while (!din.eof() && token == "Light")
      {
         int index;
         din >> index;
         if (index >= 0 && index < MAX_LIGHT)
         {
            light[index].read(din);
            if (index >= light_count) 
               light_count = index+1;
         }
         din >> token;
      }

      // Read objects
      while (!din.eof() && token == "Object")
      {
         int index;
         din >> index;
         if (index >= 0 && index < MAX_OBJECT)
         {
            object[index].read(din);
            if (index >= object_count) 
               object_count = index+1;
         }
         din >> token;
      }

      // Read polygons
      while (!din.eof() && token == "Polygon" && 
         polygon_count < MAX_POLYGON)
      {
         polygon[polygon_count].read(din);
         polygon_count++;
         din >> token;
      }

   // Close file
   din.close();
   }
}

//---------------------------------------
// Write Scene information to output file
//---------------------------------------
void Scene::write(string filename)
{
   // Open file
   ofstream dout;
   dout.open(filename.c_str());

   // Write lights, objects and polygons
   if (!dout.fail())
   {
      // Write lights
      for (int index=0; index<light_count; index++)
      {
         dout << "Light " << index << " ";
         light[index].write(dout);
      } 

      // Write objects
      for (int index=0; index<object_count; index++)
      {
         dout << "Object " << index << " ";
         object[index].write(dout);
      }
   
      // Write polygons
      for (int index=0; index<polygon_count; index++)
      {
         dout << "Polygon ";
         polygon[index].write(dout);
      }
   
      // Close file
      dout.close();
   }
}

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
   // Initialize OpenGL
   glClearColor(0.0, 0.0, 0.0, 1.0);
}

//---------------------------------------
// Calculate phong shading for a point
//---------------------------------------
void phong(Scene &scene, int poly, int pt,
   float &R, float &G, float &B)
{
   Point point = scene.polygon[poly].array[pt]; 
   Object object = scene.object[scene.polygon[poly].object_id];

   // Calculate ambient color value
   R = object.Ka * (object.R/255.0);
   G = object.Ka * (object.G/255.0);
   B = object.Ka * (object.B/255.0);

   // Loop over all light sources
   for (int index=0; index<scene.light_count; index++)
   {
      // Calculate NdotL value 
      Light light = scene.light[index];
      float NdotL = light.Lx * point.Nx 
                  + light.Ly * point.Ny 
                  + light.Lz * point.Nz;

      if (NdotL > 0)
      {
         // Calculate diffuse color value
         R += object.Kd * NdotL * (light.R/255.0) * (object.R/255.0);
         G += object.Kd * NdotL * (light.G/255.0) * (object.G/255.0);
         B += object.Kd * NdotL * (light.B/255.0) * (object.B/255.0);
   
         // Calculate R vector
         float Rx = 2 * NdotL * point.Nx - light.Lx;
         float Ry = 2 * NdotL * point.Ny - light.Ly;
         float Rz = 2 * NdotL * point.Nz - light.Lz;
   
         // Set default V vector
         float Vx = 0;
         float Vy = 0;
         float Vz = -1;

         // Calculate RdotV value 
         float RdotV = Rx*Vx + Ry*Vy + Rz*Vz;
   
         if (RdotV > 0)
         {
            // Calculate specular color value
            RdotV = pow(RdotV, object.Kp);
            R += object.Ks * RdotV * (light.R/255.0);
            G += object.Ks * RdotV * (light.G/255.0);
            B += object.Ks * RdotV * (light.B/255.0);
         }
      }
   }
}
   
//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
   // Clear image
   for (int y = 0; y < YDIM; y++)
      for (int x = 0; x < XDIM; x++)
	 image[y][x][0] = image[y][x][1] = image[y][x][2] = 0;

   // Read and write scene file
   Scene scene;
   scene.read("input.txt"); 
   scene.write("output.txt");

   // Display polygons
   for (int poly=0; poly<scene.polygon_count; poly++)
   {
      // Display points
      for (int pt=0; pt<scene.polygon[poly].pt_count; pt++)
      {
         // Calculate pixel color
         float R=0, G=0, B=0;
         phong(scene, poly, pt, R, G, B);

         // Store pixel color
         int x = scene.polygon[poly].array[pt].Px;
         int y = scene.polygon[poly].array[pt].Py;
	 image[y][x][0] = (unsigned char)(255 * R);
	 image[y][x][1] = (unsigned char)(255 * G);
	 image[y][x][2] = (unsigned char)(255 * B);
	 image[y+1][x][0] = (unsigned char)(255 * R);
	 image[y+1][x][1] = (unsigned char)(255 * G);
	 image[y+1][x][2] = (unsigned char)(255 * B);
	 image[y][x+1][0] = (unsigned char)(255 * R);
	 image[y][x+1][1] = (unsigned char)(255 * G);
	 image[y][x+1][2] = (unsigned char)(255 * B);
	 image[y+1][x+1][0] = (unsigned char)(255 * R);
	 image[y+1][x+1][1] = (unsigned char)(255 * G);
	 image[y+1][x+1][2] = (unsigned char)(255 * B);

         // Print pixel color
         cout << "point: " << x  << " " << y << " color: " 
              << (int)image[y][x][0] << " " 
              << (int)image[y][x][1] << " " 
              << (int)image[y][x][2] << endl;
      }
   }

   // Display image
   glClear(GL_COLOR_BUFFER_BIT);
   glDrawPixels(XDIM, YDIM, GL_RGB, GL_UNSIGNED_BYTE, image);
   glFlush();
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
   glutCreateWindow("Homework 4");
   init();

   // Specify callback function
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;
}
