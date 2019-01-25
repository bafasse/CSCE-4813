#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Common.h"
#include "Point3.h"
#include "Vector3.h"

class Light
{
public:
   Light();

   void set_lightType(string l) { lightType = l; }
   void set_position(Point3 p) { position = p; }
   void set_color(Vector3 c) { color = c; }
   void set_function(Vector3 f) { function = f; }
   void set_direction(Vector3 d) { direction = d; }
   void set_ambientLight(Vector3 a) { ambientLight = a; }
   void set_aperture(float a) { aperture = a; }
   void set_exponent(float e) { exponent = e; }

   string get_lightType() { return lightType; }
   Point3 get_position() { return position; }
   Vector3 get_color() { return color; }
   Vector3 get_function() { return function; }
   Vector3 get_direction() { return direction; }
   Vector3 get_ambientLight() { return ambientLight; }
   float get_aperture() { return aperture; }
   float get_exponent() { return exponent; }

   string lightType;
   Point3 position;
   Vector3 color;
   Vector3 function;
   Vector3 direction;
   Vector3 ambientLight;
   float aperture;
   float exponent;
};

#endif
