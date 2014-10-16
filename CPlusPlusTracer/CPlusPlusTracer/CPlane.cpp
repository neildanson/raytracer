#include "CPlane.h"


CPlane::CPlane(const shared_ptr<CVector> normal, double offset, const shared_ptr<CSurface> surface)
   : PlaneNormal(normal), Offset(offset), Surface(surface) {
}

shared_ptr<CIntersection> CPlane::Intersects(const shared_ptr<CRay> ray) {
   auto denom = this->PlaneNormal->Dot(ray->Direction);
   if (denom > 0.0) {
      return nullptr;
   }
   return make_shared<CIntersection>(ray, 
      (this->PlaneNormal->Dot(ray->Position) + this->Offset) / -denom, 
      make_shared<CPlane>(this->PlaneNormal, this->Offset, this->Surface));
}

shared_ptr<CVector> CPlane::Normal(const shared_ptr<CVector> pos) {
   return this->PlaneNormal;
}

shared_ptr<CSurface> CPlane::GetSurface() {
   return this->Surface;
}