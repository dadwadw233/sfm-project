//
// Created by dcr on 2022/1/23.
//

#include "detectPoints.h"

#include <utility>

detectPoints::detectPoints(std::vector<cv::Mat> inputImgs) {
    std::copy(imgs.begin(), imgs.end(), std::move(inputImgs));
    keyPoints.resize(imgs.size());
    descriptors.resize(imgs.size());
    matches.resize(imgs.size());
    goodMatches.resize(imgs.size());
}

void detectPoints::findFeaturePoints() {
    cv::Ptr<cv::ORB> orb = cv::ORB::create();
    for (int i = 0; i < imgs.size(); ++i) {
        orb->detect(imgs[i], keyPoints[i]);
        orb->compute(imgs[i], keyPoints[i], descriptors[i]);
    }
}

void detectPoints::matchFeaturePoints() {
    findFeaturePoints();
    cv::BFMatcher matcher(cv::NORM_HAMMING);
    double minDis{10000};
    double maxDis{};
    for (int i = 0; i < keyPoints.size(); ++i) {
        matcher.match(imgs[0], imgs[i], matches[i]);
        for (int j = 0; j < descriptors[0][0].rows; ++j) {

        }
    }
}
