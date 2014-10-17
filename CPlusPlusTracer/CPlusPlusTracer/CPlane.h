#pragma once

#include "CSceneObject.h"
#include "CSurface.h"
#include "CVector.h"

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

