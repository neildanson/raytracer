#pragma once
#include "CVector.h"
#include "CColor.h"

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
