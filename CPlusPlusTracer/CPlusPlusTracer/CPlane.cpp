#include "CPlane.h"


CPlane::CPlane(CVector normal, double offset, shared_ptr<CSurface> surface)
   : PlaneNormal(normal), Offset(offset), Surface(surface) {
}

shared_ptr<CIntersection> CPlane::Intersects(CRay ray) {
   auto denom = this->PlaneNormal.Dot(ray.GetDirection());
   if (denom > 0.0) {
      return nullptr;
   }
   return make_shared<CIntersection>(ray, (this->PlaneNormal.Dot(ray.GetPosition()) + this->Offset) / -denom, this);
}

CVector CPlane::Normal(CVector pos) {
   return this->PlaneNormal;
}

shared_ptr<CSurface> CPlane::GetSurface() {
   return this->Surface;
}