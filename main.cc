#include <iostream>
#include "direct.h"
#include "feature_points/detect_points.h"
#include "pose_estimate.h"

int main() {
  std::string image_files = R"(./images/all_images.txt)";
  std::cout<<"the target file is :"<<image_files<<std::endl;
  sfmProject::detectPoints points(image_files);
  return 0;
}
