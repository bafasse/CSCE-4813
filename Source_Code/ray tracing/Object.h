#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Common.h"
#include "Vector3.h"

class Object {
public:
   Object();

   void set_shape(string s) { shape = s; }
   void set_ambient(Vector3 a) { ambient = a; }
   void set_diffuse(Vector3 d) { diffuse = d; }
   void set_specular(Vector3 s) { specular = s; }
   void set_reflect(Vector3 r) { reflect = r; }
   void set_transparent(Vector3 t) { transparent = t; }
   void set_alpha(double a) { alpha = a; }
   void set_emission(Vector3 e) { emission = e; }
   void set_emit(Vector3 e) { emit = e; }
   void set_shine(float s) { shine = s; }
   void set_ior(float i) { ior = i; }
   void set_textureFile(string t) { textureFile = t; }
   void set_textureU(float u) { textureU = u; }
   void set_textureV(float v) { textureV = v; }

   string get_shape() { return shape; }
   Vector3 get_ambient() { return ambient; }
   Vector3 get_diffuse() { return diffuse; }
   Vector3 get_specular() { return specular; }
   Vector3 get_reflect() { return reflect; }
   Vector3 get_transparent() { return transparent; }
   double get_alpha() { return alpha; }
   Vector3 get_emission() { return emission; }
   Vector3 get_emit() { return emit; }
   float get_shine() { return shine; }
   float get_ior() { return ior; }
   string get_textureFile() { return textureFile; }
   float get_textureU() { return textureU; }
   float get_textureV() { return textureV; }

   string shape;
   Vector3 ambient;
   Vector3 diffuse;
   Vector3 specular;
   Vector3 reflect;
   Vector3 transparent;
   double alpha;
   Vector3 emission;
   Vector3 emit;
   float shine;
   float ior;
   string textureFile;
   float textureU;
   float textureV;
};

#endif
