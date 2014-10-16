#pragma once
#include "CVector.h"
#include "CColor.h"

#include <memory>
using namespace std;

class CLight
{
public:
   const shared_ptr<CVector> Position;
   const shared_ptr<CColor> Color;
   CLight(const shared_ptr<CVector>, const shared_ptr<CColor>);
};
