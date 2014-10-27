#include "Color.h"

CColor::CColor(double r, double g, double b) : R(r), G(g), B(b) {
}

CColor CColor::Add(CColor c) {
   return CColor(this->R + c.R, this->G + c.G, this->B + c.B);
}

CColor CColor::Subtract(CColor c) {
   return CColor(this->R - c.R, this->G - c.G, this->B - c.B);
}

CColor CColor::Scale(double s) {
   return CColor(this->R * s, this->G * s, this->B * s);
}

CColor CColor::Multiply(CColor c) {
   return CColor(this->R * c.R, this->G * c.G, this->B * c.B);
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