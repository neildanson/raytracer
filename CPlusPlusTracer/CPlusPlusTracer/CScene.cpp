#include "CScene.h"

CScene::CScene(shared_ptr<CCamera> camera,
   vector<shared_ptr<CSceneObject>> objects,
   vector<shared_ptr<CLight>> lights)
   : Camera(camera), Objects(objects), Lights(lights) {
}

shared_ptr<CIntersection> CScene::Intersection(const shared_ptr<CRay> ray) {
   shared_ptr<CIntersection> intersection = nullptr;
   for (int i = 0; i < this->Objects.size(); i++) {
      auto object = this->Objects[i];
      auto isect = object->Intersects(ray);
      if (isect != nullptr) {
         if (intersection == nullptr) {
            intersection = isect;
         }
         else if (isect->Distance < intersection->Distance) {
            intersection = isect;
         }
      }
   }
   return intersection;
}

double CScene::TestRay(const shared_ptr<CRay> ray) {
   auto intersection = this->Intersection(ray);
   return intersection == nullptr ? 0.0 : intersection->Distance;
}

shared_ptr<CColor> CScene::TraceRay(const shared_ptr<CRay> ray, int depth) {
   auto black = make_shared<CColor>(0.0, 0.0, 0.0);
   auto intersection = this->Intersection(ray);
   return intersection == nullptr ? black : this->Shade(intersection, depth);
}

shared_ptr<CColor> CScene::Shade(shared_ptr<CIntersection> intersection, int depth) {
   auto pos = intersection->Ray->Direction->Scale(intersection->Distance)->Add(intersection->Ray->Position);
   auto normal = intersection->Object->Normal(pos);
   auto dot = normal->Dot(intersection->Ray->Direction);
   auto reflectDir = intersection->Ray->Direction->Subtract(normal->Scale(2.0 * dot));
   auto natural = this->GetNaturalColor(intersection->Object, pos, normal, reflectDir);
   if (depth < 5) {
      auto reflectPos = reflectDir->Scale(0.0001)->Add(pos);
      auto reflectColor = this->GetReflectionColor(intersection->Object, reflectPos, reflectDir, depth);
      return natural->Add(reflectColor);
   }
   auto grey = make_shared<CColor>(0.5, 0.5, 0.5);
   return grey->Add(natural);
}

shared_ptr<CColor> CScene::GetNaturalColor(const shared_ptr<CSceneObject> object, const shared_ptr<CVector> position, const shared_ptr<CVector> normal, const shared_ptr<CVector> rayDirection) {
   auto black = make_shared<CColor>(0.0, 0.0, 0.0);
   auto result = black;
   for (int i = 0; i < this->Lights.size(); i++) {
      auto light = this->Lights[i];
      auto lightDistance = light->Position->Subtract(position);
      auto livec = lightDistance->Normalize();
      auto ray = make_shared<CRay>(position, livec);
      auto isect = this->TestRay(ray);
      auto isInShadow = (isect > lightDistance->Length() || isect == 0.0);
      if (isInShadow) {
         auto illum = livec->Dot(normal);
         auto lcolor = illum > 0 ? light->Color->Scale(illum) : black;
         auto normalizedRayDirection = rayDirection->Normalize();
         auto specular = livec->Dot(normalizedRayDirection);
         auto scolor = specular > 0.0 ? light->Color->Scale(pow(specular, object->GetSurface()->Roughness())):black;
         auto diffuseResult = object->GetSurface()->Diffuse(position)->Multiply(lcolor);
         auto specularResult = object->GetSurface()->Specular(position)->Multiply(scolor);
         result = result->Add(diffuseResult)->Add(specularResult);
      }
   }

   return result;
}

shared_ptr<CColor> CScene::GetReflectionColor(const shared_ptr<CSceneObject> object, const shared_ptr<CVector> pos, const shared_ptr<CVector> rayDirection, int depth) {
   auto ray = make_shared<CRay>(pos, rayDirection);
   return this->TraceRay(ray, depth + 1)->Scale(object->GetSurface()->Reflect(pos));
}

double CScene::RecenterX(int x, double halfWidth, double invWidth) {
   double fx = (double)x;
   return (fx - halfWidth) * invWidth;
}

double CScene::RecenterY(int y, double halfHeight, double invHeight) {
   double fy = (double)y;
   return -(fy - halfHeight) * invHeight;
}

shared_ptr<CVector> CScene::GetPoint(int x, int y, double halfWidth, double halfHeight, double invWidth, double invHeight, const shared_ptr<CCamera> camera) {
   auto right = camera->Right->Scale(this->RecenterX(x, halfWidth, invWidth));
   auto up = camera->Up->Scale(this->RecenterY(y, halfHeight, invHeight));
   return right->Add(up)->Add(camera->Forward)->Normalize();
}

int* CScene::Render(int width, int height, int* result) {
   auto fWidth = (double)width;
   auto fHeight = (double)height;
   auto inverseAspectRatio = fHeight / fWidth;
   auto scaleWidth = fWidth * inverseAspectRatio;
   auto halfWidth = scaleWidth / 2.0;
   auto halfHeight = fHeight / 2.0;
   auto invWidth = 1.0 / (scaleWidth * 2.0);
   auto invHeight = 1.0 / (fHeight * 2.0);

   int basey = 0;
   for (int y = 0; y < height; y++) {
      basey = y * width;
      for (int x = 0; x < width; x++) {
         auto rayDir = this->GetPoint(x, y, halfWidth, halfHeight, invWidth, invHeight, this->Camera);
         auto ray = make_shared<CRay>(this->Camera->Position, rayDir);
         result[basey + x] = this->TraceRay(ray, 0)->ToColor();
      }
   }
   return result;
}