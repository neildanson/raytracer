#include "CIntersection.h"

CIntersection::CIntersection(const shared_ptr<CRay> ray, double distance, const shared_ptr<CSceneObject> object)
   : Ray(ray), Distance(distance), Object(object)
{
}