main.cpp                                                                                            0000664 0001750 0001750 00000030353 13455245573 012323  0                                                                                                    ustar   bafasse                         bafasse                                                                                                                                                                                                                #include <math.h>
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

#define PLAYER 0
#define MAZE 1
int rows = 21;
int cols = 21;
int startrow = 0;
int startcol  = 0;
unsigned char maze[50][50];
int xangle = 10;
int yangle = 10;
int zangle = 100;
int xpos = 0;
int ypos = 0;
int zpos = 0;
int player_row, player_col;
int mode = PLAYER;

// unsigned char *texture;
int xdim, ydim;
char *brick = "textures/brick.jpg";
char *rock = "textures/rock.jpg";
char *wood = "textures/wood.jpg";
char *grass = "textures/grass.jpg";
char *player = "textures/player.jpg";
unsigned char *rock_texture;
unsigned char *brick_texture;
unsigned char *wood_texture;
unsigned char *grass_texture;
unsigned char *player_texture;

unsigned char brick_array[1];
unsigned char rock_array[1];
unsigned char wood_array[1];
unsigned char grass_array[1];


void read_maze() 
{
    string line;
    ifstream myfile ("maze.txt");
	string junk;

    if (myfile.is_open())
    {
            // cout << line << '\n';

            // Reads in maze to array
			myfile >> rows >> cols >> startrow >> startcol;
			cout << rows << ' ' << cols << endl;
			cout << startrow << ' ' << startcol << endl;
			getline(myfile, junk);
			myfile >> noskipws;
            for (int i = 0; i < rows; ++i)
            {
                for ( int j = 0; j < cols; ++j)
                {
                    myfile >> maze[i][j];
                }
                getline(myfile, junk);
            }
        myfile.close();
    }

    else cout << "Unable to open file"; 

    // return 0;
}


void init_texture(char *name, unsigned char *&texture, int &xdim, int &ydim)
{
   // Read jpg image
   im_color image;
   image.ReadJpg(name);
   printf("Reading image %s\n", name);
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

void draw_cube(float midx, float midy, float midz, float size)
{
   // Define 8 vertices
   float ax = midx - size / 2;
   float ay = midy - size / 2;
   float az = midz + size / 2;
   float bx = midx + size / 2;
   float by = midy - size / 2;
   float bz = midz + size / 2;
   float cx = midx + size / 2;
   float cy = midy + size / 2;
   float cz = midz + size / 2;
   float dx = midx - size / 2;
   float dy = midy + size / 2;
   float dz = midz + size / 2;
   float ex = midx - size / 2;
   float ey = midy - size / 2;
   float ez = midz - size / 2;
   float fx = midx + size / 2;
   float fy = midy - size / 2;
   float fz = midz - size / 2;
   float gx = midx + size / 2;
   float gy = midy + size / 2;
   float gz = midz - size / 2;
   float hx = midx - size / 2;
   float hy = midy + size / 2;
   float hz = midz - size / 2;

   // Draw 6 faces
   glBegin(GL_POLYGON);
   glVertex3f(ax, ay, az);
   glVertex3f(bx, by, bz);
   glVertex3f(cx, cy, cz);
   glVertex3f(dx, dy, dz);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex3f(ax, ay, az);
   glVertex3f(dx, dy, dz);
   glVertex3f(hx, hy, hz);
   glVertex3f(ex, ey, ez);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex3f(ax, ay, az);
   glVertex3f(ex, ey, ez);
   glVertex3f(fx, fy, fz);
   glVertex3f(bx, by, bz);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex3f(gx, gy, gz);
   glVertex3f(fx, fy, fz);
   glVertex3f(ex, ey, ez);
   glVertex3f(hx, hy, hz);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex3f(gx, gy, gz);
   glVertex3f(cx, cy, cz);
   glVertex3f(bx, by, bz);
   glVertex3f(fx, fy, fz);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex3f(gx, gy, gz);
   glVertex3f(hx, hy, hz);
   glVertex3f(dx, dy, dz);
   glVertex3f(cx, cy, cz);
   glEnd();
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


// void display_john() 
// {
// 	// Incrementally rotate objects
// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    	glMatrixMode(GL_MODELVIEW);
//    	glLoadIdentity();
//    	glTranslatef(xpos / 500.0, ypos / 500.0, zpos / 500.0);
//    	glRotatef(xangle, 1.0, 0.0, 0.0);
//    	glRotatef(yangle, 0.0, 1.0, 0.0);
// 	glRotatef(zangle, 0.0, 0.0, 1.0);

// 	// init_rock(rock, rock_texture, xdim, ydim);
// 	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, rock_texture);
	
// 	init_block(0, 0, 0, 1, 1, 1);
// 	glFlush();

// 	// Draw Obje
// }

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
	int k = -9;
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, player_texture);
	// init_block(0, 0, 0, 1, 1, 1);

	// Draw Objects
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if (maze[i][j] == 'r')
			{
				// use rock texture
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, rock_texture);
				// init_texture(rock, rock_texture, xdim, ydim);
				// rock_texture;
				init_block(i + k, j + k, 0+ k, i+1 + k, j+1 + k, 1 + k);
			}

			else if (maze[i][j] == 'b')
			{
				//use brick textureee
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, brick_texture);
				// init_brick(brick, texture, xdim, ydim);
				init_block(i + k, j + k, 0+ k, i+1 + k, j+1 + k, 1 + k);
			}

			else if (maze[i][j] == 'w')
			{
				// use wood texture
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, wood_texture);
				// init_wood(wood, texture, xdim, ydim);
				init_block(i + k, j + k, 0+ k, i+1 + k, j+1 + k, 1 + k);
			}

			else if (maze[i][j] == ' ')
			{
				// use grass texture
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, grass_texture);
				// init_grass(grass, texture, xdim, ydim);
				init_block(i + k, j + k, 0+ k, i+1 + k, j+1 + k, 1 + k);
			}

			else 
			{
				cout << "Cannot map this texure" << endl;
			}

		}
	}

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if(maze[i][j] == ' ')
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, player_texture);
				init_block(0,0,0,1,1,1);
				// draw_cube(8,10,0,1);
			}
		}
	}
	glFlush();
}


