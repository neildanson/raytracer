#pragma once
#include "CSurface.h"

#include <memory>
using namespace std;

class CShiny : public CSurface
{
public:
   double Roughness();
   shared_ptr<CColor> Diffuse(const shared_ptr<CVector>);
   shared_ptr<CColor> Specular(const shared_ptr<CVector>);
   double Reflect(const shared_ptr<CVector>);
};
