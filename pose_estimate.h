//
// Created by yyh on 2022/1/28.
//

#ifndef SFM_PROJECT__POSE_ESTIMATE_H_
#define SFM_PROJECT__POSE_ESTIMATE_H_
#include <ceres/ceres.h>
#include <Eigen/Dense>
#include <iostream>
#include <opencv2/core/eigen.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include "ceres/rotation.h"
#include "feature_points/detect_points.h"

namespace sfmProject {
class pose_estimate {
 private:
  static cv::Mat K;
  double camera[6];
  ceres::Problem problem;
  std::vector<cv::Point3f> pts_3d;
  std::vector<cv::Point2f> pts_2d;
  ceres::Solver::Options options;
  ceres::Solver::Summary summary;
  std::vector<std::pair<cv::Point2f, cv::Vec2d>>poseList

 public:
  explicit pose_estimate();

  pose_estimate(const pose_estimate&) = delete;

  pose_estimate& operator=(const pose_estimate&) = delete;

  ~pose_estimate();

  // the module to compute the residual
  struct PnPCeres {
    PnPCeres(const cv::Point2f& uv, const cv::Point3f& xyz)
        : _uv(uv), _xyz(xyz) {}

    template <typename T>
    bool operator()(const T* const camera,  //
                    T* residual) const;     //

    static ceres::CostFunction* Create(const cv::Point2f& uv,
                                       const cv::Point3f& xyz);
    const cv::Point2f _uv;
    const cv::Point3f _xyz;
  };

  void initialize();

  void constructProblem();

  void solveBA();

  void poseGeneration(const std::vector<cv::Mat>R, const std::vector<cv::Mat>t);
};
cv::Mat pose_estimate::K;
}  // namespace sfmProject
#endif  // SFM_PROJECT__POSE_ESTIMATE_H_
