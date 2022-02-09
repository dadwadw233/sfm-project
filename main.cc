#include <iostream>
#include "feature_points/detect_points.h"
#include "pose_estimate.h"
#include "thread"
using namespace sfmProject;
cv::Mat pose_estimate::K;  // init the static var

void get_file_names(std::string path, std::vector<std::string> &file_names) {}
int main() {
  std::string path = "/home/yyh/sfm-project/out/2022_01_29_21_10_10/color/";
  detect_points points(path);

  int image_number = points.get_image_number();

  std::vector<cv::Mat> R;
  std::vector<cv::Mat> t;
  R.resize(image_number), t.resize(image_number);

  points.matchFeaturePoints();

  pose_estimation_2d2d(points, R, t);
  pose_estimate P;

  P.poseGeneration(R, t);

  return 0;
}