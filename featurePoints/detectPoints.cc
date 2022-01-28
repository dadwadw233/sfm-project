//
// Created by dcr on 2022/1/23.
//

#include "detectPoints.h"

#include <utility>

detectPoints::detectPoints(std::vector<cv::Mat> inputImgs) {
    std::copy(inputImgs.begin(), inputImgs.end(), &imgs.front());
    keyPoints.resize(imgs.size());
    descriptors.resize(imgs.size());
    matches.resize(imgs.size());
    goodMatches.resize(imgs.size());
}

void detectPoints::findFeaturePoints() {
    cv::Ptr<cv::ORB> orb = cv::ORB::create();
    for (unsigned int i = 0; i < imgs.size(); ++i) {
        orb->detect(imgs[i], keyPoints[i]);
        orb->compute(imgs[i], keyPoints[i], descriptors[i]);
    }
}

void detectPoints::matchFeaturePoints() {
    findFeaturePoints();
    cv::BFMatcher matcher(cv::NORM_HAMMING);
    double minDis{10000};
    double maxDis{};
    for (unsigned int i = 0; i < keyPoints.size(); ++i) {
        minDis = 100000, maxDis = 0;
        matcher.match(imgs[0], imgs[i], matches[i]);
        for (int j = 0; j < descriptors[0][0].rows; ++j) {
            double dist = matches[0][i].distance;
            minDis = minDis < dist ? minDis : dist;
            maxDis = maxDis > dist ? maxDis : dist;
        }
    }

    for (unsigned int i = 0; i < keyPoints.size(); ++i) {
        std::vector<cv::DMatch> tempGoodMatches;
        for (int j = 0; j < descriptors[0][0].rows; ++j) {
            if (matches[i][j].distance <= fmax(2 * minDis, 10.0)) {
                tempGoodMatches.push_back(matches[i][j]);
            }
        }
        goodMatches.push_back(tempGoodMatches);
    }
}
