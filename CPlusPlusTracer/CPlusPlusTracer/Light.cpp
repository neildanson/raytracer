#include "Light.h"

CLight::CLight(CVector position, CColor CColor) : Position(position), Color(CColor) {
}

CColor CLight::GetColor() {
	return this->Color;
}
CVector CLight::GetPosition() {
	return this->Position;
}