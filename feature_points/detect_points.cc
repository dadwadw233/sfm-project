//
// Created by dcr on 2022/1/23.
//

#include "detect_points.h"

#include <utility>
namespace sfmProject {
detect_points::detect_points(std::vector<cv::Mat> &input_images) {
  std::copy(input_images.begin(), input_images.end(), images.begin());
  image_number = input_images.size();
  key_points.resize(image_number);
  descriptors.resize(image_number);
  matches.resize(image_number);
  good_matches.resize(image_number);
  return;
}

detect_points::detect_points(std::string &location) {
  intptr_t file_handle = 0;
  _finddata32_t file_infor;
  cv::Mat temp;
  const char *file_path = location.c_str();
  file_handle = _findfirst32(file_path, &file_infor);

  if (file_handle == -1) {
    std::cout << "error occurred can not find the target file" << std::endl;
  } else {
    std::cout << "successfully find the target file" << std::endl;
    temp = cv::imread(location + '/' + file_infor.name);
    while (_findnext32(file_handle, &file_infor) != -1) {
      images.push_back(temp);
    }
    std::cout << "have successfully read " << images.size() << " images"<<std::endl;
    image_number = images.size();
    key_points.resize(image_number);
    descriptors.resize(image_number);
    matches.resize(image_number);
    good_matches.resize(image_number);
  }
  _findclose(file_handle);
}

/**
 * ues orb to detect the feature points from the input images
 */
void detect_points::find_feature_points() {
  cv::Ptr<cv::ORB> orb = cv::ORB::create();
  for (unsigned int i = 0; i < images.size(); ++i) {
    orb->detect(images[i], key_points[i]);
    orb->compute(images[i], key_points[i], descriptors[i]);
  }
}

/**
 * after find all the feature points.
 * match them between images for other uses
 */
void detect_points::matchFeaturePoints() {
  find_feature_points();
  cv::BFMatcher matcher(cv::NORM_HAMMING);
  double min_distance{10000};
  double max_distance{};
  for (unsigned int i = 0; i < key_points.size(); ++i) {
    min_distance = 100000, max_distance = 0;
    matcher.match(images[0], images[i], matches[i]);
    for (int j = 0; j < descriptors[0].rows; ++j) {
      double distance = matches[0][i].distance;
      min_distance = min_distance < distance ? min_distance : distance;
      max_distance = max_distance > distance ? max_distance : distance;
    }
  }
  for (unsigned int i = 0; i < key_points.size(); ++i) {
    std::vector<cv::DMatch> temp_good_matches;
    for (int j = 0; j < descriptors[0].rows; ++j) {
      if (matches[i][j].distance <= fmax(2 * min_distance, 10.0)) {
        temp_good_matches.push_back(matches[i][j]);
      }
    }
    good_matches.push_back(temp_good_matches);
  }
}

int detect_points::get_image_number() { return image_number; }

/**
 * copy the points in order to compute the R and t between two images
 * @param points
 * @param image_index
 */
void detect_points::copy_key_points(std::vector<cv::Point2f> &points,
                                    const int image_index) {
  points.clear();
  for (int i = 0; i < (int)good_matches[image_index].size(); ++i) {
    points.push_back(
        key_points[image_index][good_matches[image_index][i].queryIdx].pt);
  }
}

void detect_points::pose_estimation_2d2d(detect_points points,
                                         std::vector<cv::Mat> &R,
                                         std::vector<cv::Mat> &t) {
  int focal_length = 521;
  int image_number = points.get_image_number();
  cv::Mat fundamental_matrix;
  cv::Mat essential_matrix;
  cv::Mat homography_matrix;

  std::vector<cv::Point2f> first_image_points;
  std::vector<cv::Point2f> now_image_points;
  cv::Point2d principal_point(640, 360);

  points.copy_key_points(first_image_points, 0);

  for (int i = 1; i < image_number; ++i) {
    points.copy_key_points(now_image_points, i);
    fundamental_matrix = cv::findFundamentalMat(
        first_image_points, now_image_points, cv::FM_8POINT);
    essential_matrix =
        cv::findEssentialMat(first_image_points, now_image_points, focal_length,
                             principal_point, cv::RANSAC);
    cv::recoverPose(essential_matrix, first_image_points, now_image_points,
                    R[i], t[i], focal_length, principal_point);
  }
}
}  // namespace sfmProject
