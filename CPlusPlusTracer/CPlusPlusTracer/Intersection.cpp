#include "Intersection.h"

CIntersection::CIntersection(CRay ray, double distance, CSceneObject* object)
   : Ray(ray), Distance(distance), Object(object)
{
}

CRay CIntersection::GetRay() {
	return this->Ray;
}

CSceneObject* CIntersection::GetObject() {
	return this->Object;
}

double CIntersection::GetDistance() {
	return this->Distance;
}