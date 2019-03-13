#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
using namespace std;

// Global variables 
#define ROTATE 2
int xangle = 0;
int yangle = 0;
int zangle = 0;
#define SIZE 31

// Surface coordinates
float Px[SIZE + 1][SIZE + 1];
float Py[SIZE + 1][SIZE + 1];
float Pz[SIZE + 1][SIZE + 1];

// Surface Normals
float Nx[SIZE + 1][SIZE + 1];
float Ny[SIZE + 1][SIZE + 1];
float Nz[SIZE + 1][SIZE + 1];

// Colors
float R[SIZE + 1][SIZE + 1];
float G[SIZE + 1][SIZE + 1];
float B[SIZE + 1][SIZE + 1];

// Light0 Position
#define LIGHT0 0
float lx0 = 0.5;
float ly0 = -0.5;
float lz0 = 0.25;

float Mr0 = ((float) rand() / (RAND_MAX)) ;
float Mg0 = ((float) rand() / (RAND_MAX)) ;
float Mb0 = ((float) rand() / (RAND_MAX))  ;

float Lr0 = ((float) rand() / (RAND_MAX)) ;
float Lg0 = ((float) rand() / (RAND_MAX)) ;
float Lb0 = ((float) rand() / (RAND_MAX)) ;

// Light1 Position
#define LIGHT1 1
float lx1 = 0.25;
float ly1 = -0.25;
float lz1 = 0.25;

float Mr1 = ((float) rand() / (RAND_MAX)) ;
float Mg1 = ((float) rand() / (RAND_MAX)) ;
float Mb1 = ((float) rand() / (RAND_MAX))  ;

float Lr1 = ((float) rand() / (RAND_MAX));
float Lg1 = ((float) rand() / (RAND_MAX));
float Lb1 = ((float) rand() / (RAND_MAX));

int mode = ROTATE;


float myrand(float R)
{
   return (2 * R * rand()) / RAND_MAX - R;
}


void split(int xlow, int xhigh, int ylow, int yhigh, float radius)
{
   // Check terminating condition
   if ((xhigh > xlow+1) || (yhigh > ylow+1))
   {
      // Calculate length of diagonal
      int xmid = (xhigh + xlow) / 2;
      int ymid = (yhigh + ylow) / 2;
      float dx = Px[xhigh][yhigh] - Px[xlow][ylow];
      float dy = Py[xhigh][yhigh] - Py[xlow][ylow];
      float dz = Pz[xhigh][yhigh] - Pz[xlow][ylow];
      float length = sqrt(dx * dx + dy * dy + dz * dz) / radius;

      // Generate five midpoints with random displacements
      Px[xlow][ymid] = (Px[xlow][ylow] + Px[xlow][yhigh]) / 2 + myrand(length);
      Py[xlow][ymid] = (Py[xlow][ylow] + Py[xlow][yhigh]) / 2 + myrand(length);
      Pz[xlow][ymid] = (Pz[xlow][ylow] + Pz[xlow][yhigh]) / 2 + myrand(length);

      Px[xhigh][ymid] = (Px[xhigh][ylow] + Px[xhigh][yhigh]) / 2 + myrand(length);
      Py[xhigh][ymid] = (Py[xhigh][ylow] + Py[xhigh][yhigh]) / 2 + myrand(length);
      Pz[xhigh][ymid] = (Pz[xhigh][ylow] + Pz[xhigh][yhigh]) / 2 + myrand(length);

      Px[xmid][ylow] = (Px[xlow][ylow] + Px[xhigh][ylow]) / 2 + myrand(length);
      Py[xmid][ylow] = (Py[xlow][ylow] + Py[xhigh][ylow]) / 2 + myrand(length);
      Pz[xmid][ylow] = (Pz[xlow][ylow] + Pz[xhigh][ylow]) / 2 + myrand(length);

      Px[xmid][yhigh] = (Px[xlow][yhigh] + Px[xhigh][yhigh]) / 2 + myrand(length);
      Py[xmid][yhigh] = (Py[xlow][yhigh] + Py[xhigh][yhigh]) / 2 + myrand(length);
      Pz[xmid][yhigh] = (Pz[xlow][yhigh] + Pz[xhigh][yhigh]) / 2 + myrand(length);

      Px[xmid][ymid] = (Px[xlow][ylow] + Px[xhigh][yhigh]) / 2 + myrand(length);
      Py[xmid][ymid] = (Py[xlow][ylow] + Py[xhigh][yhigh]) / 2 + myrand(length);
      Pz[xmid][ymid] = (Pz[xlow][ylow] + Pz[xhigh][yhigh]) / 2 + myrand(length);

      // Perform recursive calls
      split(xlow, xmid, ylow, ymid, radius);
      split(xmid, xhigh, ylow, ymid, radius);
      split(xlow, xmid, ymid, yhigh, radius);
      split(xmid, xhigh, ymid, yhigh, radius);
   }
}


