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
   shared_ptr<CIntersection> Intersection(const shared_ptr<CRay>);
   double TestRay(const shared_ptr<CRay>);
   shared_ptr<CColor> TraceRay(const shared_ptr<CRay>, int);
   shared_ptr<CColor> Shade(const shared_ptr<CIntersection>, int);
   shared_ptr<CColor> GetNaturalColor(const shared_ptr<CSceneObject>, const shared_ptr<CVector>, const shared_ptr<CVector>, const shared_ptr<CVector>);
   shared_ptr<CColor> GetReflectionColor(const shared_ptr<CSceneObject>, const shared_ptr<CVector>, const shared_ptr<CVector>, int);
   double RecenterX(int, double, double);
   double RecenterY(int, double, double);
   shared_ptr<CVector> GetPoint(int, int, double, double, double, double, const shared_ptr<CCamera>);

public:
   const shared_ptr<CCamera> Camera;
   const vector<shared_ptr<CSceneObject>> Objects;
   const vector<shared_ptr<CLight>> Lights;
   CScene(shared_ptr<CCamera>,
      vector<shared_ptr<CSceneObject>>,
      vector<shared_ptr<CLight>>);
   int* Render(int, int, int*);
};
