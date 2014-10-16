//g++ *.cpp -std=c++11 -O2
#include "CCamera.h"
#include "CVector.h"
#include "CLight.h"
#include "CSceneObject.h"
#include "CScene.h"
#include "CSphere.h"
#include "CPlane.h"
#include "CShiny.h"
#include "CCheckerboard.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


#include <memory>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char*  argv[])
{
   auto camera = CCamera::CreateCamera(
      make_shared<CVector>(3.0, 2.0, 4.0),
      make_shared<CVector>(-1.0, 0.5, 0.0));

   auto objects = vector<shared_ptr<CSceneObject>>();
   objects.push_back(
      make_shared<CSphere>(
      make_shared<CVector>(0.0, 1.0, 0.0),
      1.0,
      make_shared<CShiny>()));
   objects.push_back(
      make_shared<CSphere>(
      make_shared<CVector>(-1.0, 0.5, 1.5),
      0.5,
      make_shared<CShiny>()));
   objects.push_back(
      make_shared<CPlane>(
      make_shared<CVector>(0.0, 1.0, 0),
      0.0,
      make_shared<CCheckerboard>()));

   auto lights = vector<shared_ptr<CLight>>();
   lights.push_back(
      make_shared<CLight>(
      make_shared<CVector>(-2.0, 2.5, 0.0),
      make_shared<CColor>(0.49, 0.07, 0.07)));
   lights.push_back(
      make_shared<CLight>(
      make_shared<CVector>(1.5, 2.5, 1.5),
      make_shared<CColor>(0.07, 0.07, 0.49)));
   lights.push_back(
      make_shared<CLight>(
      make_shared<CVector>(1.5, 2.5, -1.5),
      make_shared<CColor>(0.07, 0.49, 0.07)));
   lights.push_back(
      make_shared<CLight>(
      make_shared<CVector>(0.0, 3.5, 0.0),
      make_shared<CColor>(0.21, 0.21, 0.21)));
   auto scene = CScene(camera, objects, lights);
   int* result = new int[1920 * 1080];
   clock_t start = clock();
   result = scene.Render(1920, 1080, result);
   clock_t end = clock();
   printf("%f\n", (double)(end - start) / CLOCKS_PER_SEC);
   stbi_write_png("Cpp.png", 1920, 1080, 4, result, 1920 * 4);

   //string str;
   //getline(cin, str);
   return 0;
}