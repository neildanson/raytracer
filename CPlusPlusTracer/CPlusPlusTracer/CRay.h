#pragma once
#include "CVector.h"

#include <memory>
using namespace std;
class CRay
{
public:
   const shared_ptr<CVector> Position, Direction;
   CRay(shared_ptr<CVector>, shared_ptr<CVector>);
};
