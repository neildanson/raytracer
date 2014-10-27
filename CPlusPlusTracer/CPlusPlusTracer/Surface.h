#pragma once
#include "Color.h"
#include "Vector.h"

#include <memory>
using namespace std;

class CSurface
{
public:
   virtual double Roughness() = 0;
   virtual CColor Diffuse(CVector) = 0;
   virtual CColor Specular(CVector) = 0;
   virtual double Reflect(CVector) = 0;
};
