#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Window Borders
GLint SCREEN_WIDTH = 500;
GLint SCREEN_HEIGHT = 500;
GLint SCREEN_DEPTH = 16;

//---------------------------------------
// Calculate random value between [-R..R]
//---------------------------------------
float myrand(float R)
{
   return (2 * R * rand()) / RAND_MAX - R;
}

void firework(float angle1) 
{
    // srand(time(NULL));
    // Choosing colors
    int red = rand() % 255;
    int green = rand() % 255;
    int blue = rand() % 255;

    int x1 = myrand(SCREEN_WIDTH);
    int y1 = myrand(SCREEN_HEIGHT);
    int z1 = myrand(SCREEN_DEPTH);

    glColor3f(red,green,blue);
    glBegin(GL_LINES);
    
    int x2,y2,z2;
    for(int i = 0; i < rand() % (200 - 150 + 1) + 150; ++i){
        glVertex3f(0,0,0);
        x2 = rand() % 2000 - 1000;
        y2 = rand() % 2000 - 1000;
        z2 = rand() % 2000 - 1000;
        glVertex3f(x2,y2,z2);
    }
    glEnd();

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
   // Draw tree
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0.0, 1.0, 0.0);
   glBegin(GL_LINES);
   firework(1.5);
   glEnd();
   glFlush();
}

int main(int argc, char *argv[]) 
{
    glutInit(&argc, argv);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Fireworks");
    glutDisplayFunc(display);
    // glutIdleFunc(idle);
    init();
    glutMainLoop();
    return 0;
}