#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;

// int mode;
// #define Trans           0
// #define RotX            1
// #define RotY            2
// #define RotZ            3
// #define Scale           4
// #define ProPnt          5
// // ========================
// #define ChnSthrlnd      6
// #define Accept          7
// #define Discard         8
// #define Clip            9
// // ========================
// #define Normal          10
// #define Dot             11
// #define Cross           12
// #define Diffuse         13
// #define Ideal           14
// #define Specular        15


// Geometric Operations===============================
void geoTranslation(double x, double y, double z, double Tx, double Ty, double Tz) 
{
    double px = x + Tx;
    double py = y + Ty;
    double pz = z + Tz;

    cout << endl;
    cout << "x' = " << px << endl;
    cout << "y' = " << py << endl;
    cout << "z' = " << pz << endl;
}

void geoRotateX(double theta, double x, double y, double z)
{
    double px = x;
    double py = y * cos(theta) - z * sin(theta);
    double pz = y * sin(theta) + z * cos(theta);

    cout << endl;
    cout << "x' = " << px << endl;
    cout << "y' = " << py << endl;
    cout << "z' = " << pz << endl;
}

void geoRotateY(double theta, double x, double y, double z)
{
    double px = x * cos(theta) + z * sin(theta);
    double py = y;
    double pz = ((-1) * x) * sin(theta) + z * cos(theta);

    cout << endl;
    cout << "x' = " << px << endl;
    cout << "y' = " << py << endl;
    cout << "z' = " << pz << endl;
}

void geoRotateZ(double theta, double x, double y, double z)
{
    double px = x * cos(theta) - y * sin(theta);
    double py = x * sin(theta) + y * cos(theta);
    double pz = z;

    cout << endl;
    cout << "x' = " << px << endl;
    cout << "y' = " << py << endl;
    cout << "z' = " << pz << endl;
}

void geoScale(double x, double y, double z, double Sx, double Sy, double Sz)
{
    double px = Sx * x;
    double py = Sy * y;
    double pz = Sz * z;

    cout << endl;
    cout << "x' = " << px << endl;
    cout << "y' = " << py << endl;
    cout << "z' = " << pz << endl;
}

void geoProjectPoint(double x, double y, double z, double d)
{
    // NEED HELP
    double px = x / (z/d);
    double py = y / (z/d);
    double pz = d;

    cout << endl;
    cout << "x' = " << px << endl;
    cout << "y' = " << py << endl;
    cout << "z' = " << pz << endl;
}
// ========================================================


// Clipping Operations ====================================
void cohenSutherland(double x, double y)
{
    // no Z

    // READS BINARY BACKWARDS
    bool array [4];
    int outcode = 0;

    if (x > 1)
    {
        array[0] = 1;
        array[1] = 0;
        // cout << " X Greater than 1" << endl;
    }

    else if (x < -1)
    {
        array[0] = 0;
        array[1] = 1;
        // cout << " X Less than one" << endl;
    }

    else if (x > -1 && x < 1)
    {
        array[0] = 0;
        array[1] = 0;
        // cout << " X Just right" << endl;
    }

    else
    {
        cout << "ERROR with X value" << endl;
        exit(0);
    }
    // =================================
    if (y > 1)
    {
        array[2] = 1;
        array[3] = 0;
        // cout << " Y Greater than 1" << endl;
    }
    else if (y < -1)
    {
        array[2] = 0;
        array[3] = 1;
        // cout << " Y Less than one" << endl;
    }

    else if (y > -1 && y < 1)
    {
        array[2] = 0;
        array[3] = 0;
        // cout << " Y Just right" << endl;
    }
    else
    {
        cout << "ERROR with Y value" << endl;
        exit(0);
    }

    for (int i = 0; i < 4; ++i)
    {
        if (array[i] == 1)
        {
            // for (int j = 0; j < i; ++j)
            // {
            //     // power = 1;
            //     power *= 2;
            // }
            // outcode += power;
            outcode += pow(2, i);
            // cout << "pow(2, i) = " << pow(2, i) << endl;
        }
        else if (array[i] == 0)
        {
            outcode += 0;
            // cout << "Inside 0" << endl;
        }
    }

    cout << "Outcode Value is = " << outcode << endl << endl;
}

double acceptLineSegment()
{
    return 0;
}

double discardLineSegment()
{
    return 0;
}

double clipLine()
{
    return 0;
}
// ========================================================


// Shading ================================================
void Normalize(double Ax, double Ay, double Az)
{
    // V^ = v \ |v|
    double vLength = sqrt(Ax * Ax + Ay * Ay + Az * Az);
    double Bx = Ax / vLength;
    double By = Ay / vLength;
    double Bz = Az / vLength;

    cout << endl;
    cout << "[Bx, By, Bz] = [" << Bx << ", " << By << ", " << Bz << "]" << endl;
    cout << endl;
}

