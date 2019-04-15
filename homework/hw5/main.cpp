#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
using namespace std;
#include "libim/im_color.h"

// #define XDIM 256
// #define YDIM 256
const int rows = 21;
const int cols = 21;
unsigned char maze[rows][cols];
// unsigned char image[YDIM][XDIM][3];
// Global variables 
#define ROTATE 1
#define TRANSLATE 2
int xangle = 10;
int yangle = 10;
int zangle = 10;
int xpos = 0;
int ypos = 0;
int zpos = 0;
int mode = ROTATE;

unsigned char *texture;
int xdim, ydim;
char *brick = "textures/brick.jpg";
char *rock = "textures/rock.jpg";
char *wood = "textures/wood.jpg";
char *grass = "textures/grass.jpg";
unsigned char *rock_texture;
unsigned char *brick_texture;
unsigned char *wood_texture;
unsigned char *grass_texture;

char brick_array[1];
char rock_array[1];
char wood_array[1];
char grass_array[1];


void read (string file) 
{
    string line;
    ifstream myfile (file);
    myfile >> noskipws;
    if (myfile.is_open())
    {
            // cout << line << '\n';

            // Reads in maze to array
            for (int i = 0; i < rows; ++i)
            {
                for ( int j = 0; j < cols; ++j)
                {
                    myfile >> maze[i][j];
                }
                // cout << endl;
            }
        myfile.close();
    }

    else cout << "Unable to open file"; 

    // return 0;
}


void init_rock(char *rock, unsigned char *&texture, int &xdim, int &ydim)
{
	im_color image;
	image.ReadJpg(rock);

	printf("Reading image %s\n", rock);
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


void init_brick(char *brick, unsigned char *&texture, int &xdim, int &ydim)
{
	im_color image;
	image.ReadJpg(brick);

	// printf("Reading image %s\n", brick);
   	xdim = 1; while (xdim < image.R.Xdim) xdim*=2; xdim /=2;
   	ydim = 1; while (ydim < image.R.Ydim) ydim*=2; ydim /=2;
   	image.Interpolate(xdim, ydim);
   	// printf("Interpolating to %d by %d\n", xdim, ydim);

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

void init_wood(char *wood, unsigned char *&texture, int &xdim, int &ydim)
{
	im_color image;
	image.ReadJpg(wood);

	// printf("Reading image %s\n", wood);
   	xdim = 1; while (xdim < image.R.Xdim) xdim*=2; xdim /=2;
   	ydim = 1; while (ydim < image.R.Ydim) ydim*=2; ydim /=2;
   	image.Interpolate(xdim, ydim);
   	// printf("Interpolating to %d by %d\n", xdim, ydim);

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


void init_grass(char *grass, unsigned char *&texture, int &xdim, int &ydim)
{
	im_color image;
	image.ReadJpg(grass);

	// printf("Reading image %s\n", grass);
   	xdim = 1; while (xdim < image.R.Xdim) xdim*=2; xdim /=2;
   	ydim = 1; while (ydim < image.R.Ydim) ydim*=2; ydim /=2;
   	image.Interpolate(xdim, ydim);
   	// printf("Interpolating to %d by %d\n", xdim, ydim);

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

void init_block(float xmin, float ymin, float zmin,
           	   float xmax, float ymax, float zmax) 
{
	// Define 8 vertices
   	float ax = xmin, ay = ymin, az = zmax;
   	float bx = xmax, by = ymin, bz = zmax;
   	float cx = xmax, cy = ymax, cz = zmax;
   	float dx = xmin, dy = ymax, dz = zmax;

   	float ex = xmin, ey = ymin, ez = zmin;
   	float fx = xmax, fy = ymin, fz = zmin;
   	float gx = xmax, gy = ymax, gz = zmin;
   	float hx = xmin, hy = ymax, hz = zmin;

   	// Draw 6 faces

   	//front face
	glBegin(GL_POLYGON);  // Max texture coord 1.0
   	glTexCoord2f(0.0, 0.0);
   	glVertex3f(ax, ay, az);
   	glTexCoord2f(1.0, 0.0);
   	glVertex3f(bx, by, bz);
   	glTexCoord2f(1.0, 1.0);
   	glVertex3f(cx, cy, cz);
   	glTexCoord2f(0.0, 1.0);
   	glVertex3f(dx, dy, dz);
   	glEnd();

   	//left face
   	glBegin(GL_POLYGON);  // Max texture coord 1.0
   	glTexCoord2f(0.0, 0.0);
   	glVertex3f(ex, ey, ez);
   	glTexCoord2f(1.0, 0.0);
   	glVertex3f(ax, ay, az);
   	glTexCoord2f(1.0, 1.0);
   	glVertex3f(dx, dy, dz);
   	glTexCoord2f(0.0, 1.0);
   	glVertex3f(hx, hy, hz);
   	glEnd();

   	// back face
   	glBegin(GL_POLYGON);  // Max texture coord 1.0
   	glTexCoord2f(0.0, 0.0);
   	glVertex3f(fx, fy, fz);
   	glTexCoord2f(1.0, 0.0);
   	glVertex3f(ex, ey, ez);
   	glTexCoord2f(1.0, 1.0);
   	glVertex3f(hx, hy, hz);
   	glTexCoord2f(0.0, 1.0);
   	glVertex3f(gx, gy, gz);
   	glEnd();

   	// right face
   	glBegin(GL_POLYGON);  // Max texture coord 1.0
   	glTexCoord2f(0.0, 0.0);
   	glVertex3f(bx, by, bz);
   	glTexCoord2f(1.0, 0.0);
   	glVertex3f(fx, fy, fz);
   	glTexCoord2f(1.0, 1.0);
   	glVertex3f(gx, gy, gz);
   	glTexCoord2f(0.0, 1.0);
   	glVertex3f(cx, cy, cz);
   	glEnd();

   	// bottom face
   	glBegin(GL_POLYGON);  // Max texture coord 3.0
   	glTexCoord2f(0.0, 0.0);
   	glVertex3f(ax, ay, az);
   	glTexCoord2f(2.0, 0.0);
	glVertex3f(ex, ey, ez);
	glTexCoord2f(2.0, 2.0);
	glVertex3f(fx, fy, fz);
	glTexCoord2f(0.0, 2.0);
	glVertex3f(bx, by, bz);
	glEnd();

	// top face
	glBegin(GL_POLYGON);  // Max texture coord 3.0
	glTexCoord2f(0.0, 0.0);
	glVertex3f(gx, gy, gz);
	glTexCoord2f(3.0, 0.0);
	glVertex3f(cx, cy, cz);
	glTexCoord2f(3.0, 3.0);
	glVertex3f(dx, dy, dz);
	glTexCoord2f(0.0, 3.0);
	glVertex3f(hx, hy, hz);
	glEnd();	
}


void print_maze() 
{
	// Prints array for debugging
	for (int i = 0; i < rows; ++i)
	{
		for ( int j = 0; j < cols; ++j)
		{
			cout << maze[i][j];
		}
	}
}


void display() 
{
	// Incrementally rotate objects
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
   	glTranslatef(xpos / 500.0, ypos / 500.0, zpos / 500.0);
   	glRotatef(xangle, 1.0, 0.0, 0.0);
   	glRotatef(yangle, 0.0, 1.0, 0.0);
	glRotatef(zangle, 0.0, 0.0, 1.0);

	// Draw Objects
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if (maze[i][j] == 'r')
			{
				// use rock texture
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, rock_texture);
				init_rock(rock, texture, xdim, ydim);
				// rock_texture;
				init_block(i, j, 0, i+1, j+1, 1);
			}

			else if (maze[i][j] == 'b')
			{
				//use brick textureee
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, brick_texture);
				init_brick(brick, texture, xdim, ydim);
				init_block(i, j, 0, i+1, j+1, 1);
			}

			else if (maze[i][j] == 'w')
			{
				// use wood texture
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, wood_texture);
				init_wood(wood, texture, xdim, ydim);
				init_block(i, j, 0, i+1, j+1, 1);
			}

			else if (maze[i][j] == ' ')
			{
				// use grass texture
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, grass_texture);
				init_grass(grass, texture, xdim, ydim);
				init_block(i, j, 0, i+1, j+1, 1);
			}

			// else 
			// {
			// 	cout << "Cannot map this texure" << endl;
			// }

		}
	}
	glFlush();
}


