#pragma once
#include "Ray.h"

#include <memory>
using namespace std;

class CSceneObject;

class CIntersection
{
	CRay Ray;
	CSceneObject* Object;
	double Distance;
public:
	CIntersection(CRay, double, CSceneObject*);
	CRay GetRay();
	CSceneObject* GetObject();
	double GetDistance();
};
