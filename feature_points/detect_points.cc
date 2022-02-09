//
// Created by dcr on 2022/1/23.
//

#include "detect_points.h"

#include <utility>
#include <functional>

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

detect_points::detect_points(const std::string &location) {
  // Linux edition
  DIR *pDir;
  struct dirent *ptr;

  if (!(pDir = opendir(location.c_str()))) {
    std::cout << "the root is " << location << std::endl;
    std::cout << "can not get the file ptr , check the dir location";
    return;
  }

  while ((ptr = readdir(pDir)) != nullptr) {
    // 这里我理解他的指针应该是自动会指向到下一个文件，所以不用写指针的移动
    std::string sub_file =
        location + "/" + ptr->d_name;  // 当前指针指向的文件名
    if (ptr->d_type != 8 &&
        ptr->d_type !=
            4) {  // 递归出口，当不是普通文件（8）和文件夹（4）时退出递归
      return;
    }
    cv::Mat temp;
    // 普通文件直接加入到files
    if (ptr->d_type == 8) {
      // 相当于将命令下使用ls展示出来的文件中除了. 和 ..全部保存在files中
      // 当然下面可以写各种字符串的筛选逻辑，比如只要后缀有.jpg图片
      if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0) {
        if (strstr(ptr->d_name, ".png")) {
          temp = cv::imread(location + ptr->d_name);
          std::cout << ptr->d_name << " ";
          images.push_back(temp);
        }
      }
    }
  }
  std::cout << std::endl;
  image_number = images.size();
  key_points.resize(image_number);
  descriptors.resize(image_number);
  matches.resize(image_number);
  good_matches.resize(image_number);
  std::cout << "have successfully read " << images.size() << " images"
            << std::endl;
  // 关闭根目录
  std::cout << "test: " << images[0].size << std::endl;
  closedir(pDir);

  // windows edition
  /*intptr_t file_handle = 0;
  _finddata32_t file_infor{};
  cv::Mat temp;
  char *file_path = new char[location.size() + 1];
  strcpy_s(file_path, location.size() + 1, location.c_str());
  std::string target(location, 0, location.size() - 5);
  file_handle = _findfirst32(file_path, &file_infor);

  if (file_handle == -1) {
      std::cout << "error occurred!!! can not find the target file" <<
  std::endl; } else { begin_image = cv::imread(target + file_infor.name);
      cv::Ptr<cv::ORB> orb = cv::ORB::create(500, 1.2f, 8, 31, 0, 2,
  cv::ORB::HARRIS_SCORE, 31, 20); orb->detect(begin_image,
  begin_image_key_points); orb->compute(begin_image, begin_image_key_points,
  begin_image_descriptors); while (_findnext32(file_handle, &file_infor) != -1)
  { temp = cv::imread(target + file_infor.name); images.push_back(temp);
      }
      _findclose(file_handle);
  }*/

  image_number = images.size();
  key_points.resize(image_number);
  descriptors.resize(image_number);
  matches.resize(image_number);
  good_matches.resize(image_number);
//  delete[] file_path;

  std::cout << "have successfully read " << image_number << " images"
            << std::endl;
}

/**
 *
 * @param i
 */
void detect_points::find_feature_points(int i) {
  cv::Ptr<cv::ORB> orb =
      cv::ORB::create(500, 1.2f, 8, 31, 0, 2, cv::ORB::HARRIS_SCORE, 31, 20);
  orb->detect(images[i], key_points[i]);
  orb->compute(images[i], key_points[i], descriptors[i]);
}

/**
 *
 * @param i
 */
void detect_points::matchFeaturePoints(int i) {
  double min_distance{10000};
  double max_distance{};
  cv::BFMatcher matcher(cv::NORM_HAMMING);
  matcher.match(begin_image_descriptors, descriptors[i], matches[i]);
  // for (unsigned int i = 0; i < key_points.size(); ++i) {
  //     min_distance = 100000, max_distance = 0;
  //     for (int j = 0; j < descriptors[0].rows; ++j) {
  //       double distance = matches[0][i].distance;
  //       min_distance = min_distance < distance ? min_distance : distance;
  //       max_distance = max_distance > distance ? max_distance : distance;
  //     }
  //   }
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
  //        std::cout << "have successfully matched all the feature points" <<
  //        std::endl;
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
    points1.push_back(
        begin_image_key_points[matches[image_index][i].queryIdx].pt);
    points2.push_back(
        key_points[image_index][matches[image_index][i].trainIdx].pt);
  }
}

void pose_estimation_2d2d(detect_points &points, cv::Mat &R, cv::Mat &t,
                          int index) {
  double focal_length = 951.432;
  //        cv::Mat fundamental_matrix;
  cv::Mat essential_matrix;
  //        cv::Mat homography_matrix;

  std::vector<cv::Point2f> first_image_points;
  std::vector<cv::Point2f> now_image_points;
  cv::Point2d principal_point(966.617, 532.934);

  points.copy_key_points(first_image_points, now_image_points, index);
  //            fundamental_matrix =
  //                    cv::findFundamentalMat(first_image_points,
  //                    now_image_points);
  //            homography_matrix =
  //                    cv::findHomography(first_image_points,
  //                    now_image_points);
  essential_matrix =
      cv::findEssentialMat(first_image_points, now_image_points, focal_length,
                           principal_point, cv::RANSAC);
  cv::recoverPose(essential_matrix, first_image_points, now_image_points, R, t,
                  focal_length, principal_point);

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

void fuc(detect_points &points, std::vector<cv::Mat> &R,
         std::vector<cv::Mat> &t, int i) {
  points.find_feature_points(i);
  points.matchFeaturePoints(i);
  pose_estimation_2d2d(points, std::ref(R[i]), t[i], i);
}

void get_R_t(detect_points &points, std::vector<cv::Mat> &R,
             std::vector<cv::Mat> &t) {
  std::vector<std::thread> all_threads;
  for (int i = 0; i < points.image_number; ++i) {
    all_threads.push_back(
        std::thread{fuc, std::ref(points), std::ref(R), std::ref(t), i});
    std::cout << i << std::endl;
  }
  std::for_each(all_threads.begin(), all_threads.end(),
                std::mem_fn(&std::thread::join));
}

}  // namespace sfmProject