void init() 
{
	// Init view
   	glClearColor(0.0, 0.0, 0.0, 1.0);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(-30.0, 30.0, -30.0, 30.0, -30.0, 30.0);
   	glEnable(GL_DEPTH_TEST);
	
	// Init Texture
	read("maze.txt");
	init_rock((char *)"textures/rock.jpg", rock_texture, xdim, ydim);
	init_brick((char *)"textures/brick.jpg", brick_texture, xdim, ydim);
	init_wood((char *)"textures/wood.jpg", wood_texture, xdim, ydim);
	init_grass((char *)"textures/grass.jpg", grass_texture, xdim, ydim);
	glEnable(GL_TEXTURE_2D);
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, rock_texture);
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, brick_texture);
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, wood_texture);
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, grass_texture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}


void keyboard(unsigned char key, int x, int y)
{
   // Determine if we are in ROTATE or TRANSLATE mode
   if ((key == 'r') || (key == 'R'))
   {
      printf("Type x y z to decrease or X Y Z to increase ROTATION angles.\n");
      mode = ROTATE;
   }
   else if ((key == 't') || (key == 'T'))
   {
      printf("Type x y z to decrease or X Y Z to increase TRANSLATION distance.\n");
      mode = TRANSLATE;
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
}


int main (int argc, char *argv[]) 
{

    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(250, 250);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutCreateWindow("Maze");
    glutDisplayFunc(display);
    // read("maze.txt");
    // print_maze();
    glutKeyboardFunc(keyboard);
    init();
    // init_surface(-1.0, 1.0, -1.0, 1.0, -1, 0, -1, 0, 0, 0);
    // print_menu();
    glutMainLoop();
    return 0;
}


