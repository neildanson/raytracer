#pragma once
#include "CSceneObject.h"
#include "CSurface.h"
#include "CVector.h"

#include <memory>
using namespace std;

class CSphere : public CSceneObject
{
   CVector Position;
   double Radius;
   shared_ptr<CSurface> Surface;
public:

   CSphere(CVector, double, shared_ptr<CSurface>);

   shared_ptr<CIntersection> Intersects(CRay);
   CVector Normal(CVector);
   shared_ptr<CSurface> GetSurface();
};
