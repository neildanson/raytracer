#pragma once

#include "SceneObject.h"
#include "Surface.h"
#include "Vector.h"

#include <memory>
using namespace std;

class CPlane : public CSceneObject
{
   CVector PlaneNormal;
   double Offset;
   shared_ptr<CSurface> Surface;
public:
   CPlane(CVector, double, shared_ptr<CSurface>);

   shared_ptr<CIntersection> Intersects(CRay);
   CVector Normal(CVector);
   shared_ptr<CSurface> GetSurface();
};

