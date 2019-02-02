//---------------------------------------
// Program: hw3.cpp
// Purpose: Homework 3 solution.
// Author:  John Gauch
// Date:    February 2015
//---------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Object class
const int SIZE = 20;
class Object 
{
public:
   // Surface points
   float Px[SIZE][SIZE];
   float Py[SIZE][SIZE];
   float Pz[SIZE][SIZE];

   // Normal vectors
   float Nx[SIZE][SIZE];
   float Ny[SIZE][SIZE];
   float Nz[SIZE][SIZE];

   // Display parameters
   float xpos, ypos, zpos;
   float xsize, ysize, zsize;
   float xangle, yangle, zangle;
};
Object object;
char mode = ' ';

const int MAX_SAVE = 10;
Object save_object[MAX_SAVE];
int save_count = 0;

//---------------------------------------
// Initialize empty object
//---------------------------------------
void init_object(Object &s)
{
   // Initialize transformation parameters
   s.xpos = s.ypos = s.zpos = 0;
   s.xsize = s.ysize = s.zsize = 1;
   s.xangle = s.yangle = s.zangle = 0;

   // Initialize points and normals
   for (int u = 0; u < SIZE; u++)
   for (int v = 0; v < SIZE; v++)
   {
         s.Px[u][v] = s.Nx[u][v] = 0;
         s.Py[u][v] = s.Ny[u][v] = 0;
         s.Pz[u][v] = s.Nz[u][v] = 0;
   }
}

//---------------------------------------
// Calculate surface normals
//---------------------------------------
void surface_normals(Object &s)
{
   // Find surface normals
   for (int u = 0; u < SIZE-1; u++)
   for (int v = 0; v < SIZE-1; v++)
   {
      // Get two tangent vectors
      float Ux = s.Px[u+1][v] - s.Px[u][v];
      float Uy = s.Py[u+1][v] - s.Py[u][v];
      float Uz = s.Pz[u+1][v] - s.Pz[u][v];
      float Vx = s.Px[u][v+1] - s.Px[u][v];
      float Vy = s.Py[u][v+1] - s.Py[u][v];
      float Vz = s.Pz[u][v+1] - s.Pz[u][v];
      
      // Do cross product
      s.Nx[u][v] = Uy * Vz - Uz * Vy;
      s.Ny[u][v] = Uz * Vx - Ux * Vz;
      s.Nz[u][v] = Ux * Vy - Uy * Vx;
      float length = sqrt( 
         s.Nx[u][v] * s.Nx[u][v] + 
         s.Ny[u][v] * s.Ny[u][v] + 
         s.Nz[u][v] * s.Nz[u][v]);
      if (length > 0)
      {
         s.Nx[u][v] /= length;
         s.Ny[u][v] /= length;
         s.Nz[u][v] /= length;
      }
   } 

   // Wrap around values for last row and col
   for (int u = 0; u < SIZE; u++)
   {
      s.Nx[u][SIZE-1] = s.Nx[u][0];
      s.Ny[u][SIZE-1] = s.Ny[u][0];
      s.Nz[u][SIZE-1] = s.Nz[u][0];
   }
   for (int v = 0; v < SIZE; v++)
   {
      s.Nx[SIZE-1][v] = s.Nx[0][v];
      s.Ny[SIZE-1][v] = s.Ny[0][v];
      s.Nz[SIZE-1][v] = s.Nz[0][v];
   }
}

//---------------------------------------
// Initialize sphere surface and normals
//---------------------------------------
void init_sphere(Object &s)
{
   // Initialize sphere surface and normals
   for (int u = 0; u < SIZE; u++)
   {
      float angle1 = 2 * u * M_PI / (SIZE - 1);
      for (int v = 0; v < SIZE; v++)
      {
         float angle2 = v * M_PI / (SIZE - 1);
         s.Px[u][v] = s.Nx[u][v] = - cos(angle1) * sin(angle2);
         s.Py[u][v] = s.Ny[u][v] = - sin(angle1) * sin(angle2);
         s.Pz[u][v] = s.Nz[u][v] = - cos(angle2);
      }
   }
}

//---------------------------------------
// Initialize cylinder surface and normals
//---------------------------------------
void init_cylinder(Object &s)
{
   // Initialize cylinder surface and normals
   for (int u = 0; u < SIZE; u++)
   {
      float angle1 = 2 * u * M_PI / (SIZE - 1);
      for (int v = 0; v < SIZE; v++)
      {
         s.Px[u][v] = cos(angle1);
         s.Py[u][v] = sin(angle1);
         s.Pz[u][v] = 2.0 * v / (SIZE - 1.0) - 1.0;

         s.Nx[u][v] = cos(angle1);
         s.Ny[u][v] = sin(angle1);
         s.Nz[u][v] = 0;
      }
   }
}

