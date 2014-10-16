#pragma once
#include "CRay.h"

#include <memory>
using namespace std;

class CSceneObject;

class CIntersection
{
public:
   const shared_ptr<CRay> Ray;
   const shared_ptr<CSceneObject> Object;
   const double Distance;
   CIntersection(const shared_ptr<CRay>, double, const shared_ptr<CSceneObject>);
};
