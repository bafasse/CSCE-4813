//============================================================
// Program: Scene.cpp
// Purpose: Functions to process scene files
// Author:  John Gauch
// Date:    Spring 2013
//============================================================

#include "Scene.h"

Scene scene;

//============================================================
Scene::Scene()
{
   token = "";
   errorMessage = "";
   background = Vector3(0,0,0);
}

//============================================================
bool Scene::readScene(string filename) 
{
    din.open(filename.c_str());
    if (din.fail())
    {
        errorMessage = "Error: Could not open input file: " + filename;
        cerr << errorMessage << endl;
        return false;
    }

    bool done = false;
    errorMessage = "";
    do {
        // Read background
        done = readToken();
        if (getToken() == TOKEN_BACKGROUND)
            done = !readBackground(background);

        // Read camera
        else if (getToken() == TOKEN_CAMERA)
            done = !readCamera(camera);

        // Read lights
        else if (getToken() == TOKEN_LIGHT)
        {
            Light light;
            done = !readLight(light);
            if (!done) vlight.push_back(light);
        }

        // Read subgraphs
        else if (getToken() == TOKEN_MASTERSUBGRAPH)
        {
            Subgraph subgraph;
            done = !readSubgraph(subgraph);
            if (!done) vsubgraph.push_back(subgraph);
        }

        else if (!done) {
            errorMessage = "Error: Unrecognized scene token: " + getToken();
            cerr << errorMessage << endl;
            return false;
        }
    } while (!done);

    Matrix4 ident;
    ident.identity();
    flattenTree("root", ident, ident);
    cout << "object count: " << vtrans.size() << endl;
    return (errorMessage.length() == 0);
}

//============================================================
bool Scene::readBackground(Vector3 & background) 
{
    do {
        readToken();
        if (getToken() == TOKEN_OB) {
        } else if (getToken() == TOKEN_CB) {
            break;

        } else if (getToken() == TOKEN_COLOR) {
          readToken(); background[0] = getValue();
          readToken(); background[1] = getValue();
          readToken(); background[2] = getValue();

        } else {
            errorMessage = "Error: Unrecognized background token: " + getToken();
            cerr << errorMessage << endl;
            return false;
        }
    } while (true);
    return true;
}

//============================================================
bool Scene::readCamera(Camera & camera)
{
    do {
        readToken();
        if (getToken() == TOKEN_OB) {
        } else if (getToken() == TOKEN_CB) {
            break;

        } else if (getToken() == TOKEN_EYE) {
            readToken(); camera.eye[0] = getValue();
            readToken(); camera.eye[1] = getValue();
            readToken(); camera.eye[2] = getValue();
            
        } else if (getToken() == TOKEN_LOOK) {
            readToken(); camera.look[0] = getValue();
            readToken(); camera.look[1] = getValue();
            readToken(); camera.look[2] = getValue();
            camera.focus = camera.eye + camera.look;

        } else if (getToken() == TOKEN_FOCUS) {
            readToken(); camera.focus[0] = getValue();
            readToken(); camera.focus[1] = getValue();
            readToken(); camera.focus[2] = getValue();
            camera.look = camera.focus - camera.eye;
            
        } else if (getToken() == TOKEN_UP) {
            readToken(); camera.up[0] = getValue();
            readToken(); camera.up[1] = getValue();
            readToken(); camera.up[2] = getValue();
            
        } else if (getToken() == TOKEN_ANGLE) {
            readToken(); camera.zoom = getValue();
            
        } else if (getToken() == TOKEN_NEAR_FAR) {
            readToken(); camera.near = getValue();
            readToken(); camera.far = getValue();
            
        } else {
            errorMessage = "Error: Unrecognized camera token: " + getToken();
            cerr << errorMessage << endl;
            return false;
        }
    } while (true);
    return true;
}

