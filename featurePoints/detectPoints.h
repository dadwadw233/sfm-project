//
// Created by dcr on 2022/1/23.
//

#ifndef SFM_PROJECT_DETECTPOINTS_H
#define SFM_PROJECT_DETECTPOINTS_H
#include "cmath"
#include "opencv2/opencv.hpp"
#include "vector"

class detectPoints {
 private:
  std::vector<cv::Mat> images;
  std::vector<std::vector<cv::KeyPoint>> key_points;
  std::vector<std::vector<cv::Mat>> descriptors;
  std::vector<std::vector<cv::DMatch>> matches;
  std::vector<std::vector<cv::DMatch>> good_matches;

 public:
  ~detectPoints() = delete;
  explicit detectPoints() = delete;
  detectPoints(std::vector<cv::Mat> &input_images);
  void find_feature_points();
  void matchFeaturePoints();
};

#endif  // SFM_PROJECT_DETECTPOINTS_H
