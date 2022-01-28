//
// Created by yyh on 2022/1/28.
//

#include "pose_estimate.h"
namespace sfmProject {
template <typename T>
bool pose_estimate::PnPCeres::operator()(const T *const camera,
                                         T *residual) const {
  T p[3];
  T point[3];
  point[0] = T(_xyz.x);
  point[1] = T(_xyz.y);
  point[2] = T(_xyz.z);
  ceres::AngleAxisRotatePoint(camera, point, p);  //计算RP
  p[0] += camera[3];
  p[1] += camera[4];
  p[2] += camera[5];
  T xp = p[0] / p[2];
  T yp = p[1] / p[2];  // xp,yp是归一化坐标，深度为p[2]
  T u_ = xp * K.at<double>(0, 0) + K.at<double>(0, 2);
  T v_ = yp * K.at<double>(1, 1) + K.at<double>(1, 2);
  residual[0] = T(_uv.x) - u_;
  residual[1] = T(_uv.y) - v_;
  return true;
}
ceres::CostFunction *pose_estimate::PnPCeres::Create(const cv::Point2f &uv,
                                                     const cv::Point3f &xyz) {
  return (
      new ceres::AutoDiffCostFunction<PnPCeres, 2, 6>(new PnPCeres(uv, xyz)));
}
}  // namespace sfmProject