void init() 
{
	 // Init maze
   read_maze();
   float radius = sqrt(rows*rows + cols*cols)/2;

   // Init view
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-radius, radius, -radius, radius, -radius, radius);
   glEnable(GL_DEPTH_TEST);

   // Init texture
   init_texture(brick, brick_texture, xdim, ydim);
   // init_texture((char *)"fire.jpg", fire_texture, xdim, ydim);
   init_texture(grass, grass_texture, xdim, ydim);
   init_texture(rock, rock_texture, xdim, ydim);
   init_texture(wood, wood_texture, xdim, ydim);
   init_texture(player, player_texture, xdim, ydim);
   glEnable(GL_TEXTURE_2D);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, rock_texture);
}


void keyboard(unsigned char key, int x, int y)
{
   // Determine if we are in ROTATE or TRANSLATE mode
   if ((key == 'r') || (key == 'R'))
   {
      printf("Type x y z to decrease or X Y Z to increase ROTATION angles.\n");
      mode = PLAYER;
   }
   else if ((key == 't') || (key == 'T'))
   {
      printf("Type x y z to decrease or X Y Z to increase TRANSLATION distance.\n");
      mode = MAZE;
   }

   // Handle ROTATE
   if (mode == MAZE)
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
   if (mode == PLAYER)
   {
      if (key == 'x')
	 player_row -= 5;
      else if (key == 'y')
	 player_col -= 5;
    //   else if (key == 'z')
	//  player_zpos -= 5;
      else if (key == 'X')
	 player_row += 5;
      else if (key == 'Y')
	 player_col += 5;
    //   else if (key == 'Z')
	//  player_zpos += 5;
      glutPostRedisplay();
   }
}