//============================================================
bool Scene::readLight(Light & light) 
{
    light.lightType = TOKEN_POINT;
    do {
        readToken();
        if (getToken() == TOKEN_OB) {
        } else if (getToken() == TOKEN_CB) {
            break;
            
        } else if (getToken() == TOKEN_LIGHTTYPE) {
            readToken();
            if (getToken() == TOKEN_POINT)
                light.lightType = TOKEN_POINT;
            
            else if (getToken() == TOKEN_DIRECTIONAL)
                light.lightType = TOKEN_DIRECTIONAL;
                
            else if (getToken() == TOKEN_SPOTLIGHT)
                light.lightType = TOKEN_SPOTLIGHT;
                
            else {
                errorMessage = "Error: Unknown light type: " + getToken();
                cerr << errorMessage << endl;
                return false;
            }

        } else if (getToken() == TOKEN_POSITION) {
            readToken(); light.position[0] = getValue();
            readToken(); light.position[1] = getValue();
            readToken(); light.position[2] = getValue();
            
        } else if (getToken() == TOKEN_COLOR) {
            readToken(); light.color[0] = getValue();
            readToken(); light.color[1] = getValue();
            readToken(); light.color[2] = getValue();
            
        } else if (getToken() == TOKEN_FUNCTION) {
            readToken(); light.function[0] = getValue();
            readToken(); light.function[1] = getValue();
            readToken(); light.function[2] = getValue();
            
        } else if (getToken() == TOKEN_DIRECTION) {
            readToken(); light.direction[0] = getValue();
            readToken(); light.direction[1] = getValue();
            readToken(); light.direction[2] = getValue();
            
        } else if (getToken() == TOKEN_APERTURE) {
            readToken(); light.aperture = getValue();
            
        } else if (getToken() == TOKEN_EXPONENT) {
            readToken(); light.exponent = getValue();
            
        } else if (getToken() == TOKEN_AMBIENT) {
            readToken(); light.ambientLight[0] = getValue();
            readToken(); light.ambientLight[1] = getValue();
            readToken(); light.ambientLight[2] = getValue();

        } else {
            errorMessage = "Error: Unrecognized light token: " + getToken();
            cerr << errorMessage << endl;
            return false;
        }

    } while (true);
    return true;
}

//============================================================
bool Scene::readSubgraph(Subgraph & subgraph) 
{
    readToken();
    subgraph.name = getToken();

    do {
        readToken();
        if (getToken() == TOKEN_OB) {
        } else if (getToken() == TOKEN_CB) {
            break;

        } else if (getToken() == TOKEN_TRANS) {
            Trans trans;
	    bool done = !readTrans(trans);
            if (!done) subgraph.vtrans.push_back(trans);

        } else {
            errorMessage = "Error: Unrecognized subgraph token: " 
                         + subgraph.name + " " + getToken();
            cerr << errorMessage << endl;
            return false;
        }
    } while (true);
    return true;
}

//============================================================
bool Scene::readTrans(Trans & trans) 
{
    Matrix4 modelview;
    Matrix4 modelview_Inv;

    do {
        readToken();
        if (getToken() == TOKEN_OB) {
        } else if (getToken() == TOKEN_CB) {
            break;
        } else if (getToken() == TOKEN_ROTATE) {
            Vector3 axis;
            double angle;
            readToken(); axis[0] = getValue();
            readToken(); axis[1] = getValue();
            readToken(); axis[2] = getValue();
            readToken(); angle = getValue() * M_PI / 180; 
            modelview = modelview * modelview.rotation(axis, angle);
            modelview_Inv = modelview.rotation(axis, -angle) * modelview_Inv;

        } else if (getToken() == TOKEN_TRANSLATE) {
            Vector3 translate;
            readToken(); translate[0] = getValue();
            readToken(); translate[1] = getValue();
            readToken(); translate[2] = getValue();
            modelview = modelview * modelview.translation(translate);
            modelview_Inv = modelview_Inv.translation(-translate) * modelview_Inv;

        } else if (getToken() == TOKEN_SCALE) {
            Vector3 scale, scale_Inv;
            readToken(); scale[0] = getValue();
            readToken(); scale[1] = getValue();
            readToken(); scale[2] = getValue();
            scale_Inv[0] = 1/scale[0];
            scale_Inv[1] = 1/scale[1];
            scale_Inv[2] = 1/scale[2];
            modelview = modelview * modelview.scaling(scale);
            modelview_Inv = modelview_Inv.scaling(scale_Inv) * modelview_Inv;

        } else if (getToken() == TOKEN_MATRIXRC) {
            Vector4 r0, r1, r2, r3;
            readToken(); r0[0] = getValue();
            readToken(); r0[1] = getValue();
            readToken(); r0[2] = getValue();
            readToken(); r0[3] = getValue();
      
            readToken(); r1[0] = getValue();
            readToken(); r1[1] = getValue();
            readToken(); r1[2] = getValue();
            readToken(); r1[3] = getValue();
      
            readToken(); r2[0] = getValue();
            readToken(); r2[1] = getValue();
            readToken(); r2[2] = getValue();
            readToken(); r2[3] = getValue();
      
            readToken(); r3[0] = getValue();
            readToken(); r3[1] = getValue();
            readToken(); r3[2] = getValue();
            readToken(); r3[3] = getValue();
            Matrix4 matrix(r0,r1,r2,r3);
            Matrix4 matrix_Inv = matrix.inverse();
            modelview = modelview * matrix;
            modelview_Inv = matrix_Inv * modelview_Inv;

        } else if (getToken() == TOKEN_MATRIXCR) {
            Vector4 r0, r1, r2, r3;
            readToken(); r0[0] = getValue();
            readToken(); r1[0] = getValue();
            readToken(); r2[0] = getValue();
            readToken(); r3[0] = getValue();
      
            readToken(); r0[1] = getValue();
            readToken(); r1[1] = getValue();
            readToken(); r2[1] = getValue();
            readToken(); r3[1] = getValue();
      
            readToken(); r0[2] = getValue();
            readToken(); r1[2] = getValue();
            readToken(); r2[2] = getValue();
            readToken(); r3[2] = getValue();
      
            readToken(); r0[3] = getValue();
            readToken(); r1[3] = getValue();
            readToken(); r2[3] = getValue();
            readToken(); r3[3] = getValue();
            Matrix4 matrix(r0,r1,r2,r3);
            Matrix4 matrix_Inv = matrix.inverse();
            modelview = modelview * matrix;
            modelview_Inv = matrix_Inv * modelview_Inv;

        } else if (getToken() == TOKEN_OBJECT) {
            Object object;
            readObject(object);
            trans.set_object(object);
            trans.set_modelview(modelview);
            trans.set_modelview_Inv(modelview_Inv);

        } else if (getToken() == TOKEN_SUBGRAPH) {
            string subgraphName;
            readToken(); subgraphName = getToken();
            trans.set_subgraphName(subgraphName);
            trans.set_modelview(modelview);
            trans.set_modelview_Inv(modelview_Inv);

        } else {
            errorMessage = "Error: Unrecognized trans token: " + getToken();
            cerr << errorMessage << endl;
            return false;
        }
    } while (true);
    return true;
}

