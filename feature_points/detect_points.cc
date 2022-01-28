//
// Created by dcr on 2022/1/23.
//

#include "detect_points.h"

#include <utility>

detect_points::detect_points(std::vector<cv::Mat> &input_images) {
    std::copy(input_images.begin(), input_images.end(), &images.front());
    key_points.resize(images.size());
    descriptors.resize(images.size());
    matches.resize(images.size());
    good_matches.resize(images.size());
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
        for (int j = 0; j < descriptors[0][0].rows; ++j) {
            double distance = matches[0][i].distance;
            min_distance = min_distance < distance ? min_distance : distance;
            max_distance = max_distance > distance ? max_distance : distance;
        }
    }
    // reduce the mismatch feature points improve the result
    for (unsigned int i = 0; i < key_points.size(); ++i) {
        std::vector<cv::DMatch> temp_good_matches;
        for (int j = 0; j < descriptors[0][0].rows; ++j) {
            if (matches[i][j].distance <= fmax(2 * min_distance, 10.0)) {
              temp_good_matches.push_back(matches[i][j]);
            }
        }
        good_matches.push_back(temp_good_matches);
    }
}
