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
  std::vector<cv::Mat> imgs;
  std::vector<std::vector<cv::KeyPoint>> keyPoints;
  std::vector<std::vector<cv::Mat>> descriptors;
  std::vector<std::vector<cv::DMatch>> matches;
  std::vector<std::vector<cv::DMatch>> goodMatches;

 public:
  ~detectPoints() = delete;
  detectPoints() = delete;
  detectPoints(std::vector<cv::Mat> inputImgs);
  void findFeaturePoints();
  void matchFeaturePoints();
};

#endif  // SFM_PROJECT_DETECTPOINTS_H