//============================================================
bool Scene::readObject(Object & object)
{
    readToken();
    if (getToken() == TOKEN_CUBE) {
        object.shape = TOKEN_CUBE;

    } else if (getToken() == TOKEN_CYLINDER) {
        object.shape = TOKEN_CYLINDER;

    } else if (getToken() == TOKEN_CONE) {
        object.shape = TOKEN_CONE;

    } else if (getToken() == TOKEN_SPHERE) {
        object.shape = TOKEN_SPHERE;

    } else {
        errorMessage = "Error: Unrecognized object type: " + getToken();
        cerr << errorMessage << endl;
        return false;
    }

    do {
        readToken();
        if (getToken() == TOKEN_OB) {
        } else if (getToken() == TOKEN_CB) {
            break;

        } else if (getToken() == TOKEN_AMBIENT) {
            readToken(); object.ambient[0] = getValue();
            readToken(); object.ambient[1] = getValue();
            readToken(); object.ambient[2] = getValue();

        } else if (getToken() == TOKEN_DIFFUSE) {
            readToken(); object.diffuse[0] = getValue();
            readToken(); object.diffuse[1] = getValue();
            readToken(); object.diffuse[2] = getValue();

        } else if (getToken() == TOKEN_SPECULAR) {
            readToken(); object.specular[0] = getValue();
            readToken(); object.specular[1] = getValue();
            readToken(); object.specular[2] = getValue();

        } else if (getToken() == TOKEN_REFLECT) {
            readToken(); object.reflect[0] = getValue();
            readToken(); object.reflect[1] = getValue();
            readToken(); object.reflect[2] = getValue();

        } else if (getToken() == TOKEN_TRANSPARENT) {
            readToken(); object.transparent[0] = getValue();
            readToken(); object.transparent[1] = getValue();
            readToken(); object.transparent[2] = getValue();

        } else if (getToken() == TOKEN_ALPHA) {
            readToken(); object.alpha = getValue();

        } else if (getToken() == TOKEN_EMISSION) {
            readToken(); object.emission[0] = getValue();
            readToken(); object.emission[1] = getValue();
            readToken(); object.emission[2] = getValue();

        } else if (getToken() == TOKEN_EMIT) {
            readToken(); object.emit[0] = getValue();
            readToken(); object.emit[1] = getValue();
            readToken(); object.emit[2] = getValue();

        } else if (getToken() == TOKEN_SHINE) {
            readToken(); object.shine = getValue();

        } else if (getToken() == TOKEN_IOR) {
            readToken(); object.ior = getValue();

        } else if (getToken() == TOKEN_TEXTURE) {
            readToken(); object.textureFile = getToken();
            readToken(); object.textureU = getValue();
            readToken(); object.textureV = getValue();

        } else {
            errorMessage = "Error: Unrecognized object token: " + getToken();
            cerr << errorMessage << endl;
            return false;
        }
    } while (true);
    return true;
}

