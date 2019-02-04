#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <ctime>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
using namespace std;

// Window Borders
GLint SCREEN_WIDTH = 500;
GLint SCREEN_HEIGHT = 500;
GLint SCREEN_DEPTH = 500;

//---------------------------------------
// Calculate random value between [-R..R]
//---------------------------------------
float myrand(float R)
{
   return (2 * R * rand()) / RAND_MAX - R;
}

void firework(float x1, float y1, float z1) 
{
    // Choosing colors w/ floats from 0-1
    float red = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float green = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float blue = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    glColor3f(red,green,blue);

    
    for(int j = 0; j < rand() % (75 - 50 + 1) + 100; ++j) 
    {        
        glVertex3f(x1,y1,z1);
        float x2 = myrand(50) + x1;
        float y2 =myrand(70) + y1;
        float z2 = myrand(80) + z1;
        glVertex3f(x2,y2,z2);
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
   float radius = 100;
   glOrtho(-radius, radius, -radius, radius, -radius, radius);
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0.0, 1.0, 0.0);
   glBegin(GL_LINES);
   float x1, y1, z1;
//    float x1;
//    float y1;
//    float z1;
//    float x1 = myrand(10);
//    float y1 = myrand(20);
//    float z1 = myrand(50);
   for (int i = 0; i < rand() % (8 - 5 + 1) + 5; ++i)
   {
       x1 = myrand(100);
       y1 = myrand(100);
       z1 = myrand(100);
       firework(x1,y1,z1);
   }
   glEnd();
   glFlush();
}

int main(int argc, char *argv[]) 
{
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutCreateWindow("Fireworks");
    glutDisplayFunc(display);
    // glutIdleFunc(idle);
    init();
    glutMainLoop();
    return 0;
}