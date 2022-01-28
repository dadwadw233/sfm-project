//
// Created by dcr on 2022/1/23.
//

#ifndef SFM_PROJECT_DETECT_POINTS_H
#define SFM_PROJECT_DETECT_POINTS_H
#include "cmath"
#include "opencv2/opencv.hpp"
#include "vector"

class detect_points {
 private:
  std::vector<cv::Mat> images;
  std::vector<std::vector<cv::KeyPoint>> key_points;
  std::vector<std::vector<cv::Mat>> descriptors;
  std::vector<std::vector<cv::DMatch>> matches;
  std::vector<std::vector<cv::DMatch>> good_matches;

 public:
  ~detect_points() = delete;
  explicit detect_points() = delete;
  detect_points(std::vector<cv::Mat> &input_images);
  void find_feature_points();
  void matchFeaturePoints();
};

#endif  // SFM_PROJECT_DETECT_POINTS_H
