#include "CCamera.h"

CCamera::CCamera(CVector position, CVector forward, CVector right, CVector up)
   : Position(position), Forward(forward), Right(right), Up(up) {
}

CCamera CCamera::CreateCamera(CVector position, CVector lookAt) {
   auto forward = lookAt.Subtract(position).Normalize();
   auto down = CVector(0.0, -1.0, 0.0);
   auto right = forward.Cross(down).Normalize().Scale(1.5);
   auto up = forward.Cross(right).Normalize().Scale(1.5);
   return CCamera(position, forward, right, up);
}

CVector CCamera::GetPosition() {
	return this->Position;
}

CVector CCamera::GetForward() {
	return this->Forward;
}

CVector CCamera::GetUp() {
	return this->Up;
}

CVector CCamera::GetRight() {
	return this->Right;
}