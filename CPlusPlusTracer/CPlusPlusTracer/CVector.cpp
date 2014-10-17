#include "CVector.h"

CVector::CVector(double x, double y, double z) : X(x), Y(y), Z(z) {
}

double CVector::Dot(CVector v) {
   return (this->X * v.X) + (this->Y * v.Y) + (this->Z * v.Z);
}

double CVector::Length(){
   return sqrt(this->Dot(*this));
}

CVector CVector::Cross(CVector v) {
   return
      CVector((this->Y*v.Z) - (this->Z * v.Y),
	          (this->Z*v.X) - (this->X * v.Z),
              (this->X*v.Y) - (this->Y * v.X));
}

CVector CVector::Add(CVector v) {
   return CVector(this->X + v.X, this->Y + v.Y, this->Z + v.Z);
}

CVector CVector::Subtract(CVector v) {
   return CVector(this->X - v.X, this->Y - v.Y, this->Z - v.Z);
}

CVector CVector::Scale(double s) {
   return CVector(this->X * s, this->Y * s, this->Z * s);
}

CVector CVector::Normalize() {
   double mag = this->Length();
   return this->Scale(mag == 0.0 ? INFINITY : (1.0 / mag));
}

double CVector::GetX() {
   return this->X;
}

double  CVector::GetY() {
   return this->Y;
}

double  CVector::GetZ() {
   return this->Z;
}