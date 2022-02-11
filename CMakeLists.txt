cmake_minimum_required(VERSION 3.11)
project(sfm_project)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
find_package(Ceres REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(sfm_project main.cc feature_points/detect_points.cc feature_points/detect_points.h pose_estimate.cc pose_estimate.h)

add_library(detect_points feature_points/detect_points.cc)

target_link_libraries(sfm_project
        ${OpenCV_LIBS}
        Ceres::ceres
        Eigen3::Eigen)
