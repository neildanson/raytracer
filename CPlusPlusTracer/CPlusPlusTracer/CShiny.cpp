#include "CShiny.h"

double CShiny::Roughness() {
   return 50.0;
}

shared_ptr<CColor> CShiny::Diffuse(const shared_ptr<CVector> position) {
   return make_shared<CColor>(1.0, 1.0, 1.0);
}

shared_ptr<CColor> CShiny::Specular(const shared_ptr<CVector> position) {
   return make_shared<CColor>(0.5, 0.5, 0.5);
}

double CShiny::Reflect(const shared_ptr<CVector> position) {
   return 0.3;
}