//---------------------------------------
// Initialize cone surface and normals
//---------------------------------------
void init_cone(Object &s)
{
   // Initialize cone surface and normals
   float root5 = sqrt(5.0);
   for (int u = 0; u < SIZE; u++)
   {
      float angle1 = 2 * u * M_PI / (SIZE - 1);
      for (int v = 0; v < SIZE; v++)
      {
         float radius = v / (SIZE - 1.0);
         s.Px[u][v] = cos(angle1) * radius;
         s.Py[u][v] = sin(angle1) * radius;
         s.Pz[u][v] = 2.0 * v / (SIZE - 1.0) - 1.0;

         s.Nx[u][v] = cos(angle1) * 2.0 / root5;
         s.Ny[u][v] = sin(angle1) * 2.0 / root5;
         s.Nz[u][v] = -1.0 / root5;
      }
   }
}

//---------------------------------------
// Initialize donut surface and normals
//---------------------------------------
void init_donut(Object &s)
{
   // Initialize donut surface and normals
   float radius1 = 0.25;
   float radius2 = 0.75;
   for (int u = 0; u < SIZE; u++)
   {
      float angle1 = 2 * u * M_PI / (SIZE - 1);
      for (int v = 0; v < SIZE; v++)
      {
         float angle2 = 2 * v * M_PI / (SIZE - 1);
         s.Px[u][v] = cos(angle1) * (radius2 + radius1*cos(angle2));
         s.Py[u][v] = sin(angle1) * (radius2 + radius1*cos(angle2));
         s.Pz[u][v] = radius1 * sin(angle2);
      }
   }
   surface_normals(s);
}

//---------------------------------------
// Initialize vase surface and normals
//---------------------------------------
void init_vase(Object &s)
{
   // Initialize vase surface and normals
   float radius1 = 0.25;
   float radius2 = 0.75;
   for (int u = 0; u < SIZE; u++)
   {
      float angle1 = 2 * u * M_PI / (SIZE - 1);
      for (int v = 0; v < SIZE; v++)
      {
         float angle2 = 2 * v * M_PI / (SIZE - 1);
         s.Px[u][v] = cos(angle1) * (radius2 + radius1*sin(angle2));
         s.Py[u][v] = sin(angle1) * (radius2 + radius1*sin(angle2));
         s.Pz[u][v] = 2.0 * v / (SIZE - 1.0) - 1.0;
      }
   }
   surface_normals(s);
}

//---------------------------------------
// Initialize Mobius strip surface
//---------------------------------------
void init_mobius(Object &s)
{
   // Initialize mobius surface 
   for (int u = 0; u < SIZE; u++)
   {
      float angle1 = 2 * u * M_PI / (SIZE - 1);
      for (int v = 0; v < SIZE; v++)
      {
         float width = v / (SIZE - 1.0) - 0.5;
         s.Px[u][v] = (1.0 + width * cos(angle1/2)) * cos(angle1);
         s.Py[u][v] = (1.0 + width * cos(angle1/2)) * sin(angle1);
         s.Pz[u][v] = width * sin(angle1/2);
      }
   }
   surface_normals(s);
}

//---------------------------------------
// Print surface coordinates and normals.
//---------------------------------------
void print_surface(Object &s)
{
   for (int u = 0; u < SIZE; u++)
      for (int v = 0; v < SIZE; v++)
         printf("%d %d %5.2f %5.2f %5.2f %5.2f %5.2f %5.2f\n", u, v, 
            s.Px[u][v], s.Py[u][v], s.Pz[u][v],
            s.Nx[u][v], s.Ny[u][v], s.Nz[u][v]);
}

