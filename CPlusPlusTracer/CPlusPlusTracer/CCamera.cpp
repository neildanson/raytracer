#include "CCamera.h"

CCamera::CCamera(const shared_ptr<CVector> position, const shared_ptr<CVector> forward, const shared_ptr<CVector> right, const shared_ptr<CVector> up)
   : Position(position), Forward(forward), Right(right), Up(up) {
}

shared_ptr<CCamera> CCamera::CreateCamera(const shared_ptr<CVector> position, const shared_ptr<CVector> lookAt) {
   auto forward = lookAt->Subtract(position)->Normalize();
   auto down = make_shared<CVector>(0.0, -1.0, 0.0);
   auto right = forward->Cross(down)->Normalize()->Scale(1.5);
   auto up = forward->Cross(right)->Normalize()->Scale(1.5);
   return make_shared<CCamera>(position, forward, right, up);
}