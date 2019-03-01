#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<iostream>
using namespace std;

float xangle, yangle, zangle;

// Object class
const int SIZE = 20;
class Object 
{
public:

   // Display parameters
   float xpos, ypos, zpos;
   float playerx, playery, playerz;
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
   s.playerx = s.playery = s.playerz = 0;
   xangle = yangle = zangle = 0;
}

void init_world_cube(Object &s, float size)
{
   // Define 8 vertices
   float ax = s.xpos - size / 2;
   float ay = s.ypos - size / 2;
   float az = s.zpos + size / 2;
   float bx = s.xpos + size / 2;
   float by = s.ypos - size / 2;
   float bz = s.zpos + size / 2;
   float cx = s.xpos + size / 2;
   float cy = s.ypos + size / 2;
   float cz = s.zpos + size / 2;
   float dx = s.xpos - size / 2;
   float dy = s.ypos + size / 2;
   float dz = s.zpos + size / 2;
   float ex = s.xpos - size / 2;
   float ey = s.ypos - size / 2;
   float ez = s.zpos - size / 2;
   float fx = s.xpos + size / 2;
   float fy = s.ypos - size / 2;
   float fz = s.zpos - size / 2;
   float gx = s.xpos + size / 2;
   float gy = s.ypos + size / 2;
   float gz = s.zpos - size / 2;
   float hx = s.xpos - size / 2;
   float hy = s.ypos + size / 2;
   float hz = s.zpos - size / 2;

   // Draw 6 faces
   glBegin(GL_LINE_LOOP);
   glColor3f(1.0, 0.0, 0.0);
   glVertex3f(ax, ay, az);
   glVertex3f(bx, by, bz);
   glVertex3f(cx, cy, cz);
   glVertex3f(dx, dy, dz);
   glEnd();

   glBegin(GL_LINE_LOOP);
   glColor3f(0.0, 1.0, 0.0);
   glVertex3f(ax, ay, az);
   glVertex3f(dx, dy, dz);
   glVertex3f(hx, hy, hz);
   glVertex3f(ex, ey, ez);
   glEnd();

   glBegin(GL_LINE_LOOP);
   glColor3f(0.0, 0.0, 1.0);
   glVertex3f(ax, ay, az);
   glVertex3f(ex, ey, ez);
   glVertex3f(fx, fy, fz);
   glVertex3f(bx, by, bz);
   glEnd();

   glBegin(GL_LINE_LOOP);
   glColor3f(0.0, 1.0, 1.0);
   glVertex3f(gx, gy, gz);
   glVertex3f(fx, fy, fz);
   glVertex3f(ex, ey, ez);
   glVertex3f(hx, hy, hz);
   glEnd();

   glBegin(GL_LINE_LOOP);
   glColor3f(1.0, 0.0, 1.0);
   glVertex3f(gx, gy, gz);
   glVertex3f(cx, cy, cz);
   glVertex3f(bx, by, bz);
   glVertex3f(fx, fy, fz);
   glEnd();

   glBegin(GL_LINE_LOOP);
   glColor3f(1.0, 1.0, 0.0);
   glVertex3f(gx, gy, gz);
   glVertex3f(hx, hy, hz);
   glVertex3f(dx, dy, dz);
   glVertex3f(cx, cy, cz);
   glEnd();
}

