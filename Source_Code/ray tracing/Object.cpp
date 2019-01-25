#include "Object.h"

Object::Object()
{
   shape = "";
   ambient = Vector3(0,0,0);
   diffuse = Vector3(0,0,0);
   specular = Vector3(0,0,0);
   reflect = Vector3(0,0,0);
   transparent = Vector3(0,0,0);
   alpha = 0;
   emission = Vector3(0,0,0);
   emit = Vector3(0,0,0);
   shine = 0;
   ior = 0;
   textureFile = "none";
   textureU = 0;
   textureV = 0;
}

