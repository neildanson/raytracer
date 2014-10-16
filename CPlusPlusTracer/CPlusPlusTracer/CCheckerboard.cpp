#include "CCheckerboard.h"

double CCheckerboard::Roughness() {
   return 150.0;
}

shared_ptr<CColor> CCheckerboard::Diffuse(const shared_ptr<CVector> pos) {
   return fmod(floor(pos->X) + floor(pos->Z), 2.0) != 0 ? 
      make_shared<CColor>(1.0,1.0,1.0) : 
      make_shared<CColor>(0.0,0.0,0.0);
}

shared_ptr<CColor> CCheckerboard::Specular(const shared_ptr<CVector> pos) {
   return make_shared<CColor>(1.0, 1.0, 1.0);
}

double CCheckerboard::Reflect(const shared_ptr<CVector> pos) {
   return fmod(floor(pos->X) + floor(pos->Z), 2.0) != 0 ? 1.0 : 0.7;
}