//---------------------------------------
// Calculate surface normals
//---------------------------------------
void init_normals()
{
   // Initialize surface normals
   int i, j;
   for (i=0; i<=SIZE; i++)
   for (j=0; j<=SIZE; j++)
   {
      // Get tangents S and T
      float Sx = (i<SIZE) ? Px[i+1][j] - Px[i][j] : Px[i][j] - Px[i-1][j];
      float Sy = (i<SIZE) ? Py[i+1][j] - Py[i][j] : Py[i][j] - Py[i-1][j];
      float Sz = (i<SIZE) ? Pz[i+1][j] - Pz[i][j] : Pz[i][j] - Pz[i-1][j];
      float Tx = (j<SIZE) ? Px[i][j+1] - Px[i][j] : Px[i][j] - Px[i][j-1];
      float Ty = (j<SIZE) ? Py[i][j+1] - Py[i][j] : Py[i][j] - Py[i][j-1];
      float Tz = (j<SIZE) ? Pz[i][j+1] - Pz[i][j] : Pz[i][j] - Pz[i][j-1];
      
      // Calculate N = S cross T
      float Slength = sqrt(Sx*Sx + Sy*Sy + Sz*Sz);
      float Tlength = sqrt(Tx*Tx + Ty*Ty + Tz*Tz);
      if ((Slength * Tlength) > 0)
      {
         Nx[i][j] = (Sy*Tz - Sz*Ty) / (Slength * Tlength);
         Ny[i][j] = (Sz*Tx - Sx*Tz) / (Slength * Tlength);
         Nz[i][j] = (Sx*Ty - Sy*Tx) / (Slength * Tlength);
      }
   }
}


