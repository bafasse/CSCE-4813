#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "Common.h"
#include "Point3.h"
#include "Vector3.h"

bool solve_quadratic(double a, double b, double c,
   double & r1, double & r2);

bool intersect_cone(Point3 pt, Vector3 dir,
   double & t1, double & t2, Point3 & hit_pt, Vector3 & hit_normal);

bool intersect_cube(Point3 pt, Vector3 dir,
   double & t1, double & t2, Point3 & hit_pt, Vector3 & hit_normal);

bool intersect_cylinder(Point3 pt, Vector3 dir,
   double & t1, double & t2, Point3 & hit_pt, Vector3 & hit_normal);

bool intersect_sphere(Point3 pt, Vector3 dir,
   double & t1, double & t2, Point3 & hit_pt, Vector3 & hit_normal);

#endif
