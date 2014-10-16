#include "CVector.h"

CVector::CVector(double x, double y, double z) : X(x), Y(y), Z(z) {
}

double CVector::Dot(const shared_ptr<CVector> v) {
   return (this->X * v->X) + (this->Y * v->Y) + (this->Z * v->Z);
}

double CVector::Length(){
   auto v2 = make_shared<CVector>(this->X, this->Y, this->Z);
   return sqrt(this->Dot(v2));
}

shared_ptr<CVector> CVector::Cross(const shared_ptr<CVector> v) {
   return
      make_shared<CVector>((this->Y*v->Z) - (this->Z * v->Y),
	                       (this->Z*v->X) - (this->X * v->Z),
                           (this->X*v->Y) - (this->Y * v->X));
}

shared_ptr<CVector> CVector::Add(const shared_ptr<CVector> v) {
   return make_shared<CVector>(this->X + v->X, this->Y + v->Y, this->Z + v->Z);
}

shared_ptr<CVector> CVector::Subtract(const shared_ptr<CVector> v) {
   return make_shared<CVector>(this->X - v->X, this->Y - v->Y, this->Z - v->Z);
}

shared_ptr<CVector> CVector::Scale(double s) {
   return make_shared<CVector>(this->X * s, this->Y * s, this->Z * s);
}

shared_ptr<CVector> CVector::Normalize() {
   double mag = this->Length();
   return this->Scale(mag == 0.0 ? INFINITY : (1.0 / mag));
}