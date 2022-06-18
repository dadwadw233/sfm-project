//
// Created by dcr on 2022/1/23.
//

#include "detect_points.h"

#include <functional>
#include <utility>

namespace sfmProject {

//cv::Point2d pixel2cam(const cv::Point2d &p, cv::Mat K) {
//  return cv::Point2d((p.x - K.at<double>(0, 2)) / K.at<double>(0, 0),
//                     (p.y - K.at<double>(1, 2)) / K.at<double>(1, 1));
//}
//
//detect_points::detect_points(std::vector<cv::Mat> &input_images) {
//  std::copy(input_images.begin(), input_images.end(), images.begin());
//  image_number = input_images.size();
//  key_points.resize(image_number);
//  descriptors_.resize(image_number);
//  matches_.resize(image_number);
//  good_matches.resize(image_number);
//}
//
//detect_points::detect_points(const std::string &location) {}
//
///**
// *
// * @param i
// */
//void detect_points::find_feature_points(int i) {
//  cv::Ptr<cv::ORB> orb =
//      cv::ORB::create(500, 1.2f, 8, 31, 0, 2, cv::ORB::HARRIS_SCORE, 31, 20);
//  orb->detect(images[i], key_points[i]);
//  orb->compute(images[i], key_points[i], descriptors_[i]);
//}
//
///**
// *
// * @param i
// */
//void detect_points::matchFeaturePoints(int i) {
//  const float min_ratio = 1.f / 1.5f;
//  cv::BFMatcher matcher(cv::NORM_HAMMING, false);
//  std::vector<std::vector<cv::DMatch>> temp_matches;
//  //  matcher.match(begin_image_descriptors, descriptors_[i], matches_[i]);
//  matcher.knnMatch(begin_image_descriptors, descriptors_[i], temp_matches, 2);
//
//  for (auto &temp_match : temp_matches) {
//    const cv::DMatch b_match0 = temp_match[0];
//    const cv::DMatch b_match1 = temp_match[1];
//
//    if (b_match0.distance / b_match1.distance < min_ratio) {
//      matches_[i].push_back(b_match0);
//    }
//  }
//}
//
//int detect_points::get_image_number() const { return image_number; }
//
///**
// *
// * @param points1
// * @param points2
// * @param image_index
// */
//void detect_points::copy_key_points(std::vector<cv::Point2f> &points1,
//                                    std::vector<cv::Point2f> &points2,
//                                    const int image_index) {
//  points1.clear();
//  points2.clear();
//  for (int i = 0; i < (int)matches_[image_index].size(); ++i) {
//    points1.push_back(
//        begin_image_key_points[matches_[image_index][i].queryIdx].pt);
//    points2.push_back(
//        key_points[image_index][matches_[image_index][i].trainIdx].pt);
//  }
//}
//
//void pose_estimation_2d2d(detect_points &points, cv::Mat &R, cv::Mat &t,
//                          int index) {
//  double focal_length = 951.432;
//  //        cv::Mat fundamental_matrix;
//  cv::Mat essential_matrix;
//  //        cv::Mat homography_matrix;
//
//  std::vector<cv::Point2f> first_image_points;
//  std::vector<cv::Point2f> now_image_points;
//  cv::Point2d principal_point(966.617, 532.934);
//
//  points.copy_key_points(first_image_points, now_image_points, index);
//  //            fundamental_matrix =
//  //                    cv::findFundamentalMat(first_image_points,
//  //                    now_image_points);
//  //            homography_matrix =
//  //                    cv::findHomography(first_image_points,
//  //                    now_image_points);
//  essential_matrix =
//      cv::findEssentialMat(first_image_points, now_image_points, focal_length,
//                           principal_point, cv::RANSAC);
//  cv::recoverPose(essential_matrix, first_image_points, now_image_points, R, t,
//                  focal_length, principal_point);
//  //    std::cout<<R[i].size<<' '<<t[i].size<<std::endl;
//
//  // verify the R and t
//  /*for (int j = 0; j < points.matches_[i].size(); ++j) {
//    cv::Mat t_x = (cv::Mat_<double>(3, 3) << 0, t[i].at<double>(2, 0),
//                   t[i].at<double>(1, 0), t[i].at<double>(2, 0), 0,
//                   -t[i].at<double>(0, 0), -t[i].at<double>(1, 0),
//                   t[i].at<double>(0, 0), 0);
//    cv::Point2d point1 =
//        pixel2cam(points.key_points[0][points.matches_[i][j].queryIdx].pt, k);
//    cv::Point2d point2 =
//        pixel2cam(points.key_points[i][points.matches_[i][j].trainIdx].pt, k);
//    cv::Mat y1 = (cv::Mat_<double>(3, 1) << point1.x, point1.y, 1);
//    cv::Mat y2 = (cv::Mat_<double>(3, 1) << point2.x, point2.y, 1);
//
//    cv::Mat d = y2.t() * t_x * R[i] * y1;
//  }*/
//}
//
//void detect_points::test_function() {
//  cv::Mat outImage;
//  for (int i = 0; i < image_number; ++i) {
//    cv::drawMatches(begin_image, begin_image_key_points, images[i],
//                    key_points[i], matches_[i], outImage);
//    cv::imshow("matches_", outImage);
//    cv::waitKey(0);
//  }
//}
//
//void fuc(detect_points &points, std::vector<cv::Mat> &R,
//         std::vector<cv::Mat> &t, int i) {
//  points.find_feature_points(i);
//  points.matchFeaturePoints(i);
//  //  pose_estimation_2d2d(points, std::ref(R[i]), t[i], i);
//}
//
//void get_R_t(detect_points &points, std::vector<cv::Mat> &R,
//             std::vector<cv::Mat> &t) {
//  std::vector<std::thread> all_threads;
//  for (int i = 0; i < points.image_number; ++i) {
//    all_threads.push_back(
//        std::thread{fuc, std::ref(points), std::ref(R), std::ref(t), i});
//    //    std::cout << i << std::endl;
//  }
//  std::for_each(all_threads.begin(), all_threads.end(),
//                std::mem_fn(&std::thread::join));
//}

detect_points::detect_points(const int image_size) {
  descriptors_.resize(image_size);
  matches_.resize(image_size);
  key_points_.resize(image_size);
}
}  // namespace sfmProject