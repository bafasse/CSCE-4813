#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Common.h"
#include "Point3.h"
#include "Matrix4.h"
#include "Vector3.h"

class Camera
{
public:
   Camera();

   void set_eye(Point3 e) { eye = e; }
   void set_look(Vector3 l) { look = l; }
   void set_focus(Point3 f) { focus = f; }
   void set_up(Vector3 u) { up = u; }
   void set_zoom(float z) { zoom = z; }
   void set_aspect(float a) { aspect = a; }
   void set_near(float n) { near = n; }
   void set_far(float f) { far = f; }

   Point3 get_eye() { return eye; }
   Vector3 get_look() { return look; }
   Point3 get_focus() { return focus; }
   Vector3 get_up() { return up; }
   float get_zoom() { return zoom; }
   float get_aspect() { return aspect; }
   float get_near() { return near; }
   float get_far() { return far; }

   Matrix4 calculate_Sxy();
   Matrix4 calculate_Sxy_Inv();
   Matrix4 calculate_Sxyz();
   Matrix4 calculate_Sxyz_Inv();
   Matrix4 calculate_R();
   Matrix4 calculate_R_Inv();
   Matrix4 calculate_T();
   Matrix4 calculate_T_Inv();
   Matrix4 calculate_W2C();
   Matrix4 calculate_C2W();

   Point3 eye;
   Vector3 look;
   Point3 focus;
   Vector3 up;
   float zoom;
   float aspect;
   float near;
   float far;
};

#endif 
