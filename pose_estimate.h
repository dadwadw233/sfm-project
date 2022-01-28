//
// Created by yyh on 2022/1/28.
//

#ifndef SFM_PROJECT__POSE_ESTIMATE_H_
#define SFM_PROJECT__POSE_ESTIMATE_H_
#include <ceres/ceres.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <ceres/rotation.h>
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
  struct ICPCeres
  {
    ICPCeres ( cv::Point3f uvw,cv::Point3f xyz ) : _uvw(uvw),_xyz(xyz) {}
    // 残差的计算
    template <typename T>
    bool operator() (
        const T* const camera,     // 模型参数，有4维
        T* residual ) const;     // 残差
    static ceres::CostFunction* Create(const cv::Point3f &uvw,const cv::Point3f &xyz);
    const cv::Point3f _uvw;
    const cv::Point3f _xyz;
  };
  void initialize();
};
}  // namespace sfmProject
#endif  // SFM_PROJECT__POSE_ESTIMATE_H_
