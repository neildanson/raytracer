#include "CSphere.h"

CSphere::CSphere(const shared_ptr<CVector>position, double radius, const shared_ptr<CSurface> surface)
   : Position(position), Radius(radius), Surface(surface) {
}

shared_ptr<CIntersection> CSphere::Intersects(const shared_ptr<CRay> ray) {
   auto eo = this->Position->Subtract(ray->Position);
   auto v = eo->Dot(ray->Direction);
   if (v < 0.0){
      return nullptr;
   }
   auto disc = (pow(this->Radius, 2.0)) - (eo->Dot(eo) - pow(v, 2.0));
   if (disc < 0.0) {
      return nullptr;
   }
   auto distance = v - (sqrt(disc));
   return make_shared<CIntersection>(ray, distance,
      make_shared<CSphere>(this->Position, this->Radius, this->Surface));
}
shared_ptr<CVector> CSphere::Normal(const shared_ptr<CVector> pos) {
   return pos->Subtract(this->Position)->Normalize();
}
shared_ptr<CSurface> CSphere::GetSurface() {
   return this->Surface;
}