//============================================================
bool Scene::writeScene(string filename) 
{
    // Open output file
    dout.open(filename.c_str());
    if (dout.fail())
    {
        errorMessage = "Error: Could not open output file: " + filename;
        cerr << errorMessage << endl;
        return false;
    }

   // Write background
   if (!writeBackground(scene.background))
      return false;

   // Write camera
   if (!writeCamera(scene.camera))
      return false;

   // Write lights
   for (unsigned int i=0; i<vlight.size(); i++)
      if (!writeLight(vlight[i]))
         return false;

   // Write subgraphs
   for (unsigned int i=0; i<vsubgraph.size(); i++)
      if (!writeSubgraph(vsubgraph[i]))
         return false;
   return true;
}

//============================================================
bool Scene::writeBackground(Vector3 & background)
{
   dout << TOKEN_BACKGROUND << " " << TOKEN_OB << endl;
   dout << TOKEN_COLOR << " " 
        << background[0] << " "  
        << background[1] << " "  
        << background[2] << endl;
   dout << TOKEN_CB << endl << endl;
   return true;
}

//============================================================
bool Scene::writeCamera(Camera & camera)
{
   dout << TOKEN_CAMERA << " " << TOKEN_OB << endl;
   dout << TOKEN_EYE << " " 
        << camera.eye[0] << " "  
        << camera.eye[1] << " "  
        << camera.eye[2] << endl;
   dout << TOKEN_LOOK << " " 
        << camera.look[0] << " "  
        << camera.look[1] << " "  
        << camera.look[2] << endl;
   dout << TOKEN_FOCUS << " " 
        << camera.focus[0] << " "  
        << camera.focus[1] << " "  
        << camera.focus[2] << endl;
   dout << TOKEN_UP << " " 
        << camera.up[0] << " "  
        << camera.up[1] << " "  
        << camera.up[2] << endl;
   dout << TOKEN_ANGLE << " " 
        << camera.zoom << endl;
   dout << TOKEN_NEAR_FAR << " " 
        << camera.near << " " 
        << camera.far << endl;
   dout << TOKEN_CB << endl << endl;
   return true;
}

//============================================================
bool Scene::writeLight(Light & light)
{
   dout << TOKEN_LIGHT << " " << TOKEN_OB << endl;
   dout << TOKEN_LIGHTTYPE << " " 
        << light.lightType << endl;
   dout << TOKEN_POSITION << " " 
        << light.position[0] << " "  
        << light.position[1] << " "  
        << light.position[2] << endl;
   dout << TOKEN_COLOR << " " 
        << light.color[0] << " "  
        << light.color[1] << " "  
        << light.color[2] << endl;
   dout << TOKEN_FUNCTION << " " 
        << light.function[0] << " "  
        << light.function[1] << " "  
        << light.function[2] << endl;
   dout << TOKEN_DIRECTION << " " 
        << light.direction[0] << " "  
        << light.direction[1] << " "  
        << light.direction[2] << endl;
   dout << TOKEN_APERTURE << " " 
        << light.aperture << endl;
   dout << TOKEN_EXPONENT << " " 
        << light.exponent << endl;
   dout << TOKEN_AMBIENT << " " 
        << light.ambientLight[0] << " "  
        << light.ambientLight[1] << " "  
        << light.ambientLight[2] << endl;
   dout << TOKEN_CB << endl << endl;
   return true;
}

//============================================================
bool Scene::writeSubgraph(Subgraph & subgraph)
{
   dout << TOKEN_MASTERSUBGRAPH << " " 
        << subgraph.name << " " 
        << TOKEN_OB << endl << endl;
   for (unsigned int i=0; i<subgraph.vtrans.size(); i++)
      if (!writeTrans(subgraph.vtrans[i]))
         return false;
   dout << TOKEN_CB << endl << endl;
   return true;
}

//============================================================
bool Scene::writeTrans(Trans & trans)
{
   dout << TOKEN_TRANS << " " << TOKEN_OB << endl;
   dout << TOKEN_MATRIXRC << endl;
   for (int r=0; r<4; r++)
   {
      for (int c=0; c<4; c++)
         dout << trans.modelview(r,c) << " ";
      dout << endl;
   }
   if (trans.subgraphName != "")
      dout << TOKEN_SUBGRAPH << " " << trans.subgraphName << endl;
   else if (!writeObject(trans.object))
      return false;
   dout << TOKEN_CB << endl << endl;
   return true;
}