//---------------------------------------
// Display geometric object
//---------------------------------------
void display_object(Object &object)
{
   // Perform geometric transformation
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(object.xpos, object.ypos, object.zpos);
   glRotatef(object.xangle, 1.0, 0.0, 0.0);
   glRotatef(object.yangle, 0.0, 1.0, 0.0);
   glRotatef(object.zangle, 0.0, 0.0, 1.0);
   glScalef(object.xsize, object.ysize, object.zsize);

   // Draw object model
   for (int u = 0; u < SIZE-1; u++)
      for (int v = 0; v < SIZE-1; v++)
      {
         glBegin(GL_LINE_LOOP);
         glVertex3f(object.Px[u][v], object.Py[u][v], object.Pz[u][v]);
         glVertex3f(object.Px[u + 1][v], object.Py[u + 1][v], object.Pz[u + 1][v]);
         glVertex3f(object.Px[u + 1][v + 1], object.Py[u + 1][v + 1], object.Pz[u + 1][v + 1]);
         glVertex3f(object.Px[u][v + 1], object.Py[u][v + 1], object.Pz[u][v + 1]);
         glEnd();
      }
}

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
   // Initialize OpenGL
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
   glEnable(GL_DEPTH_TEST);

   // Initialize objects
   init_object(object);
   for (int i=0; i<MAX_SAVE; i++)
      display_object(save_object[i]);
}

//---------------------------------------
// Keyboard callback for OpenGL
//---------------------------------------
void keyboard(unsigned char key, int x, int y)
{
   // Accept object
   if ((key == 'a') && (save_count < MAX_SAVE))
   {
      save_object[save_count] = object;
      init_object(object);
      printf("Object %d was accepted\n", save_count);
      save_count++;
   }

   // Delete object
   if (key == 'd') 
   {
      init_object(object);
      printf("Object was deleted\n");
   }

   // Select object
   if (key == 'S')
      init_sphere(object);
   if (key == 'C')
      init_cylinder(object);
   if (key == 'N')
      init_cone(object);
   if (key == 'D')
      init_donut(object);
   if (key == 'V')
      init_vase(object);
   if (key == 'M')
      init_mobius(object);
   
   // Change mode
   if (key == 's')
      mode = 's';
   if (key == 'r')
      mode = 'r';
   if (key == 't')
      mode = 't';

   // Update sizes in scale mode
   if (mode == 's')
   {
      if (key == 'x')
         object.xsize /= 1.1;
      if (key == 'X')
         object.xsize *= 1.1;
      if (key == 'y')
         object.ysize /= 1.1;
      if (key == 'Y')
         object.ysize *= 1.1;
      if (key == 'z')
         object.zsize /= 1.1;
      if (key == 'Z')
         object.zsize *= 1.1;
   }

   // Update angles in rotate mode
   if (mode == 'r')
   {
      if (key == 'x')
         object.xangle -= 5;
      if (key == 'X')
         object.xangle += 5;
      if (key == 'y')
         object.yangle -= 5;
      if (key == 'Y')
         object.yangle += 5;
      if (key == 'z')
         object.zangle -= 5;
      if (key == 'Z')
         object.zangle += 5;
   }

   // Update positions in translate mode
   if (mode == 't')
   {
      if (key == 'x')
         object.xpos -= 0.1;
      if (key == 'X')
         object.xpos += 0.1;
      if (key == 'y')
         object.ypos -= 0.1;
      if (key == 'Y')
         object.ypos += 0.1;
      if (key == 'z')
         object.zpos -= 0.1;
      if (key == 'Z')
         object.zpos += 0.1;
   }

   // Redraw objects
   glutPostRedisplay();
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
   // Draw geometric objects
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glColor3f(0.2, 0.8, 0.2);
   display_object(object);
   glColor3f(1.0, 1.0, 1.0);
   for (int i=0; i<save_count; i++)
      display_object(save_object[i]);
   glFlush();
}

//---------------------------------------
// Print command menu
//---------------------------------------
void print_menu()
{
   printf("\nObject controls:\n");
   printf("  'S' = create sphere\n");
   printf("  'C' = create cylinder\n");
   printf("  'N' = create cone\n");
   printf("  'D' = create donut\n");
   printf("  'V' = create vase\n");
   printf("  'M' = create mobius strip\n");
   printf("\nMotion controls:\n");
   printf("  's' = switch to scaling mode\n");
   printf("  'r' = switch to rotation mode\n");
   printf("  't' = switch to translation mode\n");
   printf("  'x' = decrease X scaling/rotation/translation\n");
   printf("  'X' = increase X scaling/rotation/translation\n");
   printf("  'y' = decrease Y scaling/rotation/translation\n");
   printf("  'Y' = increase Y scaling/rotation/translation\n");
   printf("  'z' = decrease Z scaling/rotation/translation\n");
   printf("\nOther controls:\n");
   printf("  'a' = accept current object\n");
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(250, 250);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
   glutCreateWindow("Object");
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   init();
   print_menu();
   glutMainLoop();
   return 0;
}

