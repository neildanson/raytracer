#pragma once
#include "Vector.h"

#include <memory>
using namespace std;
class CRay
{
   CVector Position;
   CVector Direction;
public:
   CRay(CVector, CVector);
   CVector GetPosition();
   CVector GetDirection();
};
