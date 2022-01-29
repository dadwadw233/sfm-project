//
// Created by yyh on 2022/1/28.
//

#ifndef SFM_PROJECT__POSE_ESTIMATE_H_
#define SFM_PROJECT__POSE_ESTIMATE_H_
#include <ceres/ceres.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "ceres/rotation.h"
#include "feature_points/detect_points.h"

namespace sfmProject {
class pose_estimate {
 private:
  static cv::Mat K;

 public:
  explicit pose_estimate();
  pose_estimate(const pose_estimate&) = delete;
  pose_estimate& operator=(const pose_estimate&) = delete;
  ~pose_estimate();
  // the module of costFunction//
  struct PnPCeres {
    PnPCeres(const cv::Point2f& uv, const cv::Point3f& xyz)
        : _uv(uv), _xyz(xyz) {}
    // compute the residuals
    template <typename T>
    bool operator()(
        const T* const camera,  // Posture parameters, 6 dimensions//
        T* residual) const;     // residuals//

    static ceres::CostFunction* Create(const cv::Point2f& uv,
                                       const cv::Point3f& xyz);
    const cv::Point2f _uv;
    const cv::Point3f _xyz;
  };
  void initialize();
  void pose_estimation_2d2d(detectPoints points, std::vector<cv::Mat>& R,
                            std::vector<cv::Mat>& t);
};
}  // namespace sfmProject
#endif  // SFM_PROJECT__POSE_ESTIMATE_H_//
