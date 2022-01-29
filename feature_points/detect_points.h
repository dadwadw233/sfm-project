//
// Created by dcr on 2022/1/23.
//

#ifndef SFM_PROJECT_DETECT_POINTS_H
#define SFM_PROJECT_DETECT_POINTS_H
#include "cmath"
#include "io.h"
#include "vector"
#include "string"
#include "fstream"
#include "opencv2/opencv.hpp"

namespace sfmProject {
class detectPoints {
 private:
  int image_number{};
  std::vector<cv::Mat> images;
  std::vector<std::vector<cv::Mat>> descriptors;
  std::vector<std::vector<cv::DMatch>> matches;
  std::vector<std::vector<cv::KeyPoint>> key_points;
  std::vector<std::vector<cv::DMatch>> good_matches;

 public:
  ~detectPoints() = default;

  explicit detectPoints() = delete;

  detectPoints(std::vector<cv::Mat> &input_images);

  detectPoints(const std::string &image_file_names);

  void find_feature_points();

  void matchFeaturePoints();

  int get_image_number();

  void copy_key_points(std::vector<cv::Point2f> &points, int image_index);
};
}  // namespace sfmProject
#endif  // SFM_PROJECT_DETECT_POINTS_H//
