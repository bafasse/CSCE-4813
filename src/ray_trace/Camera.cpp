#include "Camera.h"

Camera::Camera()
{
   eye = Point3(0,0,0);
   look = Vector3(0,0,-1);
   focus = Point3(0,0,-1);
   up = Vector3(0,1,0);
   zoom=90;
   aspect=1;
   near=0.01;
   far=1;
}

Matrix4 Camera::calculate_Sxy()
{
   Matrix4 Sxy;
   float sx = tan(M_PI / 2 - aspect * zoom * M_PI / 360);
   float sy = tan(M_PI / 2 - zoom * M_PI / 360);
   Sxy = Sxy.scaling(sx, sy, 1);
   return Sxy;
}

Matrix4 Camera::calculate_Sxy_Inv()
{
   Matrix4 Sxy_Inv;
   float sx = tan(M_PI / 2 - aspect * zoom * M_PI / 360);
   float sy = tan(M_PI / 2 - zoom * M_PI / 360);
   Sxy_Inv = Sxy_Inv.scaling(1/sx, 1/sy, 1);
   return Sxy_Inv;
}

Matrix4 Camera::calculate_Sxyz()
{
   Matrix4 Sxyz;
   float scale = 1/far;
   Sxyz = Sxyz.scaling(scale, scale, scale);
   return Sxyz;
}

Matrix4 Camera::calculate_Sxyz_Inv()
{
   Matrix4 Sxyz_Inv;
   float scale = 1/far;
   Sxyz_Inv = Sxyz_Inv.scaling(1/scale, 1/scale, 1/scale);
   return Sxyz_Inv;
}

Matrix4 Camera::calculate_R()
{
   Matrix4 R;
   Vector3 f = focus - eye;
   f.normalize();
   Vector3 u = up;
   u.normalize();
   Vector3 s = f ^ u;
   u = s ^ f;
   R = Matrix4(s, u, -f);
   return R;
}

Matrix4 Camera::calculate_R_Inv()
{
   Matrix4 R_Inv;
   Vector3 f = focus - eye;
   f.normalize();
   Vector3 u = up;
   u.normalize();
   Vector3 s = f ^ u;
   u = s ^ f;
   R_Inv = Matrix4(s, u, -f);
   R_Inv = R_Inv.transpose();
   return R_Inv;
}

Matrix4 Camera::calculate_T()
{
   Matrix4 T;
   T = T.translation(Point3(0,0,0)-eye);
   return T;
}

Matrix4 Camera::calculate_T_Inv()
{
   Matrix4 T_Inv;
   T_Inv = T_Inv.translation(eye);
   return T_Inv;
}

Matrix4 Camera::calculate_W2C()
{
   Matrix4 W2C;
   Matrix4 Sxy = calculate_Sxy();
   Matrix4 Sxyz = calculate_Sxyz();
   Matrix4 R = calculate_R();
   Matrix4 T = calculate_T();
   W2C = Sxyz * Sxy * R * T;
   return W2C;
}

Matrix4 Camera::calculate_C2W()
{
   Matrix4 C2W;
   Matrix4 Sxy_Inv = calculate_Sxy_Inv();
   Matrix4 Sxyz_Inv = calculate_Sxyz_Inv();
   Matrix4 R_Inv = calculate_R_Inv();
   Matrix4 T_Inv = calculate_T_Inv();
   C2W = T_Inv * R_Inv * Sxy_Inv * Sxyz_Inv;
   return C2W;
}