double dotProduct(double Ax, double Ay, double Az, double Bx, double By, double Bz)
{
    double dot = Ax * Bx + Ay * By + Az * Bz;
    return dot;
}

void crossProduct(double Ax, double Ay, double Az, double Bx, double By, double Bz) 
{
    double Cx = Ay * Bz - Az * By;
    double Cy = Az * Bx - Az * Bz;
    double Cz = Ax * By - Ay * Bx;

    cout << endl;
    cout << "Cx = " << Cx << endl;
    cout << "Cy = " << Cy << endl;
    cout << "Cz = " << Cz << endl;
}

double diffuseTerm(double Lx, double Ly, double Lz, double Nx, double Ny, double Nz)
{
    // diffuse = n * L
    return dotProduct(Lx, Ly, Lz, Nx, Ny, Nz);

}

double idealReflection()
{
    return 0;
}

double specularTerm()
{
    // (v*r)^p
    return 0;
}
// ========================================================

void print_menu() 
{
    cout << "   '0'  - To use Geometric Translation\n";
    cout << "   '1'  - To Rotate X point\n";
    cout << "   '2'  - To Rotate Y point\n";
    cout << "   '3'  - To Rotate Z point\n";
    cout << "   '4'  - To Scale points\n";
    cout << "   '5'  - To project points onto Z=d plane\n";
    cout << "   '6'  - To use Cohen-Sutherland\n";
    cout << "   '7'  - To Accept Line Segments based on Two Outcodes\n";
    cout << "   '8'  - To Discard line Segments based on Two Outcodes\n";
    cout << "   '9'  - To Clip Line Segments based on Two Outcodes\n";
    cout << "   'a'  - To Normalize Length\n";
    cout << "   'b'  - To Calculate the Dot Product\n";
    cout << "   'c'  - To Calculate the Cross Product\n";
    cout << "   'd'  - To Calculate the Diffuse Term\n";
    cout << "   'e'  - To Calculate the Ideal Reflection\n";
    cout << "   'f'  - To Calculate the Specular Term\n";
    cout << "   'q'  - To quit\n";
    cout << "Please enter your choice: ";
}

