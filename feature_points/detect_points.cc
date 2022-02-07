//
// Created by dcr on 2022/1/23.
//

#include "detect_points.h"

#include <utility>
namespace sfmProject {

cv::Point2d pixel2cam(const cv::Point2d &p, cv::Mat K) {
  return cv::Point2d((p.x - K.at<double>(0, 2)) / K.at<double>(0, 0),
                     (p.y - K.at<double>(1, 2)) / K.at<double>(1, 1));
}

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
  _finddata32_t file_infor{};
  cv::Mat temp;
  char *file_path = new char[location.size() + 1];
  strcpy_s(file_path, location.size() + 1, location.c_str());
  std::string target(location, 0, location.size() - 5);
  file_handle = _findfirst32(file_path, &file_infor);

  if (file_handle == -1) {
    std::cout << "error occurred!!! can not find the target file" << std::endl;
  } else {
    temp = cv::imread(target + file_infor.name);
    images.push_back(temp);

    while (_findnext32(file_handle, &file_infor) != -1) {
      temp = cv::imread(target + file_infor.name);
      images.push_back(temp);
    }

    image_number = images.size();
    key_points.resize(image_number);
    descriptors.resize(image_number);
    matches.resize(image_number);
    good_matches.resize(image_number);
  }
  std::cout << "have successfully read " << images.size() << " images"
            << std::endl;
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
  std::cout << "have successfully found all the feature points" << std::endl;
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
    //    min_distance = 100000, max_distance = 0;
    matcher.match(descriptors[0], descriptors[i], matches[i]);
    //    for (int j = 0; j < descriptors[0].rows; ++j) {
    //      double distance = matches[0][i].distance;
    //      min_distance = min_distance < distance ? min_distance : distance;
    //      max_distance = max_distance > distance ? max_distance : distance;
    //    }
  }
//  std::cout << "have successfully found all the match points" << std::endl;

//  for (unsigned int i = 0; i < key_points.size(); ++i) {
//    std::vector<cv::DMatch> temp_good_matches;
//    for (int j = 0; j < descriptors[0].rows; ++j) {
//      if (matches[i][j].distance <= fmax(2 * min_distance, 10.0)) {
//        temp_good_matches.push_back(matches[i][j]);
//      }
//    }
//    good_matches.push_back(temp_good_matches);
//  }
  std::cout << "have successfully matched all the feature points" << std::endl;
}
int detect_points::get_image_number() { return image_number; }
/**
 *
 * @param points1
 * @param points2
 * @param image_index
 */
void detect_points::copy_key_points(std::vector<cv::Point2f> &points1,
                                    std::vector<cv::Point2f> &points2,
                                    const int image_index) {
  points1.clear();
  points2.clear();
  for (int i = 0; i < (int)matches[image_index].size(); ++i) {
    points1.push_back(key_points[0][matches[image_index][i].queryIdx].pt);
    points2.push_back(
        key_points[image_index][matches[image_index][i].trainIdx].pt);
  }
}

void pose_estimation_2d2d(detect_points points,
                                         std::vector<cv::Mat> &R,
                                         std::vector<cv::Mat> &t) {
  cv::Mat k = (cv::Mat_<double>(3, 3) << 951.432064, 0.000000, 652.394558,
               0.000000, 959.549543, 412.655670, 0.000000, 0.000000, 1.000000);
  double focal_length = 1395.12;
  cv::Mat fundamental_matrix;
  cv::Mat essential_matrix;
  cv::Mat homography_matrix;

  std::vector<cv::Point2f> first_image_points;
  std::vector<cv::Point2f> now_image_points;
  cv::Point2d principal_point(640, 360);

  for (int i = 1; i < points.image_number; ++i) {
    points.copy_key_points(first_image_points, now_image_points, i);
    fundamental_matrix =
        cv::findFundamentalMat(first_image_points, now_image_points);
    homography_matrix =
        cv::findHomography(first_image_points, now_image_points);
    essential_matrix =
        cv::findEssentialMat(first_image_points, now_image_points, focal_length,
                             principal_point, cv::RANSAC);
    cv::recoverPose(essential_matrix, first_image_points, now_image_points,
                    R[i], t[i], focal_length, principal_point);

    std::cout<<R[i].size<<' '<<t[i].size<<std::endl;

    // verify the R and t
    /*for (int j = 0; j < points.matches[i].size(); ++j) {
      cv::Mat t_x = (cv::Mat_<double>(3, 3) << 0, t[i].at<double>(2, 0),
                     t[i].at<double>(1, 0), t[i].at<double>(2, 0), 0,
                     -t[i].at<double>(0, 0), -t[i].at<double>(1, 0),
                     t[i].at<double>(0, 0), 0);
      cv::Point2d point1 =
          pixel2cam(points.key_points[0][points.matches[i][j].queryIdx].pt, k);
      cv::Point2d point2 =
          pixel2cam(points.key_points[i][points.matches[i][j].trainIdx].pt, k);
      cv::Mat y1 = (cv::Mat_<double>(3, 1) << point1.x, point1.y, 1);
      cv::Mat y2 = (cv::Mat_<double>(3, 1) << point2.x, point2.y, 1);

      cv::Mat d = y2.t() * t_x * R[i] * y1;
    }*/
  }
  std::cout << "have successfully computed all the R and t" << std::endl;
}
}  // namespace sfmProject
