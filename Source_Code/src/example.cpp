//---------------------------------------
// Program: example.cpp
// Purpose: To demonstrate image processing classes.
// Author:  John Gauch
//---------------------------------------
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "libim/im_color.h"
using namespace std;

//---------------------------------------
// Main program
//---------------------------------------
float diff(im_color &image1, im_color &image2)
{
   // Check image sizes
   if ((image1.R.Xdim != image2.R.Xdim) ||
   (image1.R.Ydim != image2.R.Ydim))
   {
      cout << "Error: Images not the same size\n";
      return 0;
   }

   // Calculate sum absolute difference
   int difference = 0;
   for (int y = 0; y<image1.R.Ydim; y++)
   for (int x = 0; x<image1.R.Xdim; x++)
   {
      difference += abs(image1.R.Data2D[y][x] - image2.R.Data2D[y][x]);
      difference += abs(image1.G.Data2D[y][x] - image2.G.Data2D[y][x]);
      difference += abs(image1.B.Data2D[y][x] - image2.B.Data2D[y][x]);
   }

   // Return average difference
   return difference / (3*image1.R.Xdim*image1.R.Ydim);
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
   if (argc == 3)
   {
      // Read input images
      cout << "Reading image "  << argv[1] << endl;
      im_color image1;
      image1.ReadJpg(argv[1]);
      cout << "Reading image "  << argv[2] << endl;
      im_color image2;
      image2.ReadJpg(argv[2]);

      // Print average difference
      cout << "Average difference " << diff(image1, image2) << endl;
      return 0;
   }
}