void keyboard(unsigned char key)
{
    if (key == '0')
    {
        cout << "You have chosen Geometric Transformations" << endl << endl;
        double x, y, z;
        double Tx, Ty, Tz;
        cout << "Please enter the initial location of the point xyz" << endl;
        cout << "X = "; cin >> x;
        cout << "Y = "; cin >> y;
        cout << "Z = "; cin >> z;
        // cout << "Your input was: " << x << endl;
        cout << "Now please enter the numbers you would like to translate the xyz coordinates by" << endl;
        cout << "Tx = "; cin >> Tx;
        cout << "Ty = "; cin >> Ty;
        cout << "Tz = "; cin >> Tz;
        geoTranslation(x, y, z, Tx, Ty, Tz);
    }

    else if (key == '1')
    {
        cout << "You have chosen Rotate X Point" << endl << endl;
        double x, y, z;
        double theta;
        cout << "Please enter the initial location of the point xyz followed by the angle at which you want to rotate X" << endl;
        cout << "X = "; cin >> x;
        cout << "Y = "; cin >> y;
        cout << "Z = "; cin >> z;
        cout << "Theta = "; cin >> theta;
        geoRotateX(theta, x, y, z);
    }

    else if (key == '2')
    {
        cout << "You have chosen Rotate Y Point" << endl << endl;
        double x, y, z;
        double theta;
        cout << "Please enter the initial location of the point xyz followed by the angle at which you want to rotate Y" << endl;
        cout << "X = "; cin >> x;
        cout << "Y = "; cin >> y;
        cout << "Z = "; cin >> z;
        cout << "Theta = "; cin >> theta;
        geoRotateY(theta, x, y, z);
    }

    else if (key == '3')
    {
        cout << "You have chosen Rotate Z Point" << endl << endl;
        double x, y, z;
        double theta;
        cout << "Please enter the initial location of the point xyz followed by the angle at which you want to rotate Z" << endl;
        cout << "X = "; cin >> x;
        cout << "Y = "; cin >> y;
        cout << "Z = "; cin >> z;
        cout << "Theta = "; cin >> theta;
        geoRotateZ(theta, x, y, z);
    }

    else if (key == '4')
    {
        cout << "You have chosen Scale Points" << endl;
        double x, y, z;
        double Sx, Sy, Sz;
        cout << "Please enter the initial locations of the points xyz" << endl;
        cout << "X = "; cin >> x;
        cout << "Y = "; cin >> y;
        cout << "Z = "; cin >> z;
        cout << "Now please enter the factors by which you would like to scale xyz" << endl;
        cout << "Sx = "; cin >> Sx;
        cout << "Sy = "; cin >> Sy;
        cout << "Sz = "; cin >> Sz;
        geoScale(x, y, z, Sx, Sy, Sz);
    }

    else if (key == '5')
    {
        cout << "You have chosen project point" << endl;
        double x, y, z, d;
        cout << "Please enter the initial locations of the points xyz following by the d value" << endl;
        cout << "X = "; cin >> x;
        cout << "Y = "; cin >> y;
        cout << "Z = "; cin >> z;
        cout << "d = "; cin >> d;
        geoProjectPoint(x, y, z, d);
    }

    else if (key == '6')
    {
        cout << "You have chosen Cohen-Sutherland" << endl;
        double x, y;
        cout << "Please enter values for x and y" << endl;
        cout << "X = "; cin >> x;
        cout << "Y = "; cin >> y;
        cohenSutherland(x, y);
    }

    else if (key == '7')
    {
        cout << "This doesnt do anything right now" << endl;
        cout << "Come back later" << endl;
    }

    else if (key == '8')
    {
        cout << "This doesnt do anything right now" << endl;
        cout << "Come back later" << endl;
    }

    else if (key == '9')
    {
        cout << "This doesnt do anything right now" << endl;
        cout << "Come back later" << endl;
    }

    else if (key == 'a')
    {
        // cout << "This doesnt do anything right now" << endl;
        // cout << "Come back later" << endl;

        cout << "You have chosen Normalize" << endl;
        double Ax, Ay, Az;
        cout << "Please enter the location of the points xyz" << endl;
        cout << "Ax = "; cin >> Ax;
        cout << "Ay = "; cin >> Ay;
        cout << "Az = "; cin >> Az;
        cout << endl;
        Normalize(Ax, Ay, Az);
    }

    else if (key == 'b')
    {
        cout << "You have chosen Dot Product" << endl;
        double Ax, Ay, Az;
        double Bx, By, Bz;
        cout << "Please enter the locations of the points Ax, Ay, Az" << endl;
        cout << "Ax = "; cin >> Ax;
        cout << "Ay = "; cin >> Ay;
        cout << "Az = "; cin >> Az;
        cout << "Now please enter the locations of points Bx, By, Bz" << endl;
        cout << "Bx = "; cin >> Bx;
        cout << "By = "; cin >> By;
        cout << "Bz = "; cin >> Bz;
        cout << "The Scalar dot product is: " << dotProduct(Ax, Ay, Az, Bx, By, Bz) << endl;
    }

    else if (key == 'c')
    {
        cout << "You have chosen Cross Product" << endl;
        double Ax, Ay, Az;
        double Bx, By, Bz;
        cout << "Please enter the locations of the points Ax, Ay, Az" << endl;
        cout << "Ax = "; cin >> Ax;
        cout << "Ay = "; cin >> Ay;
        cout << "Az = "; cin >> Az;
        cout << "Now please enter the locations of points Bx, By, Bz" << endl;
        cout << "Bx = "; cin >> Bx;
        cout << "By = "; cin >> By;
        cout << "Bz = "; cin >> Bz;
        crossProduct(Ax, Ay, Az, Bx, By, Bz);
    }

    else if (key == 'd')
    {
        // cout << "This doesnt do anything right now" << endl;
        // cout << "Come back later" << endl;
        cout << "You have chosen Diffuse Term" << endl;
        double Lx, Ly, Lz;
        double Nx, Ny, Nz;
        cout << "Please enter the xyz values for N and L" << endl;
        cout << "Lx = "; cin >> Lx;
        cout << "Ly = "; cin >> Ly;
        cout << "Lz = "; cin >> Lz;
        cout << "Nx = "; cin >> Nx;
        cout << "Ny = "; cin >> Ny;
        cout << "Nz = "; cin >> Nz;
    }

    else if (key == 'e')
    {
        cout << "This doesnt do anything right now" << endl;
        cout << "Come back later" << endl;
    }

    else if (key == 'f')
    {
        cout << "This doesnt do anything right now" << endl;
        cout << "Come back later" << endl;
    }

    else if (key == 'q')
    {
        cout << "END" << endl;
    }



    else 
    {
        cout << "Please enter one ogf the numbers from the menu" << endl;
        print_menu();
    }
}


int main(int argc, char *argv[]) 
{
    bool cough = true;
    cout << cough << endl;
    unsigned char key;
    print_menu();
    cin >> key;
    cout << endl;

    while (key != 'q')
    {
        keyboard(key);
        print_menu();
        cin >> key;
        cout << endl;
    }

    return 0;
}