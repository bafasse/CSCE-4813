//============================================================
// Program: Scene.h
// Purpose: Functions to process scene files
// Author:  John Gauch
// Date:    Spring 2013
//============================================================

#ifndef _SCENE_H_
#define _SCENE_H_

#include "Common.h"
#include "Camera.h"
#include "Light.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Object.h"
#include "Point3.h"
#include "Shape.h"
#include "Trans.h"
#include "Vector3.h"
#include "Vector4.h"

// String constants used for parsing
const string TOKEN_BACKGROUND     = "background";
const string TOKEN_COLOR          = "color";
const string TOKEN_OB             = "[";
const string TOKEN_CB             = "]";
const string TOKEN_CAMERA         = "camera";
const string TOKEN_EYE            = "eye";
const string TOKEN_LOOK           = "look";
const string TOKEN_FOCUS          = "focus";
const string TOKEN_UP             = "up";
const string TOKEN_ANGLE          = "angle";
const string TOKEN_NEAR_FAR       = "near-far";
const string TOKEN_LIGHT          = "light";
const string TOKEN_LIGHTTYPE      = "type";
const string TOKEN_POINT          = "point";
const string TOKEN_DIRECTIONAL    = "directional";
const string TOKEN_SPOTLIGHT      = "spotlight";
const string TOKEN_POSITION       = "position";
const string TOKEN_DIRECTION      = "direction";
const string TOKEN_FUNCTION       = "function";
const string TOKEN_APERTURE       = "aperture";
const string TOKEN_EXPONENT       = "exponent";
const string TOKEN_MASTERSUBGRAPH = "mastersubgraph";
const string TOKEN_TRANS          = "trans";
const string TOKEN_ROTATE         = "rotate";
const string TOKEN_TRANSLATE      = "translate";
const string TOKEN_SCALE          = "scale";
const string TOKEN_MATRIXRC       = "matrixRC";
const string TOKEN_MATRIXCR       = "matrixCR";
const string TOKEN_OBJECT         = "object";
const string TOKEN_CUBE           = "cube";
const string TOKEN_CYLINDER       = "cylinder";
const string TOKEN_CONE           = "cone";
const string TOKEN_SPHERE         = "sphere";
const string TOKEN_AMBIENT        = "ambient";
const string TOKEN_DIFFUSE        = "diffuse";
const string TOKEN_SPECULAR       = "specular";
const string TOKEN_REFLECT        = "reflect";
const string TOKEN_TRANSPARENT    = "transparent";
const string TOKEN_EMIT           = "emit";
const string TOKEN_SHINE          = "shine";
const string TOKEN_IOR            = "ior";
const string TOKEN_TEXTURE        = "texture";
const string TOKEN_SUBGRAPH       = "subgraph";
const string TOKEN_ALPHA          = "alpha";
const string TOKEN_EMISSION       = "emission";

//============================================================
class Subgraph
{
public:
   Subgraph() : name() {}
   string name;
   vector<Trans> vtrans;
};

//============================================================
class Scene
{
public:
   Scene();

   bool readToken() { return !(din >> token); }
   string getToken() { return token; }
   double getValue() { return atof(token.c_str()); }
   bool readScene(string filename);
   bool readBackground(Vector3 & background);
   bool readCamera(Camera & camera);
   bool readLight(Light & light);
   bool readSubgraph(Subgraph & subgraph);
   bool readTrans(Trans & trans);
   bool readObject(Object & object);
   bool writeScene(string filename);
   bool writeBackground(Vector3 & background);
   bool writeCamera(Camera & camera);
   bool writeLight(Light & light);
   bool writeSubgraph(Subgraph & subgraph);
   bool writeTrans(Trans & trans);
   bool writeObject(Object & object);
   bool flattenTree(string name, Matrix4 matrix, Matrix4 matrix_Inv);
   bool intersectObjects(Point3 ray_pt, Vector3 ray_dir, 
      Point3 & hit_pt, Vector3 & hit_normal, Object & hit_obj);

   ifstream din;
   ofstream dout;
   string token;
   string errorMessage;
   Vector3 background;
   Camera camera;
   vector<Light> vlight;
   vector<Subgraph> vsubgraph;
   vector<Trans> vtrans;
};

#endif
