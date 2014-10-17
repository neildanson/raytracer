#include "CCheckerboard.h"

double CCheckerboard::Roughness() {
   return 150.0;
}

CColor CCheckerboard::Diffuse(CVector pos) {
   return fmod(floor(pos.GetX()) + floor(pos.GetZ()), 2.0) != 0 ? 
      CColor(1.0,1.0,1.0) : 
      CColor(0.0,0.0,0.0);
}

CColor CCheckerboard::Specular(CVector pos) {
   return CColor(1.0, 1.0, 1.0);
}

double CCheckerboard::Reflect(CVector pos) {
   return fmod(floor(pos.GetX()) + floor(pos.GetZ()), 2.0) != 0 ? 1.0 : 0.7;
}
