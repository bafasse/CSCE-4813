#include "Shape.h"

//============================================================
bool solve_quadratic(double a, double b, double c, 
   double & r1, double & r2)
{
   double desc = b * b - 4 * a * c;
   if (desc < 0) return false;
   double sqrt_desc = sqrt(desc);
   r1 = (-b - sqrt_desc) / (2 * a);
   r2 = (-b + sqrt_desc) / (2 * a);
   return true;
}

//============================================================
bool intersect_cone(Point3 p, Vector3 dir, 
   double & t1, double & t2, Point3 & hit_pt, Vector3 & hit_normal)
{
   t1 = t2 = DBL_MAX;
   Vector3 n(0.0, 1.0, 0.0);
   Point3 g(0.0, 0.5, 0.0);
   // double h = 0.5;
   double r = 0.5;
   Vector3 a = p-g;
   Vector3 b = dir;
   Vector3 c = (a*n)*n;
   Vector3 d = (dir*n)*n;
   double e = a*n;
   double f = dir*n;
   double A = (b-d)*(b-d) - r*r*f*f;
   double B = 2*(a*b - a*d - b*c + c*d) - r*r*2*e*f;
   double C = (a-c)*(a-c) - r*r*e*e;
   double descriminant = B*B - 4*A*C;

   if (descriminant >= 0)
   {
      // Intersect with side
      double t_side = (-B - sqrt(descriminant))/(2*A);
      if (t_side > 0)
      {
         Point3 p_side = p+t_side*dir;
         if ((-0.5 < p_side[1]) && (p_side[1] < 0.5))
         {
            Vector3 n_side = (p_side-g) - ((p_side-g)*n)*n;
            n_side.normalize();
            Vector3 t = (g-p_side);
            t.normalize();
            n_side = n_side - (t*n_side)*t;
            n_side.normalize();
            t1 = t_side;
            hit_pt = p_side;
            hit_normal = n_side;
         }
      }
   }

   if (dir*n != 0)
   {
      // Intersect with bottom
      double t_bot = (g-p-n)*n/(dir*n);
      if (t_bot > 0)
      {
         Point3 p_bot = p+t_bot*dir;
         Point3 p_center(0, -0.5, 0);
         double dist2 = p_bot.distanceToSquared(p_center);
         if ((dist2 < 0.25) && (t_bot < t1))
         {
            t1 = t_bot;
            hit_pt = p_bot;
            hit_normal = -n;
         }
      }
   }

   return (t1 < DBL_MAX);
}

//============================================================
bool intersect_cube(Point3 pt, Vector3 dir, 
   double & t1, double & t2, Point3 & hit_pt, Vector3 & hit_normal)
{
   t1 = t2 = DBL_MAX;

   // Intersect top
   Vector3 n_top(0, 1.0, 0);
   Point3 g_top(0, 0.5, 0);
   if (dir * n_top != 0)
   {
      double t_top = ((g_top-pt) * n_top) / (dir * n_top);
      if (t_top > 0)
      {
         Point3 p_top = pt + t_top*dir;
         if ((-0.5 <= p_top[0]) && (p_top[0] < 0.5) && 
            (-0.5 <= p_top[2]) && (p_top[2] < 0.5) &&
            (t_top < t1))
         {
            t1 = t_top;
            hit_pt = p_top;
            hit_normal = n_top;
         }
      }
   }

   // Intersect bot
   Vector3 n_bot(0, -1.0, 0);
   Point3 g_bot(0, -0.5, 0);
   if (dir * n_bot != 0)
   {
      double t_bot = ((g_bot-pt) * n_bot) / (dir * n_bot);
      if (t_bot > 0)
      {
         Point3 p_bot = pt + t_bot*dir;
         if ((-0.5 <= p_bot[0]) && (p_bot[0] < 0.5) && 
            (-0.5 <= p_bot[2]) && (p_bot[2] < 0.5) &&
            (t_bot < t1))
         {
            t1 = t_bot;
            hit_pt = p_bot;
            hit_normal = n_bot;
         }
      }
   }

   // Intersect left
   Vector3 n_left(-1.0, 0, 0);
   Point3 g_left(-0.5, 0, 0);
   if (dir * n_left != 0)
   {
      double t_left = ((g_left-pt) * n_left) / (dir * n_left);
      if (t_left > 0)
      {
         Point3 p_left = pt + t_left*dir;
         if ((-0.5 <= p_left[1]) && (p_left[1] < 0.5) && 
            (-0.5 <= p_left[2]) && (p_left[2] < 0.5) &&
            (t_left < t1))
         {
            t1 = t_left;
            hit_pt = p_left;
            hit_normal = n_left;
         }
      }
   }

   // Intersect right
   Vector3 n_right(1.0, 0, 0);
   Point3 g_right(0.5, 0, 0);
   if (dir * n_right != 0)
   {
      double t_right = ((g_right-pt) * n_right) / (dir * n_right);
      if (t_right > 0)
      {
         Point3 p_right = pt + t_right*dir;
         if ((-0.5 <= p_right[1]) && (p_right[1] < 0.5) && 
            (-0.5 <= p_right[2]) && (p_right[2] < 0.5) &&
            (t_right < t1))
         {
            t1 = t_right;
            hit_pt = p_right;
            hit_normal = n_right;
         }
      }
   }

   // Intersect front
   Vector3 n_front(0, 0, 1.0);
   Point3 g_front(0, 0, 0.5);
   if (dir * n_front != 0)
   {
      double t_front = ((g_front-pt) * n_front) / (dir * n_front);
      if (t_front > 0)
      {
         Point3 p_front = pt + t_front*dir;
         if ((-0.5 <= p_front[0]) && (p_front[0] < 0.5) && 
            (-0.5 <= p_front[1]) && (p_front[1] < 0.5) &&
            (t_front < t1))
         {
            t1 = t_front;
            hit_pt = p_front;
            hit_normal = n_front;
         }
      }
   }

   // Intersect back
   Vector3 n_back(0, 0, -1.0);
   Point3 g_back(0, 0, -0.5);
   if (dir * n_back != 0)
   {
      double t_back = ((g_back-pt) * n_back) / (dir * n_back);
      if (t_back > 0)
      {
         Point3 p_back = pt + t_back*dir;
         if ((-0.5 <= p_back[0]) && (p_back[0] < 0.5) && 
            (-0.5 <= p_back[1]) && (p_back[1] < 0.5) &&
            (t_back < t1))
         {
            t1 = t_back;
            hit_pt = p_back;
            hit_normal = n_back;
         }
      }
   }

   return (t1 < DBL_MAX);
}

