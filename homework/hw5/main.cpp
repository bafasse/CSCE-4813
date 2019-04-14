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
const int row = 21;
const int col = 21;
unsigned char maze[row][col];
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


void read (string file) 
{
    string line;
    ifstream myfile (file);
    myfile >> noskipws;
    if (myfile.is_open())
    {
            // cout << line << '\n';

            // Reads in maze to array
            for (int i = 0; i < row; ++i)
            {
                for ( int j = 0; j < col; ++j)
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

	printf("Reading image %s\n", brick);
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

void init_wood(char *wood, unsigned char *&texture, int &xdim, int &ydim)
{
	im_color image;
	image.ReadJpg(wood);

	printf("Reading image %s\n", wood);
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


void init_grass(char *grass, unsigned char *&texture, int &xdim, int &ydim)
{
	im_color image;
	image.ReadJpg(grass);

	printf("Reading image %s\n", grass);
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

void init_maze() 
{

	
}


void print_maze() 
{
    // Prints array for debugging
        for (int i = 0; i < row; ++i)
        {
            for ( int j = 0; j < col; ++j)
            {
                cout << maze[i][j];
                // cout << endl;
            }
            // cout << endl;
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
	init_maze();
	glFlush();
}


void init() 
{
	// Init view
   	glClearColor(0.0, 0.0, 0.0, 1.0);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
   	glEnable(GL_DEPTH_TEST);
	
	// Init Texture
	int xdim, ydim;
	unsigned char *texture;
	read("maze.txt");
	init_rock((char *)"textures/rock.jpg", texture, xdim, ydim);
	init_brick((char *)"textures/brick.jpg", texture, xdim, ydim);
	init_wood((char *)"textures/wood.jpg", texture, xdim, ydim);
	init_grass((char *)"textures/grass.jpg", texture, xdim, ydim);
	glEnable(GL_TEXTURE_2D);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
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
    // glutKeyboardFunc(keyboard);
    init();
    // init_surface(-1.0, 1.0, -1.0, 1.0, -1, 0, -1, 0, 0, 0);
    // print_menu();
    glutMainLoop();
    return 0;
}