//============================================================
bool Scene::writeObject(Object & object)
{
   dout << TOKEN_OBJECT << " " 
        << object.shape << " " 
        << TOKEN_OB << endl;
   dout << TOKEN_AMBIENT << " " 
        << object.ambient[0] << " "  
        << object.ambient[1] << " "  
        << object.ambient[2] << endl;
   dout << TOKEN_DIFFUSE << " " 
        << object.diffuse[0] << " "  
        << object.diffuse[1] << " "  
        << object.diffuse[2] << endl;
   dout << TOKEN_SPECULAR << " " 
        << object.specular[0] << " "  
        << object.specular[1] << " "  
        << object.specular[2] << endl;
   dout << TOKEN_REFLECT << " " 
        << object.reflect[0] << " "  
        << object.reflect[1] << " "  
        << object.reflect[2] << endl;
   dout << TOKEN_TRANSPARENT << " " 
        << object.transparent[0] << " "  
        << object.transparent[1] << " "  
        << object.transparent[2] << endl;
   dout << TOKEN_ALPHA << " " 
        << object.alpha << endl;
   dout << TOKEN_EMISSION << " " 
        << object.emission[0] << " "  
        << object.emission[1] << " "  
        << object.emission[2] << endl;
   dout << TOKEN_EMIT << " " 
        << object.emit[0] << " "  
        << object.emit[1] << " "  
        << object.emit[2] << endl;
   dout << TOKEN_SHINE << " " 
        << object.shine << endl;
   dout << TOKEN_IOR << " " 
        << object.ior << endl;
   dout << TOKEN_TEXTURE << " " 
        << object.textureFile << " "
        << object.textureU << " "
        << object.textureV << endl;
   dout << TOKEN_CB << endl;
   return true;
}

//============================================================
bool Scene::flattenTree(string name, Matrix4 matrix, Matrix4 matrix_Inv)
{
   bool result = false;
   for (unsigned int s=0; s<vsubgraph.size(); s++)
      if (vsubgraph[s].name == name)
      {
         result = true;
         for (unsigned int t=0; t<vsubgraph[s].vtrans.size(); t++)
         {
            Trans trans = vsubgraph[s].vtrans[t];
            Matrix4 trans_matrix = matrix * trans.get_modelview();
            Matrix4 trans_matrix_Inv = trans.get_modelview_Inv() * matrix_Inv;
            string subgraphName = trans.get_subgraphName();
            if (subgraphName == "")
            {
               trans.set_modelview(trans_matrix);
               trans.set_modelview_Inv(trans_matrix_Inv);
               vtrans.push_back(trans);
            }
            else
               flattenTree(subgraphName, trans_matrix, trans_matrix_Inv);
         }
      }
   return result;
}

//============================================================
bool Scene::intersectObjects(Point3 ray_pt, Vector3 ray_dir, 
   Point3 & hit_pt, Vector3 & hit_normal, Object & hit_obj)
{
   bool hit_found = false;
   unsigned int hit_trans = 0;
   double hit_t = DBL_MAX;
   double int_t1 = DBL_MAX;
   double int_t2 = DBL_MAX;
   Point3 int_pt;
   Vector3 int_normal;

   for (unsigned int t=0; t<vtrans.size(); t++)
   {
      Matrix4 trans_matrix_Inv = vtrans[t].get_modelview_Inv();
      string shape = vtrans[t].object.shape;
      Point3 new_pt = trans_matrix_Inv * ray_pt;
      Vector3 new_dir = trans_matrix_Inv * ray_dir;

      if(((shape == "sphere") && intersect_sphere(new_pt, new_dir,
         int_t1, int_t2, int_pt, int_normal) && (int_t1 < hit_t))

      || ((shape == "cube") && intersect_cube(new_pt, new_dir,
         int_t1, int_t2, int_pt, int_normal) && (int_t1 < hit_t))

      || ((shape == "cylinder") && intersect_cylinder(new_pt, new_dir,
         int_t1, int_t2, int_pt, int_normal) && (int_t1 < hit_t))

      || ((shape == "cone") && intersect_cone(new_pt, new_dir,
         int_t1, int_t2, int_pt, int_normal) && (int_t1 < hit_t)))
      {
         hit_found = true;
         hit_t = int_t1;
         hit_pt = int_pt;
         hit_normal = int_normal;
         hit_trans = t;
      } 
   }

   if (hit_found)
   {
      hit_pt = vtrans[hit_trans].get_modelview() * hit_pt;
      hit_normal = vtrans[hit_trans].get_modelview_Inv().transpose() * hit_normal;
      hit_obj = vtrans[hit_trans].get_object();
   }
   return hit_found;
}

