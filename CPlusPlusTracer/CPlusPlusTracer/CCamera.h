#pragma once
#include "CVector.h"

#include <memory>
using namespace std;

class CCamera
{
public:
   shared_ptr<CVector> Position, Forward, Up, Right;
   CCamera(const shared_ptr<CVector> position, const shared_ptr<CVector> forward, shared_ptr<CVector> up, shared_ptr<CVector> right);
   static shared_ptr<CCamera> CreateCamera(const shared_ptr<CVector>, const shared_ptr<CVector>);
};
