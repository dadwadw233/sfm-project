#include <iostream>
#include "ctime"
#include "feature_points/detect_points.h"

using namespace sfmProject;

void get_file_names(std::string path, std::vector<std::string> &file_names) {}

int main() {
  long int a, b;
  a = clock();
  std::string path = R"(.\out\2022_01_29_21_10_10\color\*.png)";
  std::string path2 = "/home/yyh/sfm-project/out/2022_01_29_21_10_10/color/";
  std::string path3 = "/home/dcr/sfm-project/out/2022_01_29_21_10_10/color/";
  detect_points points(path3);

  int image_number = points.get_image_number();

  std::vector<cv::Mat> R;
  std::vector<cv::Mat> t;
  R.resize(image_number), t.resize(image_number);

  get_R_t(points, R, t);
  b = clock();
  std::cout << b - a << std::endl;

  points.test_function();

  return 0;
}