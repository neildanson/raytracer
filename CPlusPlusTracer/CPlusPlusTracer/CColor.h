#pragma once

#include <math.h>
#include <memory>
using namespace std;

class CColor
{
   int Legalize(double);
public:
   const double R, G, B;
   CColor(double r, double g, double b);
   shared_ptr<CColor> Add(const shared_ptr<CColor> c);
   shared_ptr<CColor> Subtract(const shared_ptr<CColor> c);
   shared_ptr<CColor> Scale(double s);
   shared_ptr<CColor> Multiply(const shared_ptr<CColor> c);
   int ToColor();
};