void init_surface(float Xmin, float Xmax, float Ymin, float Ymax,
		            float Wxx, float Wxy, float Wyy, float Wx, float Wy, float W1)
{
   Px[0][0] = -0.5;
   Py[0][0] = -0.5;
   Pz[0][0] = 0.0;
   Px[0][SIZE] = -0.5;
   Py[0][SIZE] = 0.5;
   Pz[0][SIZE] = 0.0;
   Px[SIZE][0] = 0.5;
   Py[SIZE][0] = -0.5;
   Pz[SIZE][0] = 0.0;
   Px[SIZE][SIZE] = 0.5;
   Py[SIZE][SIZE] = 0.5;
   Pz[SIZE][SIZE] = 0.0;
   init_normals();
   // LIGHT0
   lx0 = ((float) rand() / (RAND_MAX)) ;
   ly0 = ((float) rand() / (RAND_MAX)) ;
   lz0 = ((float) rand() / (RAND_MAX)) ;
   Lr0 = ((float) rand() / (RAND_MAX)) ;
   Lg0 = ((float) rand() / (RAND_MAX)) ;
   Lb0 = ((float) rand() / (RAND_MAX)) ;

   // LIGHT1
   lx1 = ((float) rand() / (RAND_MAX)) ;
   ly1 = ((float) rand() / (RAND_MAX)) ;
   lz1 = ((float) rand() / (RAND_MAX)) ;
   Lr1 = ((float) rand() / (RAND_MAX)) ;
   Lg1 = ((float) rand() / (RAND_MAX)) ;
   Lb1 = ((float) rand() / (RAND_MAX)) ;
   split(0, SIZE, 0, SIZE, 20);
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
      glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
      glEnable(GL_DEPTH_TEST);

      // OpenGL uses Phong shading
      // Come up with a way to only use Gouraud Shading
      // Put following inside init() function
      // glShadeModel(GL_SMOOTH);
      // glEnable(GL_NORMALIZE);
      // init_light(GL_LIGHT0, 0, 1, 1, 0.5, 0.5, 0.5);
      // init_light(GL_LIGHT1, 0, 0, 1, 0.5, 0.5, 0.5);
      // init_light(GL_LIGHT2, 0, 1, 0, 0.5, 0.5, 0.5);


      // Initialize surface
      init_surface(-1.0, 1.0, -1.0, 1.0, -1, 0, -1, 0, 0, 0);
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
   glRotatef(xangle, 1.0, 0.0, 0.0);
   glRotatef(yangle, 0.0, 1.0, 0.0);
   glRotatef(zangle, 0.0, 0.0, 1.0);

   for (int i = 0; i < SIZE; ++i)
   {
      for (int j = 0; j < SIZE; ++j)
      {
         float Lx0 = (lx0 - Px[i][j]);
         float Ly0 = ly0 - Py[i][j];
         float Lz0 = lz0 - Pz[i][j];
         float Lx1 = (lx1 - Px[i][j]);
         float Ly1 = ly1 - Py[i][j];
         float Lz1 = lz1 - Pz[i][j];
         float length0 = sqrt(Lx0 * Lx0 + Ly0 * Ly0 + Lz0 * Lz0);
         float length1 = sqrt(Lx1 * Lx1 + Ly1 * Ly1 + Lz1 * Lz1);

         Lx0 = Lx0 / length0;
         Ly0 = Ly0 / length0;
         Lz0 = Lz0 / length0;
         Lx1 = Lx1 / length1;
         Ly1 = Ly1 / length1;
         Lz1 = Lz1 / length1;

         // Dot product of N, L
         float dot0 = (Lx0 * Nx[i][j]) + (Ly0 * Ny[i][j]) + (Lz0 * Nz[i][j]);
         float dot1 = (Lx1 * Nx[i][j]) + (Ly1 * Ny[i][j]) + (Lz1 * Nz[i][j]);

         // Make M and L hard coded, global vars
         // Mr0, Mg0, Mb0
         // Lr0, Lg0, Lb0
         // R = Mr0 * Lr0 * dot0
         // G = Mg0 * Lg0 * dot0
         // B = Mb0 * Lb0 * dot0
         R[i][j] = Mr0 * Lr0 * dot0 + Mr1 * Lr1 * dot1;
         G[i][j] = Mg0 * Lg0 * dot0 + Mg1 * Lg1 * dot1;
         B[i][j] = Mb0 * Lb0 * dot0 + Mb1 * Lb1 * dot1;
      }
   }

   
   // nested for loop
   // color then point
   // Draw the surface

   for (int i = 0; i < SIZE; ++i)
   {
      for (int j = 0; j < SIZE; ++j)
      {
         glBegin(GL_POLYGON);         	 
         // glNormal3f(Nx[i][j], Ny[i][j], Nz[i][j]);
         glColor3f(R[i][j], G[i][j], B[i][j]);
         glVertex3f(Px[i][j], Py[i][j], Pz[i][j]);

         // glNormal3f(Nx[i + 1][j], Ny[i + 1][j], Nz[i + 1][j]);
         glColor3f(R[i + 1][j], G[i + 1][j], B[i + 1][j]);
         glVertex3f(Px[i + 1][j], Py[i + 1][j], Pz[i + 1][j]);

         // glNormal3f(Nx[i + 1][j + 1], Ny[i + 1][j + 1], Nz[i + 1][j + 1]);
         glColor3f(R[i + 1][j + 1], G[i + 1][j + 1], B[i + 1][j + 1]);
         glVertex3f(Px[i + 1][j + 1], Py[i + 1][j + 1], Pz[i + 1][j + 1]);
         
         // glNormal3f(Nx[i][j + 1], Ny[i][j + 1], Nz[i][j + 1]);
         glColor3f(R[i][j + 1], G[i][j + 1], B[i][j + 1]);
         glVertex3f(Px[i][j + 1], Py[i][j + 1], Pz[i][j + 1]);
         glEnd();
      }
   }
   glFlush();
}

