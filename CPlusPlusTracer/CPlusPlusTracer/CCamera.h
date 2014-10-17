#pragma once
#include "CVector.h"

#include <memory>
using namespace std;

class CCamera
{
	CVector Position, Forward, Up, Right;
public:
   CCamera(CVector, CVector, CVector, CVector);
   static CCamera CreateCamera(CVector, CVector);
   CVector GetPosition();
   CVector GetForward();
   CVector GetUp();
   CVector GetRight();
};