void print_menu()
{
	printf("\n");
	printf("Keyboard commands:\n");
	// printf("   '0' - switch to LIGHT0\n");
	// printf("   '1' - switch to LIGHT1\n");
	// printf("   '2' - switch to Rotate Mode\n");
	// printf("\n");
	printf("   'x' - rotate x-axis -5 degrees\n");
	printf("   'X' - rotate x-axis +5 degrees\n");
	printf("   'y' - rotate y-axis -5 degrees\n");
	printf("   'Y' - rotate y-axis +5 degrees\n");
	printf("   'z' - rotate z-axis -5 degrees\n");
	printf("   'Z' - rotate z-axis +5 degrees\n");
	// printf("\n");
	printf("    Use the WASD keys to move the player around");
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
	print_menu();
    // init_surface(-1.0, 1.0, -1.0, 1.0, -1, 0, -1, 0, 0, 0);
    // print_menu();
    glutMainLoop();
    return 0;
}


                                                                                                                                                                                                                                                                                     hw5_report.docx                                                                                     0000664 0001750 0001750 00000022001 13455247565 013642  0                                                                                                    ustar   bafasse                         bafasse                                                                                                                                                                                                                PK  x�N               _rels/.rels���J1�{�b�{w�UDd���ЛH}�����LH�Z��P
�PV�3���#����z�������a� �u����M�h_h��D��b��N�
F�����H^�#�r�s�Z�1�y��i�0��n�Ym����+�v���׍�D[-'Z�T��8ʥ\��D�e�\����K3�e��� �{g���S�K.:
Kv��c��\SdY���D������i����ɢ=�ϚE����}PK�r�D�   �  PK  x�N               docProps/custom.xml��[o�0���+H��S ����.�x��J"=��nd�_��jɦ��z��_���V9'�t)x��Dd%�G`�Y�c�h�y�+�ij��,~
_��T��j���@a��B�IA�=���N.��N��</	M92��Br�F0W^q��MO��L�&��mjiyqx��N�L�E�3�4P���I�z�[���d�1B��OV���8�9��cf;�K�k��"OfZ�wmT�zȎޖB����w�D0�y�C�����,[��\0�X?$Ǡ�a/zM�QYi���m붸�.�t��UU�N
��4k�oBT����x؉_�VnD�}�t�I�W4���Wa�U�w~���w��PKZ܋g\  3  PK  x�N               docProps/core.xml}R]O�0}�W,}�ڍi�a#Q�����Ʒ�]��uM[�����&*���sN���xr��`ڈZf(�
@�r���bQ`,�+k	:�A��j�嵆g]+�V�	��4��m�Uc�7P19�t���.�k��dk�	!7��
f�����ɲཥ��1(8�*���8��ւ���s���=*�(��^}0����h?h����Ξ�ͨ��~UP>>5B�f��m�u����~1EyB�4$qH�E�P2������ް�k�?�<�-�x]{I�k���fސ? ��L��n�9�p9o$=�Z2cg��+���y\��ު��p���a|�K4��4�5�����)ڧ�k�}� nۑ���V�Z�����PKp��s  �  PK  x�N               docProps/app.xml��Mo� ����!I׏U���S�MZ��V1p�Ъ����弛��~^��չm�X'��Q'(ŵ���Ѯx/P�<S�5ZA�:phE�ț����@P.G��f���5���AVA)�m����.K��I�c��,If�� 16=݈˓�/Th~9��(:x�К�y�/��&ڷ�URhϚB�@�i��Y�H�|x��_^�vx��4�F[�����bv��G��C��7p��d�x��ga�U�hp�d��pt��n!���2��nh:_�	�^���0 Y:φm)�YVYf�@�\\��ltk���N��O�]��hm�r�����%�_PK��RK  :  PK  x�N               word/_rels/document.xml.rels�R�
�0��a�6���4�"�W����$$���T����g6;3L6]]������hIC�L��J�>ߌ��F�[Iቯ�Y��^@Md��{Uc'}d,�0)��$�*n�:�
�$����5 ��d�B��	��j�mS��µQ�5}����-��(]�$�������dH��h���w��+�t��(�e��'�+�l�v{��L�F)�8��PKvd�m�   �  PK  x�N               word/theme/theme1.xml�YMo�6��W���R'�SĎ�nm��q;�HK�Ć�N����;��n;�
��.ݯ��a������L�t��֡�����~����^;
: BR���劅H�r�F~˺;�]jZ�6?��7T@B� �ܲ��ۖ.Lcy��$�w#.B�`(|����̮U*kv�id���e���K� QimN�w|DJ&.{njQ�H��~5�''��:��e��ȑ��R���UI�,{�]1�DV���\.���R9��j��~e��_��/��n�[-�� �iu��5���N�=.��T�J��������v�Y/��3|c߬�5�j%|c�w�oou:k%�3ï-�{W��e|

���I=���g7��&�����l��2�H-�?����X��ILF�\3:41�7��dS�\�Jl!�
���Q�aE� �_����3t����ß�=:~��A��|]��w������o_=�Ҍ�:��?���/�@�_~����O_~���?6�����D��!��3 Cq6�A��.��G8�1��*(�oO0�\��3xO ����J�b��x3K��Y�cL7[zƑo6.�:����vg���q�LM*;)��ˠ��'Q(y��	1�ݧ����
.�H���15�d@��,t��P���A�w)7;�P�3��mrPFª�̤��R��¡�c2y�����D���K��	��)M2wĤ��M�s�w�$,#���&�-̹����� ���g:�C�-��.WF'xy�$c�����%�lk�.�s�$o�"���4:��C`c|�t��'�#"ނ$�V�<�.�͓n���������.�6O��)�]��e�yU��q���S}���2��&�ܒ)+Kp���d:H��y�cn���N����c��� �`��Z�e�ڗ(���R��]�B��3� ��e�u�bX�IG�����_y3c�����c��h�ֲ	���_]�e��c0#^��L��,�`���F��aZ��Z�G��ɉ�Ire!���jbQy�����8nY#8�c�>��f~Բ\�x�Z��x��UՊ�,���XH��e�I���_{D3�kN#���` �ռ�7����|i�hD\�df6���"b/�ѐ�E�ߍ��<*��kӁ��n�W^��ژ�z%_3��λ���>��υ�Hs�^��9C�_`(λJҹp�{�Uvq�Qң-�p`�8�nO�����,��%Ē��_����2����S	
L�AȮ��<EY��o�SE9���8�?$��ջ��o�`�&y"R�|�l��������8��33�8����H_�
��̅U6`�\�q�Y���o�1�P��M��f���C�Q��#h�K�|��C�����NA�%��ȳ�����d�l���v�vNN���Dm���~4��`{�9c���F�îHro�?2�QB��)���OF�zGӲ�e4�U������$�B�~�`��m"�p�t�Bbz�+��[�I�Y��Y��,2Ţ7I�
ΛSf��US�B�Α2utr��L٦�#GJ���g&�_{ֲ�PK' *�  u  PK  x�N               word/settings.xml�R�n�0��+"�!�%D@\"��R��x�lodoH��w@E������ٙ�x:��&ڃ]*F�DD�
T�mS���"
$����� 泛i3	@�S!�.L�T숪I�bV�!V�W�����q�^U�����$����N�x��Fͤ_�#�s���k�݀��@`3t���Rֆ�r�V��K����	S��$}��^�sҲ�cUo��ԮP��V��/V�4dH�e�蝈3�����'��z���ȩ5�y��N-�@�7�tW(�K �����X�d �����)|Aʌ�V�{�ONq�גŗqC�'|�=o?n�w ��A�T|���+m�b�Ӟ�}PK~�`+Y  �  PK  x�N               word/fontTable.xml�RAN�0��
�w����qB=�򀍻i,���k�{ܴ�����ٙݱ��/gE����B�g�H��
��{���#��',d�,׫�e�W�"��N�w��clr�X��g�AJX僃���:�M�����j�eʁ!y�	Sd|U�/^:�x	h!��6��y:��.�3Yl���]C`<rZ���2��>p���j�И��K��`��x�����w���^�[{=%ʸ��Z��Z�����b0��
6nz�����l~�����5���~� �c)�e��׼ʔ~}���PKР>n.  7  PK  x�N               word/document.xml�ZQs5~�Wh�9��Jǃ˴�xJ�����u�;�t#��'��_·����Hh��>K���J��[�?��M��Z:��YdǓYƤ6W�\d�^�|�$c>p�sm�\d[�ϟ~��f�[������"k��{Qɚ�G��z[�G��s[J��+�F�EV��̧�n��6Ҡ����?]9MCκ��'��㩓���+��^����_׺���d֍uy㬐�#�N��\�A�����aDs��s�7�)�r�:w�[*3&0��^�}ǳ=}o�N[y7m��m�^[-n�m��U�P���Ji���Qǧw�j?f憐�O-���X�W�Y�=�YX�|K�M�8w��"l�d����E����ٔz~}����.�:6�}wj�Ї������j��k�a�ؚccn����Tό?�'^�O�so��'Y���_o�����Ζ��5b�����}#���$��yd����C�釈�h�[�^m��?��J���{y�u����:;y|��a�Ąt��P�"p0R�lF*���?��Ϲ�����_�~a�Ar�N��P��H5��Aq��-�E�"���;� �G�=��Rp�e׶3oԺ����m?R�x�\V���kf*��U�&���,X֚�x8��Zr˂|Z'Y͛ix�Үa�4-�т:ɚ���h�4�1R��O�{ɾ���X۵�j���2��[�3�����P�,ݩ�V�H��fw�{�&��`U�&Mā����|�w��` �ú��P1><g���]��?�k�7>���g���˯�q�)�*���Pt� ��	�j�K�V��U&��֒�<@Cp� ������2OO�9��G�UA�)����1��亴N�*ai��uI`��	k"s��QMT�@���R-�$/��X�[l���^�x�G@��z�'9�d��H�X��LR�|�Q4W9q�|v�b�L�D] cX�lMO	׈Έ8�W�-�N�B��;.P��Ęv�JWsU���e QH�ȈZĎ��F������Rcn�����J& ����o��)quĜ�ύ����;˒�w38a(\b���4�F��4^%�)�	�{EiLOJiT��	�T!�/�uB(�$R�5�VF8��lvq��u���b���Q�Q����\�| �y&�R�&��0�^�Ba[2�9���?��mP����pޟ�@W�s� �Y�(�Zf�B%��P�E�M-t���FI��1G��"��H� ������7G���Q��B�ii�x�SV饁f���e��S������z'`ޯ�����#��Q�����t ��5��R�\��L�1�!^�_�k�QQ>,(�(Ne="��c��X�6�F/��m��)��]���GV�ʶe|�-GjK��v%���Q ��*��UXD�.H�m\2;��Y2L�KK�᪢�݂�,��N�-��K��9X"�T	T����)���E�{�
��9�>d���R����E�[���k�qĿ�65"h9���b�oJ#$�V�K�#BB����a��늷`j�*�;����p͛k�fW4)X�����	{��I87�l�#�b�D��Yrm���o?דx�i� ��4��k��Kѫ�c8�:,�Lhz����J�Å��d�}T�u�� ���KS^���";>99�o�*<��t�|�Z��:�̢�Se5�I	L��m[�zN����0��l��u�m�:��^��e2������3N��8w6��Δ��tq׿�r��ԝ[��)�aR[�V� u�<WA���Zŋ��f�"�q������a��wPK�$�(  �$  PK  x�N               word/styles.xmlݛ�v�6��}
�]�ȗ%�Q�ƭ�8�}��HHBM, Zv��.�G��<O�y� ���lq��Ɩ@`��`������$��R1��a�Y;(�D���^_��;
�	�I"8��T��^��bv��}BU`�su2�S���VKES��Ld��gc!S��W9ḯ�3)"��1�&�n��k���2�9 �RI��X?�D��1��3e�w��S�T�hGR"o�l��ˈf#�0}�	�4:9�p!�(1�5��/M_c��c�'Zٯ�R�_�o��;��
f'DE���IG��ДLO�Z-�D�S�H?���o_�����׿���"���̕��#eƥ��JQC/�f1[6���mY6w�kY����-I�a��*�����IUF���p�'���7<�[e�Z��ֿ�:K��O[`�)��"�S:>����<���(�>��LH3�����,Ҕ�gqLm�W�����)�׊Ƌ�O�\ޔ#�s�{�si����]D3m&�yʉ��m���9[�]s�v���V!;e��(SJ�:�c$P��(���8�����M�v7q�����M?݄L���-@ml�fc�#[����d��`�7� 㻱�[D�}m�o�WL't�}�i�+e?�$�L$ɦ�]i��|�k]�4��PK�'�n�a��4�� 5�+�
~�,^G=�v���LHD�"����~l�31��n�>g���S���{��x��s�@��M�M�놬�m���1��*4P�{�M#���;h
a������5eߎq����ڇ�5j,�݅�y���^���݁H��Ow��sDmv��s�u"q��^���4�̋ZM�6��~J���4��~V��g5��~�����2Umg5�jik	6��F`۽ŧ\h��6��~�5�����w�+��^����W@?���jpM�BG?��U�jx���M���X7!c݄�u���M�w?��?I�!I���c� �D�,$� $� $�/��)�)x�Yx�YH�AH�AH�AH�AH���(/Q�!I�!I�!I���Q�R0�R����������������������@������������@oH�oH�o��o�BoBoBoBoBoBo Ao�BoBoBop�E�!C�!O�!O�!I�!I�!I�!I�!I�!A�Q�!I�!I�!hwm��j�N�v�N5x��6~����g:�����hX��Ol�(�k!n��s���&��(6J�p�l���S��{Z{�n���Bk�r;Țuw�LE}�{��i��,^��έ9��:�מ�J�ג�>g����l ��"q��*Tն�J�FUABǺt�l�?�JY��zHr-��*�Z �ץ37�0��I�HS���e������9ṟ�_�jU��!�yU�[�U ����=ԥ�Į�κ�Uy���p?�<��NW����k�{g����R-sZ��8�o�����v��x���n{��p�FT'C��Ҥ�y�H���+?�Fc'yBd5O�Ŕ���%�L��#�jr�h�T��y,��7"6M�Eh����^]uS�,)n,.E~%�uqj�ܙ���º�����P8��Qz�����Ӻ�U����d�ʳLR��M�/�Ԥ���~�����g(+~�֚��x��ށh������M�Źߺ�]:��P��`ϥ2�jl�:QL=�n���&�ֈ�<��WajIwc�]-�f#y�s��7��2���rӵ�M��%<�M
s������Om/��9����y9X����U��[=J��gn�f���w$�*h�| Em����q.�v�G5�GBk���K�')��֪3�y'�>���PK;� �d  .B  PK  x�N               [Content_Types].xml���N�0��}��W���J��z(gd�Ij��niߞq�V����K�x���Y�䓕��%8/�.�(�47B� ϳ���Lƃ|����վ �����A1�#�q��u����
��pxE��tHC� ��J��Cr��㖋r�ܶyUfm-9�1J;uj�G���[u馲�M��K�/~&X]}H;��݊7ݒ&��'���)s�)L�/�����.�0|���/|0*�?��)K�m
%Yk�Z�$7�Go���c�h}r��,@��0Nl6������r��~B{��{cӋ�~:�ɸ�S��=��жν%������W_;��"����5�"�Iݿ����/���n���6���'PK�)?�n  N  PK   x�N�r�D�   �                   _rels/.relsPK   x�NZ܋g\  3               !  docProps/custom.xmlPK   x�Np��s  �               �  docProps/core.xmlPK   x�N��RK  :               p  docProps/app.xmlPK   x�Nvd�m�   �               �  word/_rels/document.xml.relsPK   x�N' *�  u                 word/theme/theme1.xmlPK   x�N~�`+Y  �               n  word/settings.xmlPK   x�NР>n.  7                 word/fontTable.xmlPK   x�N�$�(  �$               t  word/document.xmlPK   x�N;� �d  .B               �  word/styles.xmlPK   x�N�)?�n  N               |  [Content_Types].xmlPK      �  +!                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   