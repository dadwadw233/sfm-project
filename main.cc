#include <iostream>
#include "feature_points/detect_points.h"
using namespace sfmProject;

int main() {
  std::string image_file = R"(./out/2022_01_29_21_10_10/color)";
  detect_points images(image_file);
  return 0;
}