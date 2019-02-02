#ifndef _COMMON_H_
#define _COMMON_H_

#include <cassert>
#include <cfloat>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

#ifndef EPSILON
#define EPSILON 1e-16
#endif

inline bool isZero(double in_d, double in_dEps = EPSILON)
{ 
    return (in_d < in_dEps && in_d > -in_dEps) ? true : false; 
}

#endif
