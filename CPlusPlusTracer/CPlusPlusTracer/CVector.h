#pragma once

#include <math.h>
#include <memory>
using namespace std;

class CVector
{
public:
   const double X, Y, Z;
   CVector(double x, double y, double z);
   double Dot(const shared_ptr<CVector>);
   double Length();
   shared_ptr<CVector> Cross(const shared_ptr<CVector>);
   shared_ptr<CVector> Add(const shared_ptr<CVector>);
   shared_ptr<CVector> Subtract(const shared_ptr<CVector>);
   shared_ptr<CVector> Scale(double);
   shared_ptr<CVector> Normalize();
};
