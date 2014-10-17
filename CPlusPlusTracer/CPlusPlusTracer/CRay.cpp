#include "CRay.h"

CRay::CRay(CVector position, CVector direction) : Position(position), Direction(direction) {
}

CVector CRay::GetPosition() {
   return this->Position;
}

CVector CRay::GetDirection() {
   return this->Direction;
}