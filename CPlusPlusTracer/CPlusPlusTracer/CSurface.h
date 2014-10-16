#pragma once
#include "CColor.h"
#include "CVector.h"

#include <memory>
using namespace std;

class CSurface
{
public:
   virtual double Roughness() = 0;
   virtual shared_ptr<CColor> Diffuse(const shared_ptr<CVector>) = 0;
   virtual shared_ptr<CColor> Specular(const shared_ptr<CVector>) = 0;
   virtual double Reflect(const shared_ptr<CVector>) = 0;
};
