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

const int row = 20;
const int col = 20;
char maze[row][col];


int read (string file) 
{
  string line;
  ifstream myfile (file);
  myfile >> noskipws;
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
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
    }
    myfile.close();

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

  else cout << "Unable to open file"; 

  return 0;
}

int main (int argc, char *argv[]) 
{
    read("maze.txt");
}