void init_player_cube(Object &s, float size)
{
   // Define 8 vertices
   float ax = s.playerx - size / 2;
   float ay = s.playery - size / 2;
   float az = s.playerz + size / 2;
   float bx = s.playerx + size / 2;
   float by = s.playery - size / 2;
   float bz = s.playerz + size / 2;
   float cx = s.playerx + size / 2;
   float cy = s.playery + size / 2;
   float cz = s.playerz + size / 2;
   float dx = s.playerx - size / 2;
   float dy = s.playery + size / 2;
   float dz = s.playerz + size / 2;
   float ex = s.playerx - size / 2;
   float ey = s.playery - size / 2;
   float ez = s.playerz - size / 2;
   float fx = s.playerx + size / 2;
   float fy = s.playery - size / 2;
   float fz = s.playerz - size / 2;
   float gx = s.playerx + size / 2;
   float gy = s.playery + size / 2;
   float gz = s.playerz - size / 2;
   float hx = s.playerx - size / 2;
   float hy = s.playery + size / 2;
   float hz = s.playerz - size / 2;

   // Draw 6 faces
   glBegin(GL_LINE_LOOP);
   glColor3f(1.0, 1.0, 1.0);
   glVertex3f(ax, ay, az);
   glVertex3f(bx, by, bz);
   glVertex3f(cx, cy, cz);
   glVertex3f(dx, dy, dz);
   glEnd();

   glBegin(GL_LINE_LOOP);
   glColor3f(1.0, 1.0, 1.0);
   glVertex3f(ax, ay, az);
   glVertex3f(dx, dy, dz);
   glVertex3f(hx, hy, hz);
   glVertex3f(ex, ey, ez);
   glEnd();

   glBegin(GL_LINE_LOOP);
   glColor3f(1.0, 1.0, 1.0);
   glVertex3f(ax, ay, az);
   glVertex3f(ex, ey, ez);
   glVertex3f(fx, fy, fz);
   glVertex3f(bx, by, bz);
   glEnd();

   glBegin(GL_LINE_LOOP);
   glColor3f(1.0, 1.0, 1.0);
   glVertex3f(gx, gy, gz);
   glVertex3f(fx, fy, fz);
   glVertex3f(ex, ey, ez);
   glVertex3f(hx, hy, hz);
   glEnd();

   glBegin(GL_LINE_LOOP);
   glColor3f(1.0, 1.0, 1.0);
   glVertex3f(gx, gy, gz);
   glVertex3f(cx, cy, cz);
   glVertex3f(bx, by, bz);
   glVertex3f(fx, fy, fz);
   glEnd();

   glBegin(GL_LINE_LOOP);
   glColor3f(1.0, 1.0, 0.0);
   glVertex3f(gx, gy, gz);
   glVertex3f(hx, hy, hz);
   glVertex3f(dx, dy, dz);
   glVertex3f(cx, cy, cz);
   glEnd();
}

void init_cube(Object &s, float size)
{
   // Define 8 vertices
   float ax = s.playerx - size / 2;
   float ay = s.playery - size / 2;
   float az = s.playerz + size / 2;
   float bx = s.playerx + size / 2;
   float by = s.playery - size / 2;
   float bz = s.playerz + size / 2;
   float cx = s.playerx + size / 2;
   float cy = s.playery + size / 2;
   float cz = s.playerz + size / 2;
   float dx = s.playerx - size / 2;
   float dy = s.playery + size / 2;
   float dz = s.playerz + size / 2;
   float ex = s.playerx - size / 2;
   float ey = s.playery - size / 2;
   float ez = s.playerz - size / 2;
   float fx = s.playerx + size / 2;
   float fy = s.playery - size / 2;
   float fz = s.playerz - size / 2;
   float gx = s.playerx + size / 2;
   float gy = s.playery + size / 2;
   float gz = s.playerz - size / 2;
   float hx = s.playerx - size / 2;
   float hy = s.playery + size / 2;
   float hz = s.playerz - size / 2;

   // Draw 6 faces
   glBegin(GL_LINE_LOOP);
   glColor3f(1.0, 0.0, 0.0);
   glVertex3f(ax, ay, az);
   glVertex3f(bx, by, bz);
   glVertex3f(cx, cy, cz);
   glVertex3f(dx, dy, dz);
   glEnd();

   glBegin(GL_LINE_LOOP);
   glColor3f(0.0, 1.0, 0.0);
   glVertex3f(ax, ay, az);
   glVertex3f(dx, dy, dz);
   glVertex3f(hx, hy, hz);
   glVertex3f(ex, ey, ez);
   glEnd();

   glBegin(GL_LINE_LOOP);
   glColor3f(0.0, 0.0, 1.0);
   glVertex3f(ax, ay, az);
   glVertex3f(ex, ey, ez);
   glVertex3f(fx, fy, fz);
   glVertex3f(bx, by, bz);
   glEnd();

   glBegin(GL_LINE_LOOP);
   glColor3f(0.0, 1.0, 1.0);
   glVertex3f(gx, gy, gz);
   glVertex3f(fx, fy, fz);
   glVertex3f(ex, ey, ez);
   glVertex3f(hx, hy, hz);
   glEnd();

   glBegin(GL_LINE_LOOP);
   glColor3f(1.0, 0.0, 1.0);
   glVertex3f(gx, gy, gz);
   glVertex3f(cx, cy, cz);
   glVertex3f(bx, by, bz);
   glVertex3f(fx, fy, fz);
   glEnd();

   glBegin(GL_LINE_LOOP);
   glColor3f(1.0, 1.0, 0.0);
   glVertex3f(gx, gy, gz);
   glVertex3f(hx, hy, hz);
   glVertex3f(dx, dy, dz);
   glVertex3f(cx, cy, cz);
   glEnd();
}

