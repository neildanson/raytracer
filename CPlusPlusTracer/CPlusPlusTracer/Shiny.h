#pragma once
#include "Surface.h"

#include <memory>
using namespace std;

class CShiny : public CSurface
{
public:
   double Roughness();
   CColor Diffuse(CVector);
   CColor Specular(CVector);
   double Reflect(CVector);
};
