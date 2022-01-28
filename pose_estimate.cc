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
<<<<<<< HEAD
  point[0]=T(_xyz.x);
  point[1]=T(_xyz.y);
  point[2]=T(_xyz.z);
  ceres::AngleAxisRotatePoint(camera, point, p);//计算RP
  p[0] += camera[3]; p[1] += camera[4]; p[2] += camera[5];//相机坐标2
  residual[0] = T(_uvw.x)-p[0];
  residual[1] = T(_uvw.y)-p[1];
  residual[2] = T(_uvw.z)-p[2];
  return true;
}
ceres::CostFunction *pose_estimate::PnPCeres::Create(const cv::Point2f &uv,
                                                     const cv::Point3f &xyz) {
  return (
      new ceres::AutoDiffCostFunction<PnPCeres, 2, 6>(new PnPCeres(uv, xyz)));
}
}  // namespace sfmProject