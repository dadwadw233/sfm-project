//
// Created by dcr on 2022/1/23.
//

#ifndef LITTLE_TASK_DETECTPOINTS_H
#define LITTLE_TASK_DETECTPOINTS_H
#include "opencv2/opencv.hpp"
#include "vector"
#include "cmath"


class detectPoints {
     std::vector<cv::Mat> imgs;
     std::vector<std::vector<cv::KeyPoint>> keyPoints;
     std::vector<std::vector<cv::Mat>> descriptors;
     std::vector<std::vector<cv::DMatch>> matches;
     std::vector<std::vector<cv::DMatch>> goodMatches;

public:
    ~detectPoints()= default;
    detectPoints()= default;
    detectPoints(std::vector<cv::Mat> inputImgs);
    void findFeaturePoints();
    void matchFeaturePoints();
};


#endif //LITTLE_TASK_DETECTPOINTS_H
