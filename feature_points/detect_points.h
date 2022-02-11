//
// Created by dcr on 2022/1/23.
//

#ifndef SFM_PROJECT_DETECT_POINTS_H

#include "cmath"
#include "cstring"
#include "fstream"
#include "opencv2/opencv.hpp"
#include "string"
#include "thread"
#include "vector"
#include "dirent.h"
//#include "direct.h"
//#include <io.h>

namespace sfmProject {
    class detect_points {
    private:
        int image_number{};
        std::vector<cv::Mat> images;
        std::vector<cv::Mat> descriptors;
        std::vector<std::vector<cv::KeyPoint>> key_points;
        std::vector<std::vector<cv::DMatch>> matches;
        std::vector<std::vector<cv::DMatch>> good_matches;

        cv::Mat begin_image;
        std::vector<cv::KeyPoint> begin_image_key_points;
        cv::Mat begin_image_descriptors;
        cv::Mat k = (cv::Mat_<double>(3, 3) << 951.432064, 0.000000, 652.394558,
                0.000000, 959.549543, 412.655670, 0.000000, 0.000000, 1.000000);

    public:
        ~detect_points() = default;

        explicit detect_points() = delete;

        explicit detect_points(std::vector<cv::Mat> &input_images);

        explicit detect_points(const std::string &location);

        void find_feature_points(int i);

        void matchFeaturePoints(int i);

        int get_image_number();

        void copy_key_points(std::vector<cv::Point2f> &points1, std::vector<cv::Point2f> &points2, int image_index);

        friend void pose_estimation_2d2d(detect_points &points, cv::Mat &R, cv::Mat &t, int index);

        friend void get_R_t(detect_points &points, std::vector<cv::Mat> &R, std::vector<cv::Mat> &t);
    };
}  // namespace sfmProject
#endif  // SFM_PROJECT_DETECT_POINTS_H//
