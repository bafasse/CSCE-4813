// ==================== Original  =============================
void keyboard(unsigned char key, int x, int y, Object &s)
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

   // add block
   else if (key == '+')
   {
      draw_cube(0.0,0.0,0.0,1.0);
      // mode = ADD;
   }

   // Handle ROTATE
   if (mode == ROTATE)
   {
      if (key == 'x')
	 object.xangle -= 5;
      else if (key == 'y')
	 object.yangle -= 5;
      else if (key == 'z')
	 object.zangle -= 5;
      else if (key == 'X')
	 object.xangle += 5;
      else if (key == 'Y')
	 object.yangle += 5;
      else if (key == 'Z')
	 object.zangle += 5;
      glutPostRedisplay();
   }

   // Handle TRANSLATE
   if (mode == TRANSLATE)
   {
      if (key == 'x')
	 object.xpos -= 5;
      else if (key == 'y')
	 object.ypos -= 5;
      else if (key == 'z')
	 object.zpos -= 5;
      else if (key == 'X')
	 object.xpos += 5;
      else if (key == 'Y')
	 object.ypos += 5;
      else if (key == 'Z')
	 object.zpos += 5;
      glutPostRedisplay();
   }

   if (mode == ADD)
   {
      draw_cube(0.0,0.0,0.0,1.0);
   }
}

void display() 
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   // This was used for larger cube
   // Change to use with smaller cube
   glTranslatef(s.xpos / 500.0, s.ypos / 500.0, s.zpos / 500.0);

   glRotatef(s.xangle, 1.0, 0.0, 0.0);
   glRotatef(s.yangle, 0.0, 1.0, 0.0);
   glRotatef(s.zangle, 0.0, 0.0, 1.0);
   blockworld(0.0,0.0,0.0,2.0);
   // Store these in fixed array
   blockworld(0.1,0.0,0.1,0.1);
   blockworld(0.0,0.2,0.1,0.1);

   glFlush();
}


// =========================  modified  =======================================


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
// Mouse callback for OpenGL
//---------------------------------------
void mouse(int button, int state, int x, int y, Object &s)
{
   // Handle mouse down
   static int xdown, ydown;
   if (state == GLUT_DOWN)
   {
      xdown = x;
      ydown = y;
   }

   // Handle ROTATE
   if ((mode == ROTATE) && (state == GLUT_UP))
   {
      object.xangle += (y - ydown);
      object.yangle -= (x - xdown);
      object.zangle = 0;
      glutPostRedisplay();
   }

   // Handle TRANSLATE
   if ((mode == TRANSLATE) && (state == GLUT_UP))
   {
      object.xpos += (x - xdown);
      object.ypos -= (y - ydown);
      glutPostRedisplay();
   }
}

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
   if (key == 'C')
      blockworld(x,y,0.1,0.1);
   
   // Change mode
   if ((key == 'f') || (key == 'F'))
      mode = 'f';
   if ((key == 'r') || (key == 'R'))
      mode = 'r';
   if ((key == 't') || (key == 'T'))
      mode = 't';


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

// ---------------------------------------
// Display geometric object
// ---------------------------------------
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