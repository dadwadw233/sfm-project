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
  ceres::AngleAxisRotatePoint(camera, point, p);  // compute RP //
  p[0] += camera[3];
  p[1] += camera[4];
  p[2] += camera[5];
  T xp = p[0] / p[2];
  T yp = p[1] / p[2];  // xp,yp is Normalize coordinates，the depth is p[2] //
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
void pose_estimate::pose_estimation_2d2d(detectPoints points,
                                         std::vector<cv::Mat> &R,
                                         std::vector<cv::Mat> &t) {
//  K = (cv::Mat_<double>(3, 3) << 951.43, 0.0, 652.39, 0.0, 959.55, 412.55, 0.0,
//       0.0, 1.0);
  int focal_length = 521;
  int image_number = points.get_image_number();
  cv::Mat fundamental_matrix;
  cv::Mat essential_matrix;
  cv::Mat homography_matrix;

  std::vector<cv::Point2f> first_image_points;
  std::vector<cv::Point2f> now_image_points;
  cv::Point2d principal_point(640, 360);

  points.copy_key_points(first_image_points, 0);

  for (int i = 1; i < image_number; ++i) {
    points.copy_key_points(now_image_points, i);
    fundamental_matrix = cv::findFundamentalMat(
        first_image_points, now_image_points, cv::FM_8POINT);
    essential_matrix =
        cv::findEssentialMat(first_image_points, now_image_points, focal_length,
                             principal_point, cv::RANSAC);
    cv::recoverPose(essential_matrix, first_image_points, now_image_points,
                    R[i], t[i], focal_length, principal_point);
  }
}
}  // namespace sfmProject