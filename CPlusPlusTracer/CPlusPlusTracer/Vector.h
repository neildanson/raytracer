#pragma once

#include <math.h>
#include <memory>
using namespace std;

class CVector
{
	const double X, Y, Z;
public:
   CVector(double x, double y, double z);

   double Dot(CVector) const;
   double Length() const;
   CVector Cross(CVector) const;
   CVector Add(CVector) const;
   CVector Subtract(CVector) const;
   CVector Scale(double) const;
   CVector Normalize() const;
   double GetX() const;
   double GetY() const;
   double GetZ() const;

};
