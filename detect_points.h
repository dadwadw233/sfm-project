//
// Created by dcr on 2022/1/23.
//

#ifndef SFM_PROJECT_DETECT_POINTS_H
#define SFM_PROJECT_DETECT_POINTS_H

#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <thread>
#include <vector>

#include "opencv2/opencv.hpp"


namespace sfmProject {
    class detect_points {
    private:
//        int image_number{};
//        std::vector<cv::Mat> images;
        std::vector<cv::Mat> descriptors_;
        std::vector<std::vector<cv::KeyPoint>> key_points_;
        std::vector<std::vector<cv::DMatch>> matches_;

        cv::Mat k = (cv::Mat_<double>(3, 3) << 951.432064, 0.000000, 652.394558,
                0.000000, 959.549543, 412.655670, 0.000000, 0.000000, 1.000000);

    public:
        ~detect_points() = default;

        explicit detect_points() = delete;

        explicit detect_points(const int image_size);


        void find_feature_points(int i);

        void matchFeaturePoints(int i);

        int get_image_number() const;

        void copy_key_points(std::vector<cv::Point2f> &points1, std::vector<cv::Point2f> &points2, int image_index);

        void test_function();

        friend void pose_estimation_2d2d(detect_points &points, cv::Mat &R, cv::Mat &t, int index);

        friend void get_R_t(detect_points &points, std::vector<cv::Mat> &R, std::vector<cv::Mat> &t);
    };
}  // namespace sfmProject
#endif  // SFM_PROJECT_DETECT_POINTS_H//
