#ifndef _TRANS_H_
#define _TRANS_H_

#include "Common.h"
#include "Matrix4.h"
#include "Object.h"

class Trans
{
public:
   Trans();

   void set_modelview(Matrix4 m) { modelview = m; }
   void set_modelview_Inv(Matrix4 m) { modelview_Inv = m; }
   void set_subgraphName(string s) { subgraphName = s; }
   void set_object(Object o) { object = o; }

   Matrix4 get_modelview() { return modelview; }
   Matrix4 get_modelview_Inv() { return modelview_Inv; }
   string get_subgraphName() { return subgraphName; }
   Object get_object() { return object; }

   Matrix4 modelview;
   Matrix4 modelview_Inv;
   string subgraphName;
   Object object;
};

#endif
