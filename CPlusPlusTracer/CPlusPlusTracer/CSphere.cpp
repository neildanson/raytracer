#include "CSphere.h"

CSphere::CSphere(CVector position, double radius, shared_ptr<CSurface> surface)
   : Position(position), Radius(radius), Surface(surface) {
}

shared_ptr<CIntersection> CSphere::Intersects(CRay ray) {
   auto eo = this->Position.Subtract(ray.GetPosition());
   auto v = eo.Dot(ray.GetDirection());
   if (v < 0.0){
      return nullptr;
   }
   auto disc = (pow(this->Radius, 2.0)) - (eo.Dot(eo) - pow(v, 2.0));
   if (disc < 0.0) {
      return nullptr;
   }
   auto distance = v - (sqrt(disc));
   return make_shared<CIntersection>(ray, distance, this);
}
CVector CSphere::Normal(CVector pos) {
   return pos.Subtract(this->Position).Normalize();
}
shared_ptr<CSurface> CSphere::GetSurface() {
   return this->Surface;
}