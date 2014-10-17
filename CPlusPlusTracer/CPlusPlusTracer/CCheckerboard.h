#pragma once
#include "CSurface.h"

#include <memory>
using namespace std;

class CCheckerboard : public CSurface
{
public:
   double Roughness();
   CColor Diffuse(CVector);
   CColor Specular(CVector);
   double Reflect(CVector);
};

