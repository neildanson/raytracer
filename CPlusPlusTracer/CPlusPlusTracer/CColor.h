#pragma once

#include <math.h>
#include <memory>
using namespace std;

class CColor
{
   double R, G, B;
   int Legalize(double);
public:
   CColor(double r, double g, double b);
   CColor Add(CColor c);
   CColor Subtract(CColor c);
   CColor Scale(double s);
   CColor Multiply(CColor c);
   int ToColor();
};
