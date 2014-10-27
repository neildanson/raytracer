#pragma once
#include "Vector.h"
#include "Color.h"

#include <memory>
using namespace std;

class CLight
{
	CVector Position;
	CColor Color;
public:
   CLight(CVector, CColor);
   CColor GetColor();
   CVector GetPosition();
};
