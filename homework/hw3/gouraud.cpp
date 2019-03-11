#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Global variables 
int xangle = 0;
int yangle = 0;
int zangle = 0;
#define SIZE 31

// Surface coordinates
float Px[SIZE + 1][SIZE + 1];
float Py[SIZE + 1][SIZE + 1];
float Pz[SIZE + 1][SIZE + 1];

float Nx[SIZE + 1][SIZE + 1];
float Ny[SIZE + 1][SIZE + 1];
float Nz[SIZE + 1][SIZE + 1];

float R[SIZE + 1][SIZE + 1];
float G[SIZE + 1][SIZE + 1];
float B[SIZE + 1][SIZE + 1];

#define STEP 0.1

#include "shading.cpp"

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
    split(0, SIZE, 0, SIZE, 20);
    
    for (int i = 0; i <= SIZE; ++i) { 
        for (int j = 0; j <= SIZE; ++j) {
            Nx[i][j] = -(2 * Wxx * Px[i][j] + Wxy * Py[i][j] + Wx);
            Ny[i][j] = -(2 * Wyy * Py[i][j] + Wxy * Px[i][j] + Wy);
            Nz[i][j] = 1;
            float length = sqrt(Nx[i][j] * Nx[i][j] 
                              + Ny[i][j] * Ny[i][j] 
                              + Nz[i][j] * Nz[i][j]);
                if (length > 0)
                {
                Nx[i][j] /= length;
                Ny[i][j] /= length;
                Nz[i][j] /= length;
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
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
      glEnable(GL_DEPTH_TEST);

      // Initialize smooth shading
      // Put following inside init() function
      glShadeModel(GL_SMOOTH);
      glEnable(GL_NORMALIZE);
      init_light(GL_LIGHT0, 0, 1, 1, 0.5, 0.5, 0.5);
      init_light(GL_LIGHT1, 0, 0, 1, 0.5, 0.5, 0.5);
      init_light(GL_LIGHT2, 0, 1, 0, 0.5, 0.5, 0.5);

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
   // Ka = Ks = 0, Kd = Kp = 1
   init_material(0, 1, 0, 100 * 1, 0.8, 0.6, 0.4);

   // nested for loop
   // color then point
   // Draw the surface

   for (int i = 0; i < SIZE; ++i)
   {
      for (int j = 0; j < SIZE; ++j)
      {
         glBegin(GL_POLYGON);
         glColor3f(R[i][j], G[i][j], B[i][j]);
         glVertex3f(Px[i][j], Py[i][j], Pz[i][j]);
         glColor3f(R[i + 1][j], G[i + 1][j], B[i + 1][j]);
         glVertex3f(Px[i + 1][j], Py[i + 1][j], Pz[i + 1][j]);
         glColor3f(R[i + 1][j + 1], G[i + 1][j + 1], B[i + 1][j + 1]);
         glVertex3f(Px[i + 1][j + 1], Py[i + 1][j + 1], Pz[i + 1][j + 1]);
         glColor3f(R[i][j + 1], G[i][j + 1], B[i][j + 1]);
         glVertex3f(Px[i][j + 1], Py[i][j + 1], Pz[i][j + 1]);
         glEnd();
      }
   }
   // int i, j;
   // glColor3f(1.0, 0.0, 0.0);
   // for (i = 0; i <= SIZE; i++)
   // {
   //    glBegin(GL_LINE_STRIP);
   //    for (j = 0; j <= SIZE; j++)
	//  glVertex3f(Px[i][j], Py[i][j], Pz[i][j]);
   //    glEnd();
   // }
   // glColor3f(0.0, 1.0, 0.0);
   // for (j = 0; j <= SIZE; j++)
   // {
   //    glBegin(GL_LINE_STRIP);
   //    for (i = 0; i <= SIZE; i++)
	//  glVertex3f(Px[i][j], Py[i][j], Pz[i][j]);
   //    glEnd();
   // }
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

   // Update angles
   else if (key == 'x')
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

     // Handle material properties
   if (key == 'a')
      Ka -= STEP;
   if (key == 'd')
      Kd -= STEP;
   if (key == 's')
      Ks -= STEP;
   if (key == 'p')
      Kp -= STEP;
   if (key == 'A')
      Ka += STEP;
   if (key == 'D')
      Kd += STEP;
   if (key == 'S')
      Ks += STEP;
   if (key == 'P')
      Kp += STEP;
   if (Ka < 0)
      Ka = 0;
   if (Kd < 0)
      Kd = 0;
   if (Ks < 0)
      Ks = 0;
   if (Kp < STEP)
      Kp = STEP;
   glutPostRedisplay();

   // Redraw objects
   glutPostRedisplay();
}


void print_menu() 
{
    printf("Keyboard commands:\n");
    printf("   'x' - rotate x-axis -5 degrees\n");
    printf("   'X' - rotate x-axis +5 degrees\n");
    printf("   'y' - rotate y-axis -5 degrees\n");
    printf("   'Y' - rotate y-axis +5 degrees\n");
    printf("   'z' - rotate z-axis -5 degrees\n");
    printf("   'Z' - rotate z-axis +5 degrees\n");
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
   glutCreateWindow("Surface");
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   init();
   init_surface(-1.0, 1.0, -1.0, 1.0, -1, 0, -1, 0, 0, 0);
   print_menu();
   glutMainLoop();
   return 0;
}