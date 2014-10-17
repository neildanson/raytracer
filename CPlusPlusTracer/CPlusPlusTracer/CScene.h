#pragma once
#include "CCamera.h"
#include "CLight.h"
#include "CSceneObject.h"

#include <math.h>
#include <memory>
#include <vector>
using namespace std;

class CScene
{
   CCamera Camera;
   vector<CSceneObject*> Objects;
   vector<CLight> Lights;

   shared_ptr<CIntersection> Intersection(CRay);
   double TestRay(CRay);
   CColor TraceRay(CRay, int);
   CColor Shade(shared_ptr<CIntersection>, int);
   CColor GetNaturalColor(CSceneObject*, CVector, CVector, CVector);
   CColor GetReflectionColor(CSceneObject*, CVector, CVector, int);
   double RecenterX(int, double, double);
   double RecenterY(int, double, double);
   CVector GetPoint(int, int, double, double, double, double, CCamera);

public:
   CScene(CCamera,
      vector<CSceneObject*>,
      vector<CLight>);
   int* Render(int, int, int*);
};
