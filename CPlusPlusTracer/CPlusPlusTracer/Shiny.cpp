#include "Shiny.h"

double CShiny::Roughness() {
   return 50.0;
}

CColor CShiny::Diffuse(CVector position) {
   return CColor(1.0, 1.0, 1.0);
}

CColor CShiny::Specular(CVector position) {
   return CColor(0.5, 0.5, 0.5);
}

double CShiny::Reflect(CVector position) {
   return 0.3;
}