//---------------------------------------
// Display geometric object
//---------------------------------------
void display_object(Object &object)
{
   init_world_cube(object, 2.0);
   init_player_cube(object, 0.1);
   // Perform geometric transformation
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(object.xpos, object.ypos, object.zpos);
   glRotatef(xangle, 1.0, 0.0, 0.0);
   glRotatef(yangle, 0.0, 1.0, 0.0);
   glRotatef(zangle, 0.0, 0.0, 1.0);
   // cout << xangle << endl;
   // cout << yangle << endl;
   // cout << zangle << endl;
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
   glOrtho(-1.4, 1.4, -1.4, 1.4, -1.4, 1.4);
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
   if ((key == '+') && (save_count < MAX_SAVE))
   {
      save_object[save_count] = object;
      // init_object(object);
      printf("Object %d was accepted\n", save_count);
      save_count++;
   }

   // Delete object
   if (key == '-') 
   {
      // Delete the cube at the current location 
      // Loop over array and see if current pos is at cube pos

      for (int i = 0; i < MAX_SAVE; ++i) 
      {
         if (object.playerx == object.xpos && object.playery == object.ypos && object.playerz == object.zpos) 
         {
            save_object[i] = save_object[i + 1];
         }
      }
      // init_object(object);
      printf("Object was deleted\n");
   }

   
   // Change mode
   if (key == 'r')
      mode = 'r';
   if (mode == 'R')
      mode = 'R';
   if (key == 'f')
      mode = 'f';
   if (key == 'F')
      mode = 'F';

   // Update angles in rotate mode
   if (mode == 'r')
   {
      if (key == 'x')
         xangle -= 5;
      if (key == 'X')
         xangle += 5;
      if (key == 'y')
         yangle -= 5;
      if (key == 'Y')
         yangle += 5;
      if (key == 'z')
         zangle -= 5;
      if (key == 'Z')
         zangle += 5;
   }

   // Update positions in translate mode
   if (mode == 'f')
   {
      if (key == 'x')
         object.playerx -= 0.1;
      if (key == 'X')
         object.playerx += 0.1;
      if (key == 'y')
         object.playery -= 0.1;
      if (key == 'Y')
         object.playery += 0.1;
      if (key == 'z')
         object.playerz -= 0.1;
      if (key == 'Z')
         object.playerz += 0.1;
   }

   if (mode == 'F')
   {
       // This is for my own sanity
      if (key == 'a')
         object.playerx -= 0.1;
      if (key == 'd')
         object.playerx += 0.1;
      if (key == 's')
         object.playery -= 0.1;
      if (key == 'w')
         object.playery += 0.1;
      if (key == 'z')
         object.playerz -= 0.1;
      if (key == 'Z')
         object.playerz += 0.1;
   }

     if (mode == 'R')
   {
      if (key == 'a')
         xangle -= 5;
      if (key == 'd')
         xangle += 5;
      if (key == 's')
         yangle -= 5;
      if (key == 'w')
         yangle += 5;
      if (key == 'z')
         zangle -= 5;
      if (key == 'Z')
         zangle += 5;
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
   printf("  'C' = create cube\n");
   
   printf("\nMotion controls:\n");
   printf("  'r'   = switch to rotation mode\n");
   printf("  'f'   = switch to fly mode\n");
   printf("  'F'   = switch to fly mode and use WASD keys\n");
   printf("  'R'   = switch to rotation mode and use WASD keys\n");
   printf("  'x/a' = decrease X scaling/rotation/translation\n");
   printf("  'X/d' = increase X scaling/rotation/translation\n");
   printf("  'y/s' = decrease Y scaling/rotation/translation\n");
   printf("  'Y/w' = increase Y scaling/rotation/translation\n");
   printf("  'z'   = decrease Z scaling/rotation/translation\n");
   printf("  'Z'   = increase Z scaling/rotation/translation\n");

   printf("\nOther controls:\n");
   printf("  '+' = add cube at your location\n");
   printf("  '-' = delete last cube\n");
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


