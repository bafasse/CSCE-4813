#include "Light.h"

Light::Light()
{
   lightType = "point";
   position = Point3(0,0,0);
   color = Vector3(1,1,1);
   function = Vector3(1,0,0);
   direction = Vector3(0,0,0);
   ambientLight = Vector3(0,0,0);
   aperture=180;
   exponent=1;
}

