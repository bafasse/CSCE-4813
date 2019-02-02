//============================================================
//  File:       render.cpp
//  Purpose:    Uses rendering to generate image of scene. 
//  Author:     John Gauch
//  Date:       Spring 2013
//============================================================
#include "Camera.h"
#include "Scene.h"
#include "Shape.h"
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "shading.cpp"

string infile;

//============================================================
void displaySubgraph(Scene & scene, string name)
{
   // Display objects in scene
   for (unsigned int i=0; i<scene.vsubgraph.size(); i++)
   if (scene.vsubgraph[i].name == name)
   {
      // Loop over trans vector
      for (unsigned int j=0; j<scene.vsubgraph[i].vtrans.size(); j++)
      {
         // Display subgraph
         Trans trans = scene.vsubgraph[i].vtrans[j];
         if (trans.subgraphName.length() > 0)
         {
            GLfloat matrix[16];
            for (int c=0; c<4; c++)
            for (int r=0; r<4; r++)
               matrix[trans.modelview.index(r,c)] = trans.modelview(r,c);
            glPushMatrix();
            glMultMatrixf(matrix);
            displaySubgraph(scene, trans.subgraphName);
            glPopMatrix();
         }

         // Display object
         else if (trans.object.shape.length() > 0)
         {
            // Apply transformation
            GLfloat matrix[16];
            for (int c=0; c<4; c++)
            for (int r=0; r<4; r++)
               matrix[trans.modelview.index(r,c)] = trans.modelview(r,c);
            glPushMatrix();
            glMultMatrixf(matrix);

            // Display object
            cout << trans.object.shape << endl;
            if (trans.object.shape == "sphere")
               glutWireSphere(0.5, 20, 20);
            else if (trans.object.shape == "cube")
               glutWireCube(1.0);
            else if (trans.object.shape == "cone")
               glutWireCone(0.5, 1.0, 20, 20);
            else if (trans.object.shape == "cylinder")
               glutWireCube(1.0);
            else
               cout << "Object " << trans.object.shape << " not found\n";
            glPopMatrix();
         }
      } 
   }
}

//============================================================
void display()
{
   // Read scene file
   Scene scene;
   scene.readScene(infile);

   // Define world to camera transformation 
   Matrix4 W2C = scene.camera.calculate_W2C();
   GLfloat matrix[16];
   for (int c=0; c<4; c++)
   for (int r=0; r<4; r++)
      matrix[W2C.index(r,c)] = W2C(r,c);
   glMatrixMode(GL_PROJECTION);
   // glFrustum(-1, 1, -1, 1, 0, 1);
   glLoadIdentity();
   glMultMatrixf(matrix);

   // Display scene
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   displaySubgraph(scene, "root");
   glFlush();
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
   if (argc == 2)
      infile = string(argv[1]);
   else
   {
      cout << "Enter name of infile: ";
      cin >> infile;
   }
   glutInit(&argc, argv);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(250, 250);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
   glutCreateWindow("John's Scene Rendering Program");
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;
}
