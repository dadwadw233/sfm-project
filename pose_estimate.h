//
// Created by yyh on 2022/1/28.
//

#ifndef SFM_PROJECT__POSE_ESTIMATE_H_
#define SFM_PROJECT__POSE_ESTIMATE_H_
#include <ceres/ceres.h>
#include <iostream>
#include <opencv2/opencv.hpp>
namespace sfmProject {
class pose_estimate {
 private:
  static cv::Mat K;

 public:
  explicit pose_estimate();
  pose_estimate(const pose_estimate&) = delete;
  pose_estimate& operator=(const pose_estimate&) = delete;
  ~pose_estimate();
  // 代价函数的计算模型
  struct PnPCeres {
    PnPCeres(const cv::Point2f& uv, const cv::Point3f& xyz)
        : _uv(uv), _xyz(xyz) {}
    // 残差的计算
    template <typename T>
    bool operator()(const T* const camera,  // 位姿参数，有6维
                    T* residual) const;     // 残差

    static ceres::CostFunction* Create(const cv::Point2f& uv,
                                       const cv::Point3f& xyz);
    const cv::Point2f _uv;
    const cv::Point3f _xyz;
  };
  void initialize();
};
}  // namespace sfmProject
#endif  // SFM_PROJECT__POSE_ESTIMATE_H_
