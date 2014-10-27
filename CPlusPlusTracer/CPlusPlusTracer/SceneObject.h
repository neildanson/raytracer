#pragma once
#include "Intersection.h"
#include "Ray.h"
#include "Surface.h"

#include <memory>
using namespace std;

class CSceneObject
{
public:
	virtual shared_ptr<CIntersection> Intersects(CRay) = 0;
   virtual CVector Normal(CVector) = 0;
   virtual shared_ptr<CSurface> GetSurface() = 0;
};