//---------------------------------------
// Keyboard callback for OpenGL
//---------------------------------------
void keyboard(unsigned char key, int x, int y)
{
   // Initialize surface
   if (key == 'i')
      init_surface(-1.0, 1.0, -1.0, 1.0, -1, 0, -1, 0, 0, 0);

   if (key == '0')
   {
      printf("LIGHT0 Activated\n");
      mode = LIGHT0;
   }

   if (key == '1')
   {
      printf("LIGHT1 Activated\n");
      mode = LIGHT1;
   }

   if (key == '2')
   {
      printf("Rotate Mode\n");
      mode = ROTATE;
   }

   if (mode == ROTATE)
   {
      // Update angles
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
   }


   if (mode == LIGHT0)
   {
      if (key == 'x')
         lx0 -= 1;
      else if (key == 'y')
         ly0 -= 1;
      else if (key == 'z')
         lz0 -= 1;
      else if (key == 'X')
         lx0 += 1;
      else if (key == 'Y')
         ly0 += 1;
      else if (key == 'Z')
         lz0 += 1;
      else if (key == 'R')
         Lr0 += 0.1;
      else if (key == 'r')
         Lr0 -= 0.1;
      else if (key == 'G')
         Lg0 += 0.1;
      else if (key == 'g')
         Lg0 -= 0.1;
      else if (key == 'B')
         Lb0 += 0.1;
      else if (key == 'b')
         Lb0 -= 0.1;
   }

   else if (mode == LIGHT1)
   {
      if (key == 'x')
         lx1 -= 1;
      else if (key == 'y')
         ly1 -= 1;
      else if (key == 'z')
         lz1 -= 1;
      else if (key == 'X')
         lx1 += 1;
      else if (key == 'Y')
         ly1 += 1;
      else if (key == 'Z')
         lz1 += 1;
      else if (key == 'R')
         Lr1 += 0.1;
      else if (key == 'r')
         Lr1 -= 0.1;
      else if (key == 'G')
         Lg1 += 0.1;
      else if (key == 'g')
         Lg1 -= 0.1;
      else if (key == 'B')
         Lb1 += 0.1;
      else if (key == 'b')
         Lb1 -= 0.1;
   }


   // Redraw objects
   glutPostRedisplay();
}


void print_menu() 
{
   printf("Keyboard commands:\n");
   printf("   '2' - switch to Rotate Mode\n");
   printf("   'x' - rotate x-axis -5 degrees\n");
   printf("   'X' - rotate x-axis +5 degrees\n");
   printf("   'y' - rotate y-axis -5 degrees\n");
   printf("   'Y' - rotate y-axis +5 degrees\n");
   printf("   'z' - rotate z-axis -5 degrees\n");
   printf("   'Z' - rotate z-axis +5 degrees\n");
   printf("\n");
   printf("   '0' - switch to LIGHT0\n");
   printf("   '1' - switch to LIGHT1\n");
   printf("   'r' - decrease Red light by 0.1\n");
   printf("   'R' - increase Red light by 0.1\n");
   printf("   'g' - decrease green light by 0.1\n");
   printf("   'G' - increase green light by 0.1\n");
   printf("   'b' - decrease blue light by 0.1\n");
   printf("   'B' - increase blue light by 0.1\n");
   printf("   'x' - rotate x-axis -1 degrees\n");
   printf("   'X' - rotate x-axis +1 degrees\n");
   printf("   'y' - rotate y-axis -1 degrees\n");
   printf("   'Y' - rotate y-axis +1 degrees\n");
   printf("   'z' - rotate z-axis -1 degrees\n");
   printf("   'Z' - rotate z-axis +1 degrees\n");



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
   glutCreateWindow("Gouraud Shading");
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   init();
   init_surface(-1.0, 1.0, -1.0, 1.0, -1, 0, -1, 0, 0, 0);
   print_menu();
   glutMainLoop();
   return 0;
}