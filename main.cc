#include <iostream>
#include "ctime"
#include "feature_points/detect_points.h"
#include "thread"
using namespace sfmProject;

void get_file_names(std::string path, std::vector<std::string> &file_names) {}
int main() {
  int a, b;
  a = clock();
  std::string path = R"(.\out\2022_01_29_21_10_10\color\*.png)";
  std::string path2 = "/home/yyh/sfm-project/out/2022_01_29_21_10_10/color/";
  detect_points points(path);

  int image_number = points.get_image_number();

  std::vector<cv::Mat> R;
  std::vector<cv::Mat> t;
  R.resize(image_number), t.resize(image_number);

  points.matchFeaturePoints();

  pose_estimation_2d2d(points, R, t);
  b = clock();
  std::cout << b - a << std::endl;
  return 0;
}