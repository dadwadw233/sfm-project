//
// Created by dcr on 2022/1/23.
//

#ifndef SFM_PROJECT_DETECT_POINTS_H
#define SFM_PROJECT_DETECT_POINTS_H
#include "cmath"
#include "opencv2/opencv.hpp"
#include "vector"

namespace sfmProject {
class detectPoints {
 private:
  static int image_number;
  std::vector<cv::Mat> images;
  std::vector<std::vector<cv::Mat>> descriptors;
  std::vector<std::vector<cv::DMatch>> matches;
  static std::vector<std::vector<cv::KeyPoint>> key_points;
  static std::vector<std::vector<cv::DMatch>> good_matches;

 public:
  ~detectPoints() = default;

  explicit detectPoints() = delete;

  detectPoints(std::vector<cv::Mat> &input_images);

  void find_feature_points();

  void matchFeaturePoints();

  static int get_image_number();

  static void copy_key_points(std::vector<cv::Point2f> &points,
                              int image_index);
};
}  // namespace sfmProject
#endif  // SFM_PROJECT_DETECT_POINTS_H
