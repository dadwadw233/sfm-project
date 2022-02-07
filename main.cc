#include <iostream>
#include "feature_points/detect_points.h"
#include "thread"
using namespace sfmProject;

void get_file_names(std::string path, std::vector<std::string> &file_names) {}
int main() {
  std::string path = R"(..\out\2022_01_29_21_10_10\color\*.png)";
  struct _finddata32_t file_infor {};
  detect_points points(path);

  points.matchFeaturePoints();
  return 0;
}