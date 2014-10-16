#pragma once
#include "CSceneObject.h"
#include "CSurface.h"
#include "CVector.h"

#include <memory>
using namespace std;

class CSphere : public CSceneObject
{
public:
   const shared_ptr<CVector> Position;
   const double Radius;
   const shared_ptr<CSurface> Surface;
   CSphere(const shared_ptr<CVector>, double, const shared_ptr<CSurface>);

   shared_ptr<CIntersection> Intersects(const shared_ptr<CRay>);
   shared_ptr<CVector> Normal(const shared_ptr<CVector>);
   shared_ptr<CSurface> GetSurface();
};