//============================================================
bool intersect_cylinder(Point3 p, Vector3 dir, 
   double & t1, double & t2, Point3 & hit_pt, Vector3 & hit_normal)
{
   t1 = t2 = DBL_MAX;
   Vector3 n(0.0, 1.0, 0.0);
   Point3 g(0.0, 0.0, 0.0);
   double h = 0.5;
   double r = 0.5;
   Vector3 a = p-g;
   Vector3 b = dir;
   Vector3 c = (a*n)*n;
   Vector3 d = (dir*n)*n;
   double A = (b-d)*(b-d);
   double B = 2*(a*b - a*d - b*c + c*d);
   double C = (a-c)*(a-c) - r*r;
   double descriminant = B*B - 4*A*C;

   if (descriminant >= 0)
   {
      // Intersect with side 
      double t_side = (-B - sqrt(descriminant))/(2*A);
      if (t_side > 0)
      {
         Point3 p_side = p+t_side*dir;
         if ((-0.5 < p_side[1]) && (p_side[1] < 0.5))
         {
            Vector3 n_side = (p_side-g) - ((p_side-g)*n)*n;
            n_side.normalize();
            t1 = t_side;
            hit_pt = p_side;
            hit_normal = n_side;
         }
      }
   }

   if (dir*n != 0)
   {
      // Intersect with top 
      double t_top = (g-p+h*n)*n/(dir*n);
      if (t_top > 0)
      {
         Point3 p_top = p+t_top*dir;
         Point3 p_center(0, 0.5, 0);
         double dist2 = p_top.distanceToSquared(p_center);
         if ((dist2 < 0.25) && (t_top < t1))
         {
            t1 = t_top;
            hit_pt = p_top;
            hit_normal = n;
         }
      }

      // Intersect with bottom 
      double t_bot = (g-p-h*n)*n/(dir*n);
      if (t_bot > 0)
      {
         Point3 p_bot = p+t_bot*dir;
         Point3 p_center(0, -0.5, 0);
         double dist2 = p_bot.distanceToSquared(p_center);
         if ((dist2 < 0.25) && (t_bot < t1))
         {
            t1 = t_bot;
            hit_pt = p_bot;
            hit_normal = -n;
         }
      }
   }
   return (t1 < DBL_MAX);
}

//============================================================
bool intersect_sphere(Point3 pt, Vector3 dir, 
   double & t1, double & t2, Point3 & hit_pt, Vector3 & hit_normal)
{
   Point3 center(0,0,0);
   double radius = 0.5;
   Vector3 vpt = pt - center;
   double a = dir * dir;
   double b = 2 * vpt * dir;
   double c = vpt * vpt - radius * radius;
   bool hit = solve_quadratic(a, b, c, t1, t2);
   if (hit)
   {
      hit_pt = pt + t1 * dir;
      hit_normal = hit_pt - center;
      hit_normal.normalize();
   }
   return hit;
}

