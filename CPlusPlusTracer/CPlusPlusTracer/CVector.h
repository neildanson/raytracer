#pragma once

#include <math.h>
#include <memory>
using namespace std;

class CVector
{
	double X, Y, Z;
public:
   CVector(double x, double y, double z);

   double Dot(CVector);
   double Length();
   CVector Cross(CVector);
   CVector Add(CVector);
   CVector Subtract(CVector);
   CVector Scale(double);
   CVector Normalize();
   double GetX();
   double GetY();
   double GetZ();

};
