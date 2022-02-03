//
// Created by dcr on 2022/1/23.
//

#ifndef SFM_PROJECT_DETECT_POINTS_H
#define SFM_PROJECT_DETECT_POINTS_H
#include "cmath"
#include "vector"
#include "string"
#include "fstream"
#include "io.h"
#include "opencv2/opencv.hpp"

namespace sfmProject {
class detect_points {
 private:
  int image_number{};
  std::vector<cv::Mat> images;
  std::vector<std::vector<cv::Mat>> descriptors;
  std::vector<std::vector<cv::DMatch>> matches;
  std::vector<std::vector<cv::KeyPoint>> key_points;
  std::vector<std::vector<cv::DMatch>> good_matches;

 public:
  ~detect_points() = default;

  explicit detect_points() = delete;

  detect_points(std::vector<cv::Mat> &input_images);

  detect_points(const std::string &image_file_name);

  void find_feature_points();

  void matchFeaturePoints();

  int get_image_number();

  void copy_key_points(std::vector<cv::Point2f> &points, int image_index);

  void pose_estimation_2d2d(detect_points points, std::vector<cv::Mat>& R,
                            std::vector<cv::Mat>& t);
};
}  // namespace sfmProject
#endif  // SFM_PROJECT_DETECT_POINTS_H//
