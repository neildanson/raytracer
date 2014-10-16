#include "CColor.h"

CColor::CColor(double r, double g, double b) : R(r), G(g), B(b) {
}

shared_ptr<CColor> CColor::Add(const shared_ptr<CColor> c) {
   return make_shared<CColor>(this->R + c->R, this->G + c->G, this->B + c->B);
}

shared_ptr<CColor> CColor::Subtract(const shared_ptr<CColor> c) {
   return make_shared<CColor>(this->R - c->R, this->G - c->G, this->B - c->B);
}

shared_ptr<CColor> CColor::Scale(double s) {
   return make_shared<CColor>(this->R * s, this->G * s, this->B * s);
}
shared_ptr<CColor> CColor::Multiply(const shared_ptr<CColor> c) {
   return make_shared<CColor>(this->R * c->R, this->G * c->G, this->B * c->B);
}

int CColor::Legalize(double d) {
   return d > 1.0 ? 255 : (int)(d * 255.0);
}

int CColor::ToColor() {
   int r = this->Legalize(this->R);
   int g = this->Legalize(this->G);
   int b = this->Legalize(this->B);
   return (255 << 24) + (b << 16) + (g << 8) + r;
}