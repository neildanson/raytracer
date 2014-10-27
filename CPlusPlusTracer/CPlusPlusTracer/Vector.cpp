#include "Vector.h"

CVector::CVector(double x, double y, double z) : X(x), Y(y), Z(z) {
}

double CVector::Dot(CVector v) const {
   return (this->X * v.X) + (this->Y * v.Y) + (this->Z * v.Z);
}

double CVector::Length() const {
   return sqrt(this->Dot(*this));
}

CVector CVector::Cross(CVector v) const {
   return
      CVector((this->Y*v.Z) - (this->Z * v.Y),
	          (this->Z*v.X) - (this->X * v.Z),
              (this->X*v.Y) - (this->Y * v.X));
}

CVector CVector::Add(CVector v) const {
   return CVector(this->X + v.X, this->Y + v.Y, this->Z + v.Z);
}

CVector CVector::Subtract(CVector v) const {
   return CVector(this->X - v.X, this->Y - v.Y, this->Z - v.Z);
}

CVector CVector::Scale(double s) const {
   return CVector(this->X * s, this->Y * s, this->Z * s);
}

CVector CVector::Normalize() const {
   double mag = this->Length();
   return this->Scale(mag == 0.0 ? INFINITY : (1.0 / mag));
}

double CVector::GetX() const {
   return this->X;
}

double  CVector::GetY() const {
   return this->Y;
}

double  CVector::GetZ() const {
   return this->